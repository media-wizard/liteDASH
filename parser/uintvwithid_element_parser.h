/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_UINTWITHID_ELEMENT_PARSER_H_
#define DASH_UINTWITHID_ELEMENT_PARSER_H_

#include "elementbase_parser.h"

namespace dash {
namespace mpd {

class UIntVWithIDElementParser: public ElementBaseParser {
    using ElementBaseParser::ElementBaseParser;

  public:
    bool ParseStart(const std::string &element_name, ElementBase *elem_out,
        const char **attrib) override;
    bool ParseTextData(ElementBase *elem_out, const std::string sub_element,
        const char *content, int length);
    bool ParseEnd(const std::string &element_name, ElementBase *elem_out)
        override;
    ElementBase* CreateElement(const std::string &element) const override;

  private:
    std::string list_str_;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_UINTWITHID_ELEMENT_PARSER_H_ */
