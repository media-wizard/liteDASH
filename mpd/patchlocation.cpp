/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "patchlocation.h"

namespace dash {
namespace mpd {

PatchLocation::PatchLocation() :
    ElementBase("PatchLocation"), url_(""), ttl_(0.0) {
}

const std::string& PatchLocation::GetUrl() const {
  return url_;
}

double PatchLocation::GetTtl() const {
  return ttl_;
}

} // namespace mpd
} // namespace dash
