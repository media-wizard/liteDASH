/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_OPERATINGBANDWIDTH_H_
#define DASH_OPERATINGBANDWIDTH_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class OperatingBandwidth: public ElementBase {
  public:
    OperatingBandwidth();
    const std::string& GetMediaType() const;
    uint32_t GetMin() const;
    uint32_t GetMax() const;
    uint32_t GetTarget() const;

  private:
    std::string media_type_;
    uint32_t min_;
    uint32_t max_;
    uint32_t target_;

    friend class OperatingBandwidthElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_OPERATINGBANDWIDTH_H_ */
