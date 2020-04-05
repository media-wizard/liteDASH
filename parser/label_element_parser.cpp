/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "label_element_parser.h"
#include "label.h"


namespace dash {
namespace mpd {

bool LabelElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  Label *elem = static_cast<Label*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("id") {
      elem->id_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("lang") {
      elem->lang_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* LabelElementParser::CreateElement(
    const std::string &element) const {
  return new Label();
}

} // namespace mpd
} // namespace dash
