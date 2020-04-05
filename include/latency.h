/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_LATENCY_H_
#define DASH_LATENCY_H_

#include <vector>

#include "uintpairswithid.h"

namespace dash {
namespace mpd {

class UIntPairsWithID;

class Latency: public ElementBase {
  public:
    Latency();
    ~Latency();
    const std::vector<UIntPairsWithID*>& GetQualityLatencyType() const;
    uint32_t GetReferenceId() const;
    uint32_t GetTarget() const;
    uint32_t GetMax() const;
    uint32_t GetMin() const;

  private:
    std::vector<UIntPairsWithID*> quality_latency_pairs_;
    uint32_t reference_id_;
    uint32_t target_;
    uint32_t max_;
    uint32_t min_;

    friend class LatencyElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_LATENCY_H_ */
