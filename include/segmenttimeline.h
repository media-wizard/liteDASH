/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_SEGMENTTIMELINE_H_
#define DASH_SEGMENTTIMELINE_H_

#include <vector>

#include "elementbase.h"

namespace dash {
namespace mpd {

class Timeline;

class SegmentTimeline: public ElementBase {
  public:
    SegmentTimeline();
    ~SegmentTimeline();
    const std::vector<Timeline*>& GetTimelines() const;

  private:
    std::vector<Timeline*> timelines_;

    friend class SegmentTimelineElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_SEGMENTTIMELINE_H_ */
