/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_MULTIPLESEGMENTBASE_H_
#define DASH_MULTIPLESEGMENTBASE_H_

#include "segmentbase.h"

namespace dash {
namespace mpd {

class SegmentTimeline;
class URLType;

class MultipleSegmentBase: public SegmentBase {
  public:
    MultipleSegmentBase(const std::string &name);
    virtual ~MultipleSegmentBase();
    const SegmentTimeline* GetSegmentTimeline() const;
    const URLType* GetBitstreamSwitching() const;
    uint32_t GetDuration() const;
    uint32_t GetStartNumber() const;
    uint32_t GetEndNumber() const;

  private:
    SegmentTimeline *segment_timeline_;
    URLType *bitstream_switching_;
    uint32_t duration_;
    uint32_t start_number_;
    uint32_t end_number_;

    friend class MultipleSegmentBaseElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_MULTIPLESEGMENTBASE_H_ */
