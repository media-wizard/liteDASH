/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "eventstream_element_parser.h"
#include "eventstream.h"

#include "event_element_parser.h"
#include "event.h"


namespace dash {
namespace mpd {

bool EventStreamElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  EventStream *elem = static_cast<EventStream*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("xlink:href") {
      elem->xlink_href_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("xlink:actuate") {
      elem->xlink_actuate_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("schemeIdUri") {
      elem->scheme_id_uri_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("value") {
      elem->value_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("timescale") {
      elem->timescale_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("presentationTimeOffset") {
      elem->presentation_time_offset_ = strtoull(attrib[i + 1], NULL, 10);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* EventStreamElementParser::CreateElement(
    const std::string &element) const {
  return new EventStream(element);
}

void EventStreamElementParser::AttachChildElementToParent(ElementBase *parent,
    ElementBase *child) {
  EventStream *es_elem = static_cast<EventStream*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "Event") {
    es_elem->events_.push_back(static_cast<Event*>(child));
  } else {
    ElementBaseParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* EventStreamElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "Event") {
    parser = std::make_unique < EventElementParser > (name, parent);
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
