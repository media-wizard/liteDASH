/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "latency.h"

namespace dash {
namespace mpd {

Latency::Latency() :
    ElementBase("Latency") {
}

Latency::~Latency() {
  for (size_t i = 0; i < quality_latency_pairs_.size(); i++)
    delete (quality_latency_pairs_.at(i));
}

const std::vector<UIntPairsWithID*>& Latency::GetQualityLatencyType() const {
  return quality_latency_pairs_;
}

uint32_t Latency::GetReferenceId() const {
  return reference_id_;
}

uint32_t Latency::GetTarget() const {
  return target_;
}

uint32_t Latency::GetMax() const {
  return max_;
}

uint32_t Latency::GetMin() const {
  return min_;
}

} // namespace mpd
} // namespace dash
