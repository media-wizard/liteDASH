/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "multiplesegmentbase.h"

#include "segmenttimeline.h"
#include "urltype.h"

namespace dash {
namespace mpd {

MultipleSegmentBase::MultipleSegmentBase(const std::string &name) :
    SegmentBase(name), bitstream_switching_(NULL), segment_timeline_(NULL),
    duration_(0), start_number_(1), end_number_(1) {
}

MultipleSegmentBase::~MultipleSegmentBase() {
  delete (segment_timeline_);
  delete (bitstream_switching_);
}

const SegmentTimeline* MultipleSegmentBase::GetSegmentTimeline() const {
  return segment_timeline_;
}

const URLType* MultipleSegmentBase::GetBitstreamSwitching() const {
  return bitstream_switching_;
}

uint32_t MultipleSegmentBase::GetDuration() const {
  return duration_;
}

uint32_t MultipleSegmentBase::GetStartNumber() const {
  return start_number_;
}

uint32_t MultipleSegmentBase::GetEndNumber() const {
  return end_number_;
}

} // namespace mpd
} // namespace dash
