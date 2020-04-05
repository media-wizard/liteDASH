/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "operatingbandwidth_element_parser.h"
#include "operatingbandwidth.h"


namespace dash {
namespace mpd {

bool OperatingBandwidthElementParser::ParseStart(
    const std::string &element_name, ElementBase *elem_out,
    const char **attrib) {
  OperatingBandwidth *elem = static_cast<OperatingBandwidth*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("mediaType") {
      elem->media_type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("max") {
      elem->max_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("min") {
      elem->min_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("target") {
      elem->target_ = strtoul(attrib[i + 1], NULL, 10);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* OperatingBandwidthElementParser::CreateElement(
    const std::string &element) const {
  return new OperatingBandwidth();
}

} // namespace mpd
} // namespace dash
