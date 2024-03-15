/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "event_element_parser.h"
#include "event.h"


namespace dash {
namespace mpd {

bool EventElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  Event *elem = static_cast<Event*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("presentationTime") {
      elem->presentation_time_ = strtoull(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("duration") {
      elem->duration_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("id") {
      elem->id_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("contentEncoding") {
      elem->content_encoding_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("messageData") {
      elem->message_data_ = strtoul(attrib[i + 1], NULL, 10);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* EventElementParser::CreateElement(
    const std::string &element) const {
  return new Event();
}

} // namespace mpd
} // namespace dash
