/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "segmenttimeline.h"
#include "timeline.h"

namespace dash {
namespace mpd {

SegmentTimeline::SegmentTimeline() :
    ElementBase("SegmentTimeline") {
}

SegmentTimeline::~SegmentTimeline() {
  for (size_t i = 0; i < timelines_.size(); i++)
    delete (timelines_.at(i));
}

const std::vector<Timeline*>& SegmentTimeline::GetTimelines() const {
  return timelines_;
}

} // namespace mpd
} // namespace dash
