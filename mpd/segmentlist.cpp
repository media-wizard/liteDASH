/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "segmentlist.h"
#include "segmenturl.h"

namespace dash {
namespace mpd {

SegmentList::SegmentList() :
    MultipleSegmentBase("SegmentList"), xlink_href_(""),
    xlink_actuate_("onRequest"), xlink_type_("simple"), xlink_show_("embed") {
}

SegmentList::~SegmentList() {
  for (size_t i = 0; i < segment_urls_.size(); i++)
    delete (segment_urls_.at(i));
}

const std::vector<SegmentURL*>& SegmentList::GetSegmentURLs() const {
  return segment_urls_;
}

const std::string& SegmentList::GetXlinkHref() const {
  return xlink_href_;
}

const std::string& SegmentList::GetXlinkActuate() const {
  return xlink_actuate_;
}

const std::string& SegmentList::GetXlinkType() const {
  return xlink_type_;
}

const std::string& SegmentList::GetXlinkShow() const {
  return xlink_show_;
}

} // namespace mpd
} // namespace dash
