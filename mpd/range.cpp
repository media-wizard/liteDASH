/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "range.h"

namespace dash {
namespace mpd {

Range::Range() :
    ElementBase("Range"), start_time_(""), duration_("") {
}

const std::string& Range::GetStarttime() const {
  return start_time_;
}

const std::string& Range::GetDuration() const {
  return duration_;
}

} // namespace mpd
} // namespace dash
