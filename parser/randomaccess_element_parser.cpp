/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "randomaccess_element_parser.h"
#include "randomaccess.h"


namespace dash {
namespace mpd {

bool RandomAccessElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  RandomAccess *elem = static_cast<RandomAccess*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("interval") {
      elem->interval_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("type") {
      elem->type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("minBufferTime") {
      elem->min_buffer_time_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("bandwidth") {
      elem->bandwidth_ = strtoul(attrib[i + 1], NULL, 10);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* RandomAccessElementParser::CreateElement(
    const std::string &element) const {
  return new RandomAccess();
}

} // namespace mpd
} // namespace dash
