/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "fcs_element_parser.h"
#include "fcs.h"

#include "utils.h"


namespace dash {
namespace mpd {

bool FCSElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  FCS *elem = static_cast<FCS*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("t") {
      elem->presentation_time_ = strtoull(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("d") {
      elem->duration_ = strtoull(attrib[i + 1], NULL, 10);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* FCSElementParser::CreateElement(const std::string &element) const {
  return new FCS();
}

} // namespace mpd
} // namespace dash
