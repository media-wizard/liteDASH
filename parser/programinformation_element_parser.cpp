/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "programinformation_element_parser.h"
#include "programinformation.h"


namespace dash {
namespace mpd {

bool ProgramInformationElementParser::ParseStart(
    const std::string &element_name, ElementBase *elem_out,
    const char **attrib) {
  ProgramInformation *elem = static_cast<ProgramInformation*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("lang") {
      elem->lang_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("moreInformationURL") {
      elem->more_information_url_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

bool ProgramInformationElementParser::ParseTextData(ElementBase *elem_out,
    const std::string sub_element, const char *content, int length) {
  ProgramInformation *elem = static_cast<ProgramInformation*>(elem_out);
  if (sub_element == "Title") {
    elem->title_.append(content, length);
  } else if (sub_element == "Source") {
    elem->source_.append(content, length);
  } else if (sub_element == "Copyright") {
    elem->copyright_.append(content, length);
  }
  return true;
}

ElementBase* ProgramInformationElementParser::CreateElement(
    const std::string &element) const {
  return new ProgramInformation();
}

ElementBaseParser* ProgramInformationElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "Title" || name == "Source" || name == "Copyright") {
    //These are trivial Subelements
    return this;
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }
  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
