/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "range_element_parser.h"
#include "range.h"


namespace dash {
namespace mpd {

bool RangeElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  Range *elem = static_cast<Range*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("starttime") {
      elem->start_time_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("duration") {
      elem->duration_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* RangeElementParser::CreateElement(
    const std::string &element) const {
  return new Range();
}

} // namespace mpd
} // namespace dash
