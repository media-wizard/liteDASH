/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_EXTENDEDBANDWIDTH_H_
#define DASH_EXTENDEDBANDWIDTH_H_

#include <vector>

#include "elementbase.h"

namespace dash {
namespace mpd {

class ModelPair;

class ExtendedBandwidth: public ElementBase {
  public:
    ExtendedBandwidth();
    ~ExtendedBandwidth();
    const std::vector<ModelPair*>& GetModelPairs() const;
    bool GetVbr() const;

  private:
    std::vector<ModelPair*> model_pairs_;
    bool vbr_;

    friend class ExtendedBandwidthElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_EXTENDEDBANDWIDTH_H_ */
