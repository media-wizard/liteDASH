/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_SEGMENTTIMELINE_ELEMENT_PARSER_H_
#define DASH_SEGMENTTIMELINE_ELEMENT_PARSER_H_

#include "elementbase_parser.h"

namespace dash {
namespace mpd {

class SegmentTimelineElementParser: public ElementBaseParser {
    using ElementBaseParser::ElementBaseParser;

  public:
    ElementBase* CreateElement(const std::string &element) const override;
    void AttachChildElementToParent(ElementBase *parent,
                                             ElementBase *child) override;
    ElementBaseParser* CreateChildParser(const std::string &name,
        ElementBaseParser *parent) override;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_SEGMENTTIMELINE_ELEMENT_PARSER_H_ */
