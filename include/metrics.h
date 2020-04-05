/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_METRICS_H_
#define DASH_METRICS_H_

#include <string>
#include <vector>

#include "elementbase.h"

namespace dash {
namespace mpd {

class Descriptor;
class Range;

class Metrics: public ElementBase {
  public:
    Metrics();
    ~Metrics();
    const std::vector<Descriptor*>& GetReportings() const;
    const std::vector<Range*>& GetRanges() const;
    const std::string& GetMetrics() const;

  private:
    std::vector<Descriptor*> reportings_;
    std::vector<Range*> ranges_;
    std::string metrics_;

    friend class MetricsElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_METRICS_H_ */
