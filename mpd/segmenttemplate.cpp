/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "segmenttemplate.h"

namespace dash {
namespace mpd {

SegmentTemplate::SegmentTemplate() :
    MultipleSegmentBase("SegmentTemplate"), media_(""), index_(""),
    initialization_(""), bitstream_switching_("") {
}

const std::string& SegmentTemplate::Getmedia() const {
  return media_;
}

const std::string& SegmentTemplate::Getindex() const {
  return index_;
}

const std::string& SegmentTemplate::Getinitialization() const {
  return initialization_;
}

const std::string& SegmentTemplate::GetbitstreamSwitching() const {
  return bitstream_switching_;
}

} // namespace mpd
} // namespace dash
