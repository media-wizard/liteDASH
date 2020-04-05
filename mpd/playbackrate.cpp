/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "playbackrate.h"

namespace dash {
namespace mpd {

PlaybackRate::PlaybackRate() :
    ElementBase("PlaybackRate") {
}

double PlaybackRate::GetMax() const {
  return max_;
}

double PlaybackRate::GetMin() const {
  return min_;
}

} // namespace mpd
} // namespace dash
