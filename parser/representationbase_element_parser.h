/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_REPRESENTATIONBAE_PARSER_H_
#define DASH_REPRESENTATIONBAE_PARSER_H_

#include "elementbase_parser.h"

#include <memory>
#include <string>

namespace dash {
namespace mpd {

class RepresentationBaseElementParser: public virtual ElementBaseParser {
    using ElementBaseParser::ElementBaseParser;
  public:
    bool ParseStart(const std::string &element_name, ElementBase *elem_out,
        const char **attrib);
    void AttachChildElementToParent(ElementBase *parent, ElementBase *child)
        override;
    ElementBaseParser* CreateChildParser(const std::string &name,
        ElementBaseParser *parent) override;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_REPRESENTATIONBAE_PARSER_H_ */
