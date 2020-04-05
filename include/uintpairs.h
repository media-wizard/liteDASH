/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_UINTPAIRS_H_
#define DASH_UINTPAIRS_H_

#include "elementbase.h"

namespace dash {
namespace mpd {

class UIntPairs {
  public:
    UIntPairs(uint32_t latency, uint32_t quality);
    uint32_t GetLatency() const;
    uint32_t GetQuality() const;

  private:
    uint32_t latency_;
    uint32_t quality_;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_UINTPAIRS_H_ */
