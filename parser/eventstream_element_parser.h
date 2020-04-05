/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_EVENTSTREAM_ELEMENT_PARSER_H_
#define DASH_EVENTSTREAM_ELEMENT_PARSER_H_

#include "elementbase_parser.h"

namespace dash {
namespace mpd {

class EventStreamElementParser: public ElementBaseParser {
    using ElementBaseParser::ElementBaseParser;

  public:
    bool ParseStart(const std::string &element_name, ElementBase *elem_out,
        const char **attrib) override;
    ElementBase* CreateElement(const std::string &element) const override;
    void AttachChildElementToParent(ElementBase *parent, ElementBase *child)
        override;
    ElementBaseParser* CreateChildParser(const std::string &name,
        ElementBaseParser *parent) override;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_EVENTSTREAM_ELEMENT_PARSER_H_ */
