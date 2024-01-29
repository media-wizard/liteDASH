/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "elementbase.h"

namespace dash {
namespace mpd {

ElementBase::ElementBase(const std::string &name) :
    name_(name) {
}

ElementBase::~ElementBase() {
  for (size_t i = 0; i < raw_child_elements_.size(); i++)
    delete (raw_child_elements_.at(i));
}

const std::string& ElementBase::GetName() const {
  return name_;
}

const std::vector<ElementBase*> ElementBase::GetRawChildElements() const {
  return raw_child_elements_;
}

const std::map<std::string, std::string> ElementBase::GetRawAttributes() const {
  return raw_attribs_;
}

const std::string& ElementBase::GetRawInnerText() const {
  return raw_inner_text_;
}

} // namespace mpd
} // namespace dash
