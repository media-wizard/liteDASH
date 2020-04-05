/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "uintpairswithid.h"

namespace dash {
namespace mpd {

UIntPairsWithID::UIntPairsWithID(const std::string &name) :
    ElementBase(name), type_("") {
}

UIntPairsWithID::~UIntPairsWithID() {
  for (size_t i = 0; i < ql_pairs_.size(); i++)
    delete (ql_pairs_.at(i));
}

const std::vector<UIntPairs*>& UIntPairsWithID::GetQualityLatency() const {
  return ql_pairs_;
}

const std::string& UIntPairsWithID::GetType() const {
  return type_;
}

} // namespace mpd
} // namespace dash
