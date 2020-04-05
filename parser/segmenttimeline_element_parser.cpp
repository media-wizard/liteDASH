/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "segmenttimeline_element_parser.h"
#include "segmenttimeline.h"

#include "timeline_element_parser.h"
#include "timeline.h"
#include "utils.h"


namespace dash {
namespace mpd {

ElementBase* SegmentTimelineElementParser::CreateElement(
    const std::string &element) const {
  return new SegmentTimeline();
}

void SegmentTimelineElementParser::AttachChildElementToParent(ElementBase *parent,
    ElementBase *child) {
  SegmentTimeline *elem = static_cast<SegmentTimeline*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "S") {
    elem->timelines_.push_back(static_cast<Timeline*>(child));
  } else {
    ElementBaseParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* SegmentTimelineElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "S") {
    parser = std::make_unique < TimelineElementParser > (name, parent);
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }
  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
