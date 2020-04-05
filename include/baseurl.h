/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_BASEURL_H_
#define DASH_BASEURL_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class BaseUrl: public ElementBase {
  public:
    BaseUrl();
    const std::string& GetUrl() const;
    const std::string& GetServiceLocation() const;
    const std::string& GetByteRange() const;
    double GetAvailabilityTimeOffset() const;
    bool IsAvailabilityTimeComplete() const;
    const std::string& GetTimeShiftBufferDepth() const;
    bool HasRangeAccess() const;

  private:
    std::string url_;
    std::string service_location_;
    std::string byte_range_;
    double availability_time_offset_;
    bool availability_time_complete_;
    std::string time_shift_buffer_depth_;
    bool range_access_;

    friend class BaseURLElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_BASEURL_H_ */
