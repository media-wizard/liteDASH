/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "randomaccess.h"

namespace dash {
namespace mpd {

RandomAccess::RandomAccess() :
    ElementBase("RandomAccess"), type_("closed") {
}

uint32_t RandomAccess::GetInterval() const {
  return interval_;
}

const std::string& RandomAccess::GetType() const {
  return type_;
}

const std::string& RandomAccess::GetMinBufferTime() const {
  return min_buffer_time_;
}

uint32_t RandomAccess::GetBandwidth() const {
  return bandwidth_;
}

} // namespace mpd
} // namespace dash
