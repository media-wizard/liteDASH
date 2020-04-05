/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_POPULARITYRATE_H_
#define DASH_POPULARITYRATE_H_

#include "elementbase.h"

namespace dash {
namespace mpd {

class PopularityRate: public ElementBase {
  public:
    PopularityRate();
    uint8_t GetPopularityRate() const;
    uint64_t GetStart() const;
    int32_t GetR() const;

  private:
    uint8_t popularity_rate_;
    uint64_t start_;
    int32_t r_;

    friend class PopularityRateElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_POPULARITYRATE_H_ */
