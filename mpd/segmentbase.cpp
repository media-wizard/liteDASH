/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "segmentbase.h"

#include "failovercontent.h"
#include "urltype.h"

namespace dash {
namespace mpd {

SegmentBase::SegmentBase(const std::string &name) :
    ElementBase(name), initialization_(NULL), representation_index_(NULL),
    failover_content_(NULL), timescale_(1), ept_delta_(0), pd_delta_(0),
    presentation_time_offset_(0), index_range_(""), index_range_exact_(false),
    availability_time_offset_(0.0) {
}
SegmentBase::~SegmentBase() {
  delete (initialization_);
  delete (representation_index_);
}

const URLType* SegmentBase::GetInitialization() const {
  return initialization_;
}

const URLType* SegmentBase::GetRepresentationIndex() const {
  return representation_index_;
}

const FailoverContent* SegmentBase::GetFailoverContent() const {
  return failover_content_;
}

uint32_t SegmentBase::GetTimescale() const {
  return timescale_;
}

int SegmentBase::GetEptDelta() const {
  return ept_delta_;
}

int SegmentBase::GetPdDelta() const {
  return pd_delta_;
}

uint64_t SegmentBase::GetPresentationTimeOffset() const {
  return presentation_time_offset_;
}

uint64_t SegmentBase::GetPresentationDuration() const {
  return presentation_duration_;
}

const std::string& SegmentBase::GetTimeShiftBufferDepth() const {
  return time_shift_buffer_depth_;
}

const std::string& SegmentBase::GetIndexRange() const {
  return index_range_;
}

bool SegmentBase::HasIndexRangeExact() const {
  return index_range_exact_;
}

double SegmentBase::GetAvailabilityTimeOffset() const {
  return availability_time_offset_;
}

bool SegmentBase::IsAvailabilityTimeComplete() const {
  return availability_time_complete_;
}

} // namespace mpd
} // namespace dash
