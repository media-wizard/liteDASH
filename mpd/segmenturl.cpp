/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "segmenturl.h"

namespace dash {
namespace mpd {

SegmentURL::SegmentURL() :
    ElementBase("SegmentURL"), media_URI_(""), media_range_(""), index_URI_(""),
    index_range_("") {
}

const std::string& SegmentURL::GetMediaURI() const {
  return media_URI_;
}

const std::string& SegmentURL::GetMediaRange() const {
  return media_range_;
}

const std::string& SegmentURL::GetIndexURI() const {
  return index_URI_;
}

const std::string& SegmentURL::GetIndexRange() const {
  return index_range_;
}


} // namespace mpd
} // namespace dash
