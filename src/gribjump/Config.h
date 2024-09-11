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

#include "eckit/config/LocalConfiguration.h"


namespace gribjump {

class Config : public eckit::LocalConfiguration {
public:
    Config();
    Config(const eckit::PathName);

    std::map<std::string, std::string> getMap(const std::string& key) const;
};

} // namespace gribjump