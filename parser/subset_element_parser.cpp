/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "subset_element_parser.h"
#include "subset.h"

#include "utils.h"

namespace dash {
namespace mpd {

bool SubsetElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  Subset *elem = static_cast<Subset*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("contains") {
      Utils::SplitUIntValues(attrib[i + 1], ',', elem->contains_);
    } else IF_ATTRIB_MATCHES("id") {
      elem->id_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* SubsetElementParser::CreateElement(
    const std::string &element) const {
  return new Subset();
}

} // namespace mpd
} // namespace dash
