/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "descriptor.h"

namespace dash {
namespace mpd {

Descriptor::Descriptor(const std::string &name) :
    ElementBase(name), scheme_id_uri_(""), value_(""), id_("") {
}

const std::string& Descriptor::GetSchemeIdUri() const {
  return scheme_id_uri_;
}

const std::string& Descriptor::GetValue() const {
  return value_;
}

const std::string& Descriptor::GetId() const {
  return id_;
}

} // namespace mpd
} // namespace dash
