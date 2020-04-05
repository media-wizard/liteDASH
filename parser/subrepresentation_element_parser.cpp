/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "subrepresentation_element_parser.h"
#include "subrepresentation.h"

#include "utils.h"


namespace dash {
namespace mpd {

bool SubRepresentationElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  SubRepresentation *elem = static_cast<SubRepresentation*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("level") {
      elem->level_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("dependencyLevel") {
      Utils::SplitUIntValues(attrib[i + 1], ',', elem->dependency_level_);
    } else IF_ATTRIB_MATCHES("bandwidth") {
      elem->band_width_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("contentComponent") {
      Utils::SplitStrValues(attrib[i + 1], ',', elem->content_component_);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      RepresentationBaseElementParser::ParseStart(element_name, elem_out,
          tmp_attribs);
    }
  }
  return true;
}

ElementBase* SubRepresentationElementParser::CreateElement(
    const std::string &element) const {
  return new SubRepresentation();
}

} // namespace mpd
} // namespace dash
