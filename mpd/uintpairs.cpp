/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "uintpairs.h"

namespace dash {
namespace mpd {

UIntPairs::UIntPairs(uint32_t latency, uint32_t quality) :
    latency_(latency), quality_(quality) {
}

uint32_t UIntPairs::GetLatency() const {
  return latency_;
}

uint32_t UIntPairs::GetQuality() const {
  return quality_;
}

} // namespace mpd
} // namespace dash
