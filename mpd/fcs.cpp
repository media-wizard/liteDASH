/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "fcs.h"

namespace dash {
namespace mpd {

FCS::FCS() :
    ElementBase("FCS"), presentation_time_(0), duration_(0) {
}

uint64_t FCS::GetPresentationTime() const {
  return presentation_time_;
}

uint64_t FCS::GetDuration() const {
  return duration_;
}

} // namespace mpd
} // namespace dash
