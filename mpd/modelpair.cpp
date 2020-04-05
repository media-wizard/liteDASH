/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "modelpair.h"

namespace dash {
namespace mpd {

ModelPair::ModelPair() :
    ElementBase("ModelPair"), buffer_time_(""), band_width_(0) {
}

const std::string& ModelPair::GetBufferTime() const {
  return buffer_time_;
}

uint64_t ModelPair::GetBandwidth() const {
  return band_width_;
}

} // namespace mpd
} // namespace dash
