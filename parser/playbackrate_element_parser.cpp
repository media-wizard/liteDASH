/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "playbackrate_element_parser.h"
#include "playbackrate.h"


namespace dash {
namespace mpd {

bool PlaybackRateElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  PlaybackRate *elem = static_cast<PlaybackRate*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("max") {
      elem->max_ = strtod(attrib[i + 1], NULL);
    } else IF_ATTRIB_MATCHES("min") {
      elem->min_ = strtod(attrib[i + 1], NULL);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* PlaybackRateElementParser::CreateElement(
    const std::string &element) const {
  return new PlaybackRate();
}

} // namespace mpd
} // namespace dash
