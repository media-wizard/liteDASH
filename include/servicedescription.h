/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_SERVICEDESCRIPTION_H_
#define DASH_SERVICEDESCRIPTION_H_

#include <vector>

#include "elementbase.h"

namespace dash {
namespace mpd {

class Descriptor;
class Latency;
class PlaybackRate;
class OperatingQuality;
class OperatingBandwidth;

class ServiceDescription: public ElementBase {
  public:
    ServiceDescription();
    ~ServiceDescription();
    const std::vector<Descriptor*>& GetScope() const;
    const std::vector<Latency*>& GetLatency() const;
    const std::vector<PlaybackRate*>& GetPlaybackRate() const;
    const std::vector<OperatingQuality*>& GetOperatingQuality() const;
    const std::vector<OperatingBandwidth*>& GetOperatingBandwidth() const;
    uint32_t GetId() const;

  private:
    std::vector<Descriptor*> scope_;
    std::vector<Latency*> latency_;
    std::vector<PlaybackRate*> playback_rate_;
    std::vector<OperatingQuality*> operating_quality_;
    std::vector<OperatingBandwidth*> operating_bandwidth_;
    uint32_t id_;

    friend class ServiceDescriptionElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_SERVICEDESCRIPTION_H_ */
