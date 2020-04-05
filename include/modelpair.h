/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_MODELPAIR_H_
#define DASH_MODELPAIR_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class ModelPair: public ElementBase {
  public:
    ModelPair();
    const std::string& GetBufferTime() const;
    uint64_t GetBandwidth() const;

  private:
    std::string buffer_time_;
    uint64_t band_width_;

    friend class ModelPairElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_MODELPAIR_H_ */
