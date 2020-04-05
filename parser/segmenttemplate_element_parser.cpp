/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "segmenttemplate_element_parser.h"
#include "segmenttemplate.h"


namespace dash {
namespace mpd {

bool SegmentTemplateElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  SegmentTemplate *elem = static_cast<SegmentTemplate*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("media") {
      elem->media_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("index") {
      elem->index_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("initialization") {
      elem->initialization_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("bitstreamSwitching") {
      elem->bitstream_switching_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      MultipleSegmentBaseElementParser::ParseStart(element_name, elem_out,
          tmp_attribs);
    }
  }
  return true;
}

ElementBase* SegmentTemplateElementParser::CreateElement(
    const std::string &element) const {
  return new SegmentTemplate();
}

} // namespace mpd
} // namespace dash
