/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "segmentlist_element_parser.h"
#include "segmentlist.h"

#include "segmenturl_element_parser.h"
#include "segmenturl.h"


namespace dash {
namespace mpd {

bool SegmentListElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  SegmentList *elem = static_cast<SegmentList*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("xlink:href") {
      elem->xlink_href_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("xlink:actuate") {
      elem->xlink_actuate_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("xlink:type") {
      elem->xlink_type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("xlink:show") {
      elem->xlink_show_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      MultipleSegmentBaseElementParser::ParseStart(element_name, elem_out,
          tmp_attribs);
    }
  }
  return true;
}

ElementBase* SegmentListElementParser::CreateElement(
    const std::string &element) const {
  return new SegmentList();
}

void SegmentListElementParser::AttachChildElementToParent(ElementBase *parent,
    ElementBase *child) {
  SegmentList *elem = static_cast<SegmentList*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "SegmentURL") {
    elem->segment_urls_.push_back(static_cast<SegmentURL*>(child));
  } else {
    MultipleSegmentBaseElementParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* SegmentListElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "SegmentURL") {
    parser = std::make_unique < SegmentURLElementParser > (name, parent);
  } else {
    return MultipleSegmentBaseElementParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
