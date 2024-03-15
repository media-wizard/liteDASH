/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "modelpair_element_parser.h"
#include "modelpair.h"


namespace dash {
namespace mpd {

bool ModelPairElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  ModelPair *elem = static_cast<ModelPair*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("bufferTime") {
      elem->buffer_time_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("bandwidth") {
      elem->band_width_ = strtoull(attrib[i + 1], NULL, 10);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* ModelPairElementParser::CreateElement(
    const std::string &element) const {
  return new ModelPair();
}

} // namespace mpd
} // namespace dash
