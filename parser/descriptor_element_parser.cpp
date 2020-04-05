/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "descriptor_element_parser.h"
#include "descriptor.h"


namespace dash {
namespace mpd {

bool DescriptorElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  Descriptor *elem = static_cast<Descriptor*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("schemeIdUri") {
      elem->scheme_id_uri_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("value") {
      elem->value_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("id") {
      elem->id_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* DescriptorElementParser::CreateElement(
    const std::string &element) const {
  return new Descriptor(element);
}

} // namespace mpd
} // namespace dash
