/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "servicedescription.h"
#include "descriptor.h"
#include "latency.h"
#include "operatingbandwidth.h"
#include "operatingquality.h"
#include "playbackrate.h"

namespace dash {
namespace mpd {

ServiceDescription::ServiceDescription() :
    ElementBase("ServiceDescription") {
}

ServiceDescription::~ServiceDescription() {
  for (size_t i = 0; i < scope_.size(); i++)
    delete (scope_.at(i));
  for (size_t i = 0; i < latency_.size(); i++)
    delete (latency_.at(i));
  for (size_t i = 0; i < playback_rate_.size(); i++)
    delete (playback_rate_.at(i));
  for (size_t i = 0; i < operating_quality_.size(); i++)
    delete (operating_quality_.at(i));
  for (size_t i = 0; i < operating_bandwidth_.size(); i++)
    delete (operating_bandwidth_.at(i));
}

const std::vector<Descriptor*>& ServiceDescription::GetScope() const {
  return scope_;
}

const std::vector<Latency*>& ServiceDescription::GetLatency() const {
  return latency_;
}

const std::vector<PlaybackRate*>& ServiceDescription::GetPlaybackRate() const {
  return playback_rate_;
}

const std::vector<OperatingQuality*>& ServiceDescription::GetOperatingQuality() const {
  return operating_quality_;
}

const std::vector<OperatingBandwidth*>& ServiceDescription::GetOperatingBandwidth() const {
  return operating_bandwidth_;
}

uint32_t ServiceDescription::GetId() const {
  return id_;
}

} // namespace mpd
} // namespace dash
