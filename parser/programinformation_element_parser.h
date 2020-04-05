/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_PROGRAMINFORMATION_ELEMENT_PARSER_H_
#define DASH_PROGRAMINFORMATION_ELEMENT_PARSER_H_

#include "elementbase_parser.h"

namespace dash {
namespace mpd {

class ProgramInformationElementParser: public ElementBaseParser {
    using ElementBaseParser::ElementBaseParser;

  public:
    bool ParseStart(const std::string &element_name, ElementBase *elem_out,
        const char **attrib) override;
    bool ParseTextData(ElementBase *elem_out, const std::string sub_element,
        const char *content, int length) override;
    ElementBase* CreateElement(const std::string &element) const override;
    ElementBaseParser* CreateChildParser(const std::string &name,
        ElementBaseParser *parent) override;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_PROGRAMINFORMATION_ELEMENT_PARSER_H_ */
