/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "resync_element_parser.h"
#include "resync.h"

#include "utils.h"


namespace dash {
namespace mpd {

bool ResyncElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  Resync *elem = static_cast<Resync*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("type") {
      elem->type_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("dT") {
      elem->dT_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("dImax") {
      elem->dIMax_ = strtof(attrib[i + 1], NULL);
    } else IF_ATTRIB_MATCHES("dImin") {
      elem->dIMin_ = strtof(attrib[i + 1], NULL);
    } else IF_ATTRIB_MATCHES("marker") {
      elem->marker_ = Utils::ConvertToBool(attrib[i + 1]);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* ResyncElementParser::CreateElement(
    const std::string &element) const {
  return new Resync();
}

} // namespace mpd
} // namespace dash
