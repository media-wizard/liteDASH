/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "contentprotection.h"

namespace dash {
namespace mpd {

ContentProtection::ContentProtection() :
    Descriptor("ContentProtection"), robustness_(""), ref_id_(""), ref_("") {
}

const std::string& ContentProtection::GetRobustness() const {
  return robustness_;
}

const std::string& ContentProtection::GetRefId() const {
  return ref_id_;
}

const std::string& ContentProtection::GetRef() const {
  return ref_;
}

} // namespace mpd
} // namespace dash
