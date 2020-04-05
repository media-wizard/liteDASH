/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "multiplesegmentbase_element_parser.h"
#include "multiplesegmentbase.h"

#include "segmenttimeline_element_parser.h"
#include "segmenttimeline.h"
#include "urltype_element_parser.h"
#include "urltype.h"


namespace dash {
namespace mpd {

bool MultipleSegmentBaseElementParser::ParseStart(
    const std::string &element_name, ElementBase *elem_out,
    const char **attrib) {
  MultipleSegmentBase *elem = static_cast<MultipleSegmentBase*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("duration") {
      elem->duration_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("startNumber") {
      elem->start_number_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("endNumber") {
      elem->end_number_ = strtoul(attrib[i + 1], NULL, 10);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      SegmentBaseElementParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

void MultipleSegmentBaseElementParser::AttachChildElementToParent(
    ElementBase *parent, ElementBase *child) {
  MultipleSegmentBase *elem = static_cast<MultipleSegmentBase*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "SegmentTimeline") {
    elem->segment_timeline_ = static_cast<SegmentTimeline*>(child);
  } else if (child_name == "BitstreamSwitching") {
    elem->bitstream_switching_ = static_cast<URLType*>(child);
  } else {
    SegmentBaseElementParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* MultipleSegmentBaseElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "SegmentTimeline") {
    parser = std::make_unique < SegmentTimelineElementParser > (name, parent);
  } else if (name == "BitstreamSwitching") {
    parser = std::make_unique < URLTypeElementParser > (name, parent);
  } else {
    return SegmentBaseElementParser::CreateChildParser(name, parent);
  }
  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
