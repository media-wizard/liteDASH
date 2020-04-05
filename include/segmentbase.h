/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_SEGMENTBASE_H_
#define DASH_SEGMENTBASE_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class URLType;
class FailoverContent;

class SegmentBase: public ElementBase {
  public:
    SegmentBase(const std::string &name);
    virtual ~SegmentBase();
    const URLType* GetInitialization() const;
    const URLType* GetRepresentationIndex() const;
    const FailoverContent* GetFailoverContent() const;
    uint32_t GetTimescale() const;
    int GetEptDelta() const;
    int GetPdDelta() const;
    uint64_t GetPresentationTimeOffset() const;
    uint64_t GetPresentationDuration() const;
    const std::string& GetTimeShiftBufferDepth() const;
    const std::string& GetIndexRange() const;
    bool HasIndexRangeExact() const;
    double GetAvailabilityTimeOffset() const;
    bool IsAvailabilityTimeComplete() const;

  private:
    URLType *initialization_;
    URLType *representation_index_;
    FailoverContent *failover_content_;
    uint32_t timescale_;
    int ept_delta_;
    int pd_delta_;
    uint64_t presentation_time_offset_;
    uint64_t presentation_duration_;
    std::string time_shift_buffer_depth_;
    std::string index_range_;
    bool index_range_exact_;
    double availability_time_offset_;
    bool availability_time_complete_;

    friend class SegmentBaseElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_SEGMENTBASE_H_ */
