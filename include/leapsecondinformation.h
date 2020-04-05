/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_LEAPSECONDINFORMATION_H_
#define DASH_LEAPSECONDINFORMATION_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class LeapSecondInformation: public ElementBase {
  public:
    LeapSecondInformation();
    int32_t GetAvailabilityStartLeapOffset() const;
    int32_t GetNextAvailabilityStartLeapOffset() const;
    const std::string& GetNextLeapChangeTime() const;

  private:
    int32_t availability_start_leap_offset_;
    int32_t next_availability_start_leap_offset_;
    std::string next_leap_change_time_;

    friend class LeapSecondInformationElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_LEAPSECONDINFORMATION_H_ */
