/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "timeline_element_parser.h"
#include "timeline.h"


namespace dash {
namespace mpd {

bool TimelineElementParser::ParseStart(const std::string &element_name,
                            ElementBase *elem_out, const char **attrib) {
  Timeline *timeline = static_cast<Timeline*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("t") {
      timeline->t_ = strtoull(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("d") {
      timeline->d_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("r") {
      timeline->r_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("n") {
      timeline->n_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("k") {
      timeline->k_ = strtoul(attrib[i + 1], NULL, 10);
    }
  }
  return true;
}

ElementBase* TimelineElementParser::CreateElement(
    const std::string &element) const {
  return new Timeline();
}

} // namespace mpd
} // namespace dash
