/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "urltype_element_parser.h"
#include "urltype.h"


namespace dash {
namespace mpd {

bool URLTypeElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  URLType *elem = static_cast<URLType*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("sourceURL") {
      elem->source_url_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("range") {
      elem->range_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* URLTypeElementParser::CreateElement(
    const std::string &element) const {
  return new URLType(element);
}

} // namespace mpd
} // namespace dash
