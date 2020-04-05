/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "failovercontent.h"
#include "fcs.h"

namespace dash {
namespace mpd {

FailoverContent::FailoverContent() :
    ElementBase("FailoverContent"), valid_(true) {
}

FailoverContent::~FailoverContent() {
  for (size_t i = 0; i < fcs_.size(); i++)
    delete (fcs_.at(i));
}

const std::vector<FCS*>& FailoverContent::GetFCS() const {
  return fcs_;
}

bool FailoverContent::IsValid() const {
  return valid_;
}

} // namespace mpd
} // namespace dash
