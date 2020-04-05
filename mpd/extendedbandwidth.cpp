/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "extendedbandwidth.h"
#include "modelpair.h"

namespace dash {
namespace mpd {

ExtendedBandwidth::ExtendedBandwidth() :
    ElementBase("ExtendedBandwidth"), vbr_(false) {
}

ExtendedBandwidth::~ExtendedBandwidth() {
  for (size_t i = 0; i < model_pairs_.size(); i++)
    delete (model_pairs_.at(i));
}

const std::vector<ModelPair*>& ExtendedBandwidth::GetModelPairs() const {
  return model_pairs_;
}

bool ExtendedBandwidth::GetVbr() const {
  return vbr_;
}

} // namespace mpd
} // namespace dash
