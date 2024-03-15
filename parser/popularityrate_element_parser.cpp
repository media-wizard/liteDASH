/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "popularityrate_element_parser.h"
#include "popularityrate.h"

#include "utils.h"


namespace dash {
namespace mpd {

bool PopularityRateElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  PopularityRate *elem = static_cast<PopularityRate*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("popularityRate") {
      elem->popularity_rate_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("start") {
      elem->start_ = strtoull(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("r") {
      elem->r_ = strtoul(attrib[i + 1], NULL, 10);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* PopularityRateElementParser::CreateElement(
    const std::string &element) const {
  return new PopularityRate();
}

} // namespace mpd
} // namespace dash
