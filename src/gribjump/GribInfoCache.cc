/*
 * (C) Copyright 2023- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

/// @author Christopher Bradley
/// @author Tiago Quintino


#include "eckit/filesystem/PathName.h"
#include "eckit/io/FileHandle.h"
#include "eckit/log/Log.h"
#include "eckit/log/Plural.h"
#include "eckit/config/Resource.h"
#include "eckit/log/TimeStamp.h"
#include "eckit/exception/Exceptions.h"

#include "gribjump/GribInfoCache.h"
#include "gribjump/LibGribJump.h"
#include "gribjump/info/JumpInfoFactory.h"
#include "gribjump/info/InfoExtractor.h"

namespace gribjump {

const char* file_ext = ".gribjump";

//----------------------------------------------------------------------------------------------------------------------

GribInfoCache& GribInfoCache::instance() {
    static GribInfoCache instance_;
    return instance_;
}

GribInfoCache::~GribInfoCache() {
    for (auto& entry : cache_) {
        delete entry.second;
    }
}

GribInfoCache::GribInfoCache() {

    static_assert(sizeof(off_t) == sizeof(eckit::Offset), "off_t and eckit::Offset must be the same size"); // dont think this is required anymore

    std::string cache = eckit::Resource<std::string>("gribJumpCacheDir;$GRIBJUMP_CACHE_DIR", "");
    LOG_DEBUG_LIB(LibGribJump) << "Cache directory " << cache << std::endl;

    if(cache.empty()) {
        cacheDir_ = eckit::PathName();
        persistentCache_ = false; 

        LOG_DEBUG_LIB(LibGribJump) << "Warning, cache persistence is disabled" << std::endl;

        return;
    }

    cacheDir_ = eckit::PathName(cache);
    persistentCache_ = true;

    if (!cacheDir_.exists()) {
        throw eckit::BadValue("Cache directory " + cacheDir_ + " does not exist");
    }
}

eckit::PathName GribInfoCache::cacheFilePath(const eckit::PathName& path) const {
    return cacheDir_ / path.baseName() + file_ext;
}

FileCache& GribInfoCache::getFileCache(const filename_t& f) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = cache_.find(f);
    if(it != cache_.end()) return *(it->second);
    
    eckit::Log::info() << "New GribInfoCache entry for file " << f << std::endl;
    eckit::PathName cachePath = cacheFilePath(f);
    FileCache* filecache = new FileCache(cachePath); // this will load the cache file into memory if it exists
    cache_.insert(std::make_pair(f, filecache));
    return *filecache;
}

JumpInfo* GribInfoCache::get(const eckit::URI& uri) {
    
    // if (!persistentCache_) return nullptr;

    eckit::PathName path = uri.path();
    eckit::Offset offset = std::stoll(uri.fragment());

    return get(path, offset);
}

JumpInfo* GribInfoCache::get(const eckit::PathName& path, const eckit::Offset offset) {

    filename_t f = path.baseName();
    FileCache& filecache = getFileCache(f);

    // return it if in memory cache
    {   
        JumpInfo* info = filecache.find(offset);
        if (info) return info;

        LOG_DEBUG_LIB(LibGribJump) << "GribInfoCache file " << f << " does not contain JumpInfo for field at offset " << offset << std::endl;

    }

    // Extract explicitly

    InfoExtractor extractor;
    JumpInfo* info = extractor.extract(path, offset);

    filecache.insert(offset, info);

    return info;
}

std::vector<JumpInfo*> GribInfoCache::get(const eckit::PathName& path, const eckit::OffsetList& offsets) {

    filename_t f = path.baseName();
    FileCache& filecache = getFileCache(f);

    std::vector<eckit::Offset> missingOffsets;

    for (const auto& offset : offsets) {
        if (!filecache.find(offset)) {
            missingOffsets.push_back(offset);
        }
    }

    if (!missingOffsets.empty()) {
        
        std::sort(missingOffsets.begin(), missingOffsets.end());
        InfoExtractor extractor;
        std::vector<JumpInfo*> newInfos = extractor.extract(path, missingOffsets);
        filecache.insert(newInfos);
    }

    std::vector<JumpInfo*> result;

    for (const auto& offset : offsets) {
        JumpInfo* info = filecache.find(offset);
        ASSERT(info);
        result.push_back(info);
    }

    return result;
}

// maybe insert should be private.
// Only GribInfoCache will do insertions. Client code can only "get", which may in the process insert into cache

void GribInfoCache::insert(const eckit::PathName& path, const eckit::Offset offset, JumpInfo* info) {

    filename_t f = path.baseName();
    LOG_DEBUG_LIB(LibGribJump) << "GribJumpCache inserting " << f << ":" << offset << std::endl;
    FileCache& filecache = getFileCache(f);
    filecache.insert(offset, info);
}


void GribInfoCache::insert(const eckit::PathName& path, std::vector<JumpInfo*> infos) {

    filename_t f = path.baseName();
    LOG_DEBUG_LIB(LibGribJump) << "GribJumpCache inserting " << f << "" << infos.size() << " fields" << std::endl;
    FileCache& filecache = getFileCache(f);
    filecache.insert(infos);
}


void GribInfoCache::persist(bool merge){
    if (!persistentCache_) {
        LOG_DEBUG_LIB(LibGribJump) << "Warning, GribInfoCache::persist called but cache persistence is disabled" << std::endl;
        return;
    }
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto& [filename, filecache] : cache_) {
        filecache->persist(merge);
    }
}

void GribInfoCache::clear() {
    std::lock_guard<std::mutex> lock(mutex_);

    for (auto& entry : cache_) {
        delete entry.second;
    }

    cache_.clear();
}

void GribInfoCache::scan(const eckit::PathName& fdbpath, const std::vector<eckit::Offset>& offsets) {

    // this will be executed in parallel so we dont lock main mutex_ here
    // we will rely on each method to lock mutex when needed

    LOG_DEBUG_LIB(LibGribJump) << "Scanning " << fdbpath << " at " << eckit::Plural(offsets.size(), "offsets") << std::endl;

    auto base = fdbpath.baseName();
    auto cachePath = cacheFilePath(base);

    // if cache exists load so we can merge with memory cache
    FileCache& filecache = getFileCache(base);


    // Find which offsets are not already in file cache
    std::vector<eckit::Offset> newOffsets;

    for (const auto& offset : offsets) {
        if(!filecache.find(offset)) {
            newOffsets.push_back(offset);
        }
    }

    if (newOffsets.empty()) {
        LOG_DEBUG_LIB(LibGribJump) << "No new fields to scan in " << fdbpath << std::endl;
        return;
    }

    std::sort(newOffsets.begin(), newOffsets.end());

    InfoExtractor extractor;
    std::vector<JumpInfo*> infos = extractor.extract(fdbpath, newOffsets);
    
    filecache.insert(infos);
    
    if (persistentCache_) {
        filecache.persist();
    }

}

void GribInfoCache::scan(const eckit::PathName& fdbpath) {

    // this will be executed in parallel so we dont lock main mutex_ here
    // we will rely on each method to lock mutex when needed

    LOG_DEBUG_LIB(LibGribJump) << "Scanning whole file " << fdbpath << std::endl;

    auto base = fdbpath.baseName();
    auto cachePath = cacheFilePath(base);

    // if cache exists load so we can merge with memory cache
    FileCache& filecache = getFileCache(base);

    InfoExtractor extractor;
    std::vector<JumpInfo*> infos = extractor.extract(fdbpath);
    
    filecache.insert(infos);

    if (persistentCache_) {
        filecache.persist();
    }

}

void GribInfoCache::print(std::ostream& s) const {
    std::lock_guard<std::mutex> lock(mutex_);
    // Print the manifest, then the cache
    s << "GribInfoCache[";
    s << "cacheDir=" << cacheDir_ << std::endl;
    s << "cache=" << std::endl;
    for (auto& entry : cache_) {
        s << entry.first << " -> " << entry.second << std::endl;
    }
    s << "]";
}


// ------------------------------------------------------------------------------------------------------

FileCache::FileCache(const eckit::PathName& path): path_(path) {
    if (path_.exists()) {
        
        LOG_DEBUG_LIB(LibGribJump) << "Loading file cache from " << path_ << std::endl;

        eckit::FileStream s(path_, "r");
        decode(s);
        s.close();
    } else {
        LOG_DEBUG_LIB(LibGribJump) << "Cache file " << path_ << " does not exist" << std::endl;
    }
}

FileCache::FileCache(eckit::Stream& s) {
    decode(s);
}

FileCache::~FileCache() {
    for (auto& entry : map_) {
        delete entry.second; 
    }
}

void FileCache::encode(eckit::Stream& s) {
    std::lock_guard<std::mutex> lock(mutex_);
    s << map_.size();
    for (auto& entry : map_) {
        s << entry.first;
        s << *entry.second;
    }
}

void FileCache::decode(eckit::Stream& s) {
    std::lock_guard<std::mutex> lock(mutex_);
    size_t size;
    s >> size;
    for (size_t i = 0; i < size; i++) {
        eckit::Offset offset;
        s >> offset;
        JumpInfo* info = eckit::Reanimator<JumpInfo>::reanimate(s);

        map_.insert(std::make_pair(offset, info));
    }
}

void FileCache::merge(FileCache& other) {
    std::lock_guard<std::mutex> lock(mutex_);
    other.lock();
    for (auto& entry : other.map()) {
        map_.insert(entry);
    }
    other.unlock();
}

void FileCache::persist(bool merge) {


    if (merge && path_.exists()) {
        // Load an existing cache and merge with this
        // Note: if same entry exists in both, the one in *this will be used
        FileCache other(path_);
        this->merge(other);
    }

    // create a unique filename for the cache file before (atomically) moving it into place

    eckit::PathName uniqPath = eckit::PathName::unique(path_);

    LOG_DEBUG_LIB(LibGribJump) << "Writing GribInfo to temporary file " << uniqPath << std::endl;
    eckit::FileStream s(uniqPath, "w");
    encode(s);
    s.close();

    // atomically move the file into place
    LOG_DEBUG_LIB(LibGribJump) << "Moving temp file cache to " << path_ << std::endl;
    eckit::PathName::rename(uniqPath, path_);
}

void FileCache::insert(eckit::Offset offset, JumpInfo* info) {
    std::lock_guard<std::mutex> lock(mutex_);
    map_.insert(std::make_pair(offset, info));
}


void FileCache::insert(std::vector<JumpInfo*> infos) {
    std::lock_guard<std::mutex> lock(mutex_);
    for (auto& info : infos) {
        map_.insert(std::make_pair(info->msgStartOffset(), info));
    }
}

// wrapper around map_.find()
JumpInfo* FileCache::find(eckit::Offset offset) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = map_.find(offset);
    if (it != map_.end()) {
        return it->second;
    }
    return nullptr;
}

size_t FileCache::count() {
    std::lock_guard<std::mutex> lock(mutex_);
    return map_.size();
}

}  // namespace gribjump
