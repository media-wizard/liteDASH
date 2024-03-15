/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "segmentbase_element_parser.h"
#include "segmentbase.h"

#include "failovercontent_element_parser.h"
#include "failovercontent.h"
#include "urltype_element_parser.h"
#include "urltype.h"

#include "utils.h"


namespace dash {
namespace mpd {

bool SegmentBaseElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  SegmentBase *elem = static_cast<SegmentBase*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("timescale") {
      elem->timescale_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("eptDelta") {
      elem->ept_delta_ = (int) strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("pdDelta") {
      elem->pd_delta_ = (int) strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("presentationTimeOffset") {
      elem->presentation_time_offset_ = strtoull(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("presentationDuration") {
      elem->presentation_duration_ = strtoull(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("timeShiftBufferDepth") {
      elem->time_shift_buffer_depth_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("indexRange") {
      elem->index_range_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("indexRangeExact") {
      elem->index_range_exact_ = Utils::ConvertToBool(attrib[i + 1]);
    } else IF_ATTRIB_MATCHES("availabilityTimeOffset") {
      elem->availability_time_offset_ = strtod(attrib[i + 1], NULL);
    } else IF_ATTRIB_MATCHES("availabilityTimeComplete") {
      elem->availability_time_complete_ = Utils::ConvertToBool(attrib[i + 1]);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* SegmentBaseElementParser::CreateElement(
    const std::string &element) const {
  return new SegmentBase(element);
}

void SegmentBaseElementParser::AttachChildElementToParent(ElementBase *parent,
    ElementBase *child) {
  SegmentBase *elem = static_cast<SegmentBase*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "Initialization") {
    elem->initialization_ = static_cast<URLType*>(child);
  } else if (child_name == "RepresentationIndex") {
    elem->representation_index_ = static_cast<URLType*>(child);
  } else if (child_name == "FailoverContent") {
    elem->failover_content_ = static_cast<FailoverContent*>(child);
  } else {
    ElementBaseParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* SegmentBaseElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "Initialization" || name == "RepresentationIndex") {
    parser = std::make_unique < URLTypeElementParser > (name, parent);
  } else if (name == "FailoverContent") {
    parser = std::make_unique < FailoverContentElementParser > (name, parent);
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
