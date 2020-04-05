/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "contentpopularityrate_element_parser.h"
#include "contentpopularityrate.h"

#include "popularityrate_element_parser.h"
#include "popularityrate.h"

#include "utils.h"


namespace dash {
namespace mpd {

bool ContentPopularityRateElementParser::ParseStart(
    const std::string &element_name, ElementBase *elem_out,
    const char **attrib) {
  ContentPopularityRate *elem = static_cast<ContentPopularityRate*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("source") {
      elem->source_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("source_description") {
      elem->source_description_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* ContentPopularityRateElementParser::CreateElement(
    const std::string &element) const {
  return new ContentPopularityRate();
}

void ContentPopularityRateElementParser::AttachChildElementToParent(
    ElementBase *parent, ElementBase *child) {
  ContentPopularityRate *elem = static_cast<ContentPopularityRate*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "PR") {
    elem->popularity_rates_.push_back(static_cast<PopularityRate*>(child));
  } else {
    ElementBaseParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* ContentPopularityRateElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser;
  if (name == "PR") {
    parser = std::make_unique < PopularityRateElementParser > (name, parent);
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
