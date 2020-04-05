/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "popularityrate.h"

namespace dash {
namespace mpd {

PopularityRate::PopularityRate() :
    ElementBase("PopularityRate"), r_(0) {
}

uint8_t PopularityRate::GetPopularityRate() const {
  return popularity_rate_;
}

uint64_t PopularityRate::GetStart() const {
  return start_;
}

int32_t PopularityRate::GetR() const {
  return r_;
}

} // namespace mpd
} // namespace dash
