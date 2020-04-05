/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "subset.h"

namespace dash {
namespace mpd {

Subset::Subset() :
    ElementBase("Subset"), id_("") {
}

const std::vector<uint32_t>& Subset::Contains() const {
  return contains_;
}

const std::string& Subset::GetId() const {
  return id_;
}

} // namespace mpd
} // namespace dash
