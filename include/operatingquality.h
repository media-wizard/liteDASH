/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_OPERATINGQUALITY_H_
#define DASH_OPERATINGQUALITY_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class OperatingQuality: public ElementBase {
  public:
    OperatingQuality();
    const std::string& GetMediaType() const;
    uint32_t GetMin() const;
    uint32_t GetMax() const;
    uint32_t GetTarget() const;
    const std::string& GetType() const;
    uint32_t GetMaxDifference() const;

  private:
    std::string media_type_;
    uint32_t min_;
    uint32_t max_;
    uint32_t target_;
    std::string type_;
    uint32_t max_difference_;

    friend class OperatingQualityElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_OPERATINGQUALITY_H_ */
