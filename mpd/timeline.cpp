/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "timeline.h"

namespace dash {
namespace mpd {

Timeline::Timeline() :
    ElementBase("S"),
    t_(0), n_(0), d_(0), r_(0), k_(0) {
}

uint64_t Timeline::GetStartTime() const {
  return t_;
}

uint32_t Timeline::GetDuration() const {
  return d_;
}

uint32_t Timeline::GetRepeatCount() const {
  return r_;
}

} // namespace mpd
} // namespace dash
