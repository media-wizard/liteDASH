/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "segmenturl_element_parser.h"
#include "segmenturl.h"


namespace dash {
namespace mpd {

bool SegmentURLElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  SegmentURL *elem = static_cast<SegmentURL*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("media") {
      elem->media_URI_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("mediaRange") {
      elem->media_range_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("index") {
      elem->index_URI_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("indexRange") {
      elem->index_range_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* SegmentURLElementParser::CreateElement(
    const std::string &element) const {
  return new SegmentURL();
}

} // namespace mpd
} // namespace dash
