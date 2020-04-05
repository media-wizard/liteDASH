/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "metrics.h"
#include "descriptor.h"
#include "range.h"

namespace dash {
namespace mpd {

Metrics::Metrics() :
    ElementBase("Metrics"), metrics_("") {
}

Metrics::~Metrics() {
  for (size_t i = 0; i < reportings_.size(); i++)
    delete (reportings_.at(i));
  for (size_t i = 0; i < ranges_.size(); i++)
    delete (ranges_.at(i));
}

const std::vector<Descriptor*>& Metrics::GetReportings() const {
  return reportings_;
}

const std::vector<Range*>& Metrics::GetRanges() const {
  return ranges_;
}

const std::string& Metrics::GetMetrics() const {
  return metrics_;
}

} // namespace mpd
} // namespace dash
