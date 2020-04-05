/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "operatingquality_element_parser.h"
#include "operatingquality.h"


namespace dash {
namespace mpd {

bool OperatingQualityElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  OperatingQuality *elem = static_cast<OperatingQuality*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("mediaType") {
      elem->media_type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("max") {
      elem->max_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("min") {
      elem->min_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("target") {
      elem->target_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("type") {
      elem->type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("maxDifference") {
      elem->max_difference_ = strtoul(attrib[i + 1], NULL, 10);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* OperatingQualityElementParser::CreateElement(
    const std::string &element) const {
  return new OperatingQuality();
}

} // namespace mpd
} // namespace dash
