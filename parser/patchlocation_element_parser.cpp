/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "patchlocation_element_parser.h"
#include "patchlocation.h"


namespace dash {
namespace mpd {

bool PatchLocationElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  PatchLocation *elem = static_cast<PatchLocation*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("ttl") {
      elem->ttl_ = strtod(attrib[i + 1], NULL);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

bool PatchLocationElementParser::ParseTextData(ElementBase *elem_out,
    const std::string sub_element, const char *content, int length) {
  PatchLocation *elem = static_cast<PatchLocation*>(elem_out);
  elem->url_.append(content, length);
  return true;
}

bool PatchLocationElementParser::ParseEnd(const std::string &element_name,
    ElementBase *elem_out, const GetExternalAttributes &get_attribs) {
  PatchLocation *elem = static_cast<PatchLocation *>(elem_out);
  if (elem->url_ == "./") {
    elem->url_ = get_attribs("mpd_path");
  }
  return true;
}

ElementBase* PatchLocationElementParser::CreateElement(
    const std::string &element) const {
  return new PatchLocation();
}

} // namespace mpd
} // namespace dash
