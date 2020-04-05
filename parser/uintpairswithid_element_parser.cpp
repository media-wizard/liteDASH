/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "uintpairswithid_element_parser.h"
#include "uintpairswithid.h"
#include "utils.h"


namespace dash {
namespace mpd {

bool UIntPairsWithIDElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  UIntPairsWithID *elem = static_cast<UIntPairsWithID*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("type") {
      elem->type_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  tmp_str_.clear();
  return true;
}

bool UIntPairsWithIDElementParser::ParseTextData(ElementBase *elem_out,
    const std::string sub_element, const char *content, int length) {
  tmp_str_.append(content, length);
  return true;
}

bool UIntPairsWithIDElementParser::ParseEnd(const std::string &element_name,
    ElementBase *elem_out) {
  UIntPairsWithID *elem = static_cast<UIntPairsWithID*>(elem_out);
  std::vector < std::string > pairs;
  Utils::SplitStrValues(tmp_str_, ',', pairs);
  for (auto &pair : pairs) {
    std::vector < std::string > ql;
    Utils::SplitStrValues(pair, ' ', ql);
    UIntPairs *uint_pair = new UIntPairs(strtoul(ql[0].c_str(), NULL, 10),
        strtoul(ql[1].c_str(), NULL, 10));
    elem->ql_pairs_.push_back(uint_pair);
  }
  tmp_str_.clear();
  return true;
}

ElementBase* UIntPairsWithIDElementParser::CreateElement(
    const std::string &element) const {
  return new UIntPairsWithID(element);
}

} // namespace mpd
} // namespace dash
