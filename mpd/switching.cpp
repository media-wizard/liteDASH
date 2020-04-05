/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "switching.h"

namespace dash {
namespace mpd {

Switching::Switching() :
    ElementBase("Switching"), interval_(0), type_("media") {
}

uint32_t Switching::GetInterval() const {
  return interval_;
}

const std::string& Switching::GetType() const {
  return type_;
}

} // namespace mpd
} // namespace dash
