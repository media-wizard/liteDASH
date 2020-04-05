/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "urltype.h"

namespace dash {
namespace mpd {

URLType::URLType(const std::string &name) :
    ElementBase(name), source_url_(""), range_("") {
}

const std::string& URLType::GetSourceURL() const {
  return source_url_;
}

const std::string& URLType::GetRange() const {
  return range_;
}

} // namespace mpd
} // namespace dash
