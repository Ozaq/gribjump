/*
 * (C) Copyright 2023- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

# include "gribjump/GribJump.h"

#pragma once

namespace gribjump {

// GribJumpFactory, which will create either a GribJump or a RemoteGribJump
// depending on whether the environment variable GRIBJUMP_REMOTE is set.

class GribJumpFactory {

    virtual GribJumpBase *make() const = 0 ;

protected:

    GribJumpFactory(const std::string &);
    virtual ~GribJumpFactory();

    std::string name_;

public:

    static GribJumpBase *build(const std::string &name);

};

/// Templated specialisation of the self-registering factory,
/// that does the self-registration, and the construction of each object.

template< class T>
class GribJumpBuilder : public GribJumpFactory {

    virtual GribJumpBase *make() const override {
        return new T();
    }

public:
    GribJumpBuilder(const std::string &name) : GribJumpFactory(name) {}
};

} // namespace gribjump
