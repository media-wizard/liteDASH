/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "uintvwithid_element_parser.h"
#include "uintvwithid.h"

#include "utils.h"


namespace dash {
namespace mpd {

bool UIntVWithIDElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  UIntVWithID *elem = static_cast<UIntVWithID*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("id") {
      elem->id_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("profiles") {
      Utils::SplitStrValues(attrib[i + 1], ',', elem->profiles_);
    } else IF_ATTRIB_MATCHES("contentType") {
      elem->content_type_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  list_str_.clear();
  return true;
}

bool UIntVWithIDElementParser::ParseTextData(ElementBase *elem_out,
    const std::string sub_element, const char *content, int length) {
  list_str_.append(content, length);
  return true;
}

bool UIntVWithIDElementParser::ParseEnd(const std::string &element_name,
    ElementBase *elem_out) {
  UIntVWithID *elem = static_cast<UIntVWithID*>(elem_out);
  Utils::SplitUIntValues(list_str_, ',', elem->list_);
  list_str_.clear();
  return true;
}

ElementBase* UIntVWithIDElementParser::CreateElement(
    const std::string &element) const {
  return new UIntVWithID(element);
}

} // namespace mpd
} // namespace dash
