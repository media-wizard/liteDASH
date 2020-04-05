/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "elementbase_parser.h"
#include "elementbase.h"

#include <expat.h>
#include <stdio.h>
#include <string.h>

namespace dash {
namespace mpd {

ElementBaseParser::ElementBaseParser(const std::string &element_name,
    ElementBaseParser *parent) :
    element_name_(element_name), parent_(parent) {
}

ElementBaseParser::~ElementBaseParser() {
}

ElementBaseParser* ElementBaseParser::GetChildParser(const std::string &name,
    ElementBaseParser *parent) {
  const auto &child_pos = children_.find(name);
  if (child_pos != children_.end()) {
    return child_pos->second.get();
  }
  return CreateChildParser(name, parent);
}

void ElementBaseParser::InsertChildParser(const std::string &element_name,
    std::unique_ptr<ElementBaseParser> element_parser) {
  children_.emplace(element_name, std::move(element_parser));
}

ElementBaseParser* ElementBaseParser::GetParent() const {
  return parent_;
}

const std::string& ElementBaseParser::GetElementName() const {
  return element_name_;
}

bool ElementBaseParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  ElementBase *elem = static_cast<ElementBase*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    elem->raw_attribs_[attrib[i]] = attrib[i + 1];
  }
  return true;
}

bool ElementBaseParser::ParseTextData(ElementBase *elem_out,
    const std::string sub_element, const char *content, int length) {
  return true;
}
bool ElementBaseParser::ParseEnd(const std::string &element_name,
    ElementBase *elem_out) {
  return true;
}

ElementBase* ElementBaseParser::CreateElement(
    const std::string &element) const {
  return new ElementBase(element);
}

void ElementBaseParser::AttachChildElementToParent(ElementBase *parent,
    ElementBase *child) {
  parent->raw_child_elements_.emplace_back(child);
}

ElementBaseParser* ElementBaseParser::CreateChildParser(const std::string &name,
    ElementBaseParser *parent) {
  // Create parsers for the supported children under this node
  std::unique_ptr<ElementBaseParser> parser = std::make_unique
      < ElementBaseParser > (name, parent);
  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
