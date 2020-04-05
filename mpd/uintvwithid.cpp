/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "uintvwithid.h"

namespace dash {
namespace mpd {

UIntVWithID::UIntVWithID(const std::string &name) :
    ElementBase(name), id_(0), content_type_("") {
}

const std::vector<uint32_t>& UIntVWithID::GetList() const {
  return list_;
}

uint32_t UIntVWithID::GetId() const {
  return id_;
}

const std::vector<std::string>& UIntVWithID::GetProfiles() const {
  return profiles_;
}

const std::string& UIntVWithID::GetContentType() const {
  return content_type_;
}

} // namespace mpd
} // namespace dash
