/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "operatingquality.h"

namespace dash {
namespace mpd {

OperatingQuality::OperatingQuality() :
    ElementBase("OperatingQuality"), media_type_("any") {
}

const std::string& OperatingQuality::GetMediaType() const {
  return media_type_;
}

uint32_t OperatingQuality::GetMin() const {
  return min_;
}

uint32_t OperatingQuality::GetMax() const {
  return max_;
}

uint32_t OperatingQuality::GetTarget() const {
  return target_;
}

const std::string& OperatingQuality::GetType() const {
  return type_;
}

uint32_t OperatingQuality::GetMaxDifference() const {
  return max_difference_;
}

} // namespace mpd
} // namespace dash
