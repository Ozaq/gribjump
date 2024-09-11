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

#pragma once

#include "eckit/serialisation/Stream.h"
#include "metkit/mars/MarsRequest.h"
#include "gribjump/ExtractionItem.h"
#include "gribjump/Task.h"
#include "gribjump/Lister.h"
#include "gribjump/Types.h"

namespace gribjump {

class Engine {
public:
    
    Engine();
    ~Engine();

    ResultsMap extract(const MarsRequests& requests, const RangesList& ranges, bool flattenRequests = false);
    
    // byfiles: scan entire file, not just fields matching request
    size_t scan(const MarsRequests& requests, bool byfiles = false);

    std::map<std::string, std::unordered_set<std::string> > axes(const std::string& request);

    void reportErrors(eckit::Stream& client_);
    void scheduleTasks(filemap_t& filemap);

private: 

    filemap_t buildFileMap(const MarsRequests& requests, ExItemMap& keyToExtractionItem);
    ExItemMap buildKeyToExtractionItem(const MarsRequests& requests, const RangesList& ranges, bool flatten);
    ResultsMap collectResults(ExItemMap& keyToExtractionItem);
    void forwardRemoteExtraction(filemap_t& filemap);

private:

    TaskGroup taskGroup_;

};


} // namespace gribjump
