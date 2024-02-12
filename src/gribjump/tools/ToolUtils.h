/*
 * (C) Copyright 2024- ECMWF.
 *
 * This software is licensed under the terms of the Apache Licence Version 2.0
 * which can be obtained at http://www.apache.org/licenses/LICENSE-2.0.
 * In applying this licence, ECMWF does not waive the privileges and immunities
 * granted to it by virtue of its status as an intergovernmental organisation nor
 * does it submit to any jurisdiction.
 */

#pragma once

#include "eckit/filesystem/PathName.h"
#include "gribjump/ExtractionData.h"

namespace gribjump
{

std::vector<std::vector<Range>> parseRangesFile(eckit::PathName fname);

std::vector<std::vector<std::vector<double>>> eccodesExtract(metkit::mars::MarsRequest request, std::vector<Range> ranges);

std::vector<std::vector<std::vector<double>>> eccodesExtract(eckit::PathName path, eckit::OffsetList offsets, std::vector<Range> ranges);

} // namespace gribjump
