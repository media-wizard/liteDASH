/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "leapsecondinformation.h"

namespace dash {
namespace mpd {

LeapSecondInformation::LeapSecondInformation() :
    ElementBase("LeapSecondInformation"), availability_start_leap_offset_(0) {
}

int32_t LeapSecondInformation::GetAvailabilityStartLeapOffset() const {
  return availability_start_leap_offset_;
}

int32_t LeapSecondInformation::GetNextAvailabilityStartLeapOffset() const {
  return next_availability_start_leap_offset_;
}

const std::string& LeapSecondInformation::GetNextLeapChangeTime() const {
  return next_leap_change_time_;
}

} // namespace mpd
} // namespace dash
