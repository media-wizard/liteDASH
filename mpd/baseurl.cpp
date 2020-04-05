/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "baseurl.h"

namespace dash {
namespace mpd {

BaseUrl::BaseUrl() :
    ElementBase("BaseURL"), url_(""), service_location_(""), byte_range_(""),
    time_shift_buffer_depth_(""), range_access_(false) {
}

const std::string& BaseUrl::GetUrl() const {
  return url_;
}

const std::string& BaseUrl::GetServiceLocation() const {
  return service_location_;
}

const std::string& BaseUrl::GetByteRange() const {
  return byte_range_;
}

double BaseUrl::GetAvailabilityTimeOffset() const {
  return availability_time_offset_;
}

bool BaseUrl::IsAvailabilityTimeComplete() const {
  return availability_time_complete_;
}

const std::string& BaseUrl::GetTimeShiftBufferDepth() const {
  return time_shift_buffer_depth_;
}

bool BaseUrl::HasRangeAccess() const {
  return range_access_;
}

} // namespace mpd
} // namespace dash
