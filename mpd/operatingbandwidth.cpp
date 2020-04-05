/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "operatingbandwidth.h"

namespace dash {
namespace mpd {

OperatingBandwidth::OperatingBandwidth() :
    ElementBase("OperatingBandwidth"), media_type_("all") {
}

const std::string& OperatingBandwidth::GetMediaType() const {
  return media_type_;
}

uint32_t OperatingBandwidth::GetMin() const {
  return min_;
}

uint32_t OperatingBandwidth::GetMax() const {
  return max_;
}

uint32_t OperatingBandwidth::GetTarget() const {
  return target_;
}

} // namespace mpd
} // namespace dash
