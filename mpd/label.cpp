/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "label.h"

namespace dash {
namespace mpd {

Label::Label() :
    ElementBase("Label"), id_(0) {
}

uint32_t Label::GetId() const {
  return id_;
}

const std::string& Label::GetLang() const {
  return lang_;
}

} // namespace mpd
} // namespace dash
