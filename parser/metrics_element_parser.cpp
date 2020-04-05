/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "metrics_element_parser.h"
#include "metrics.h"

#include "descriptor.h"
#include "descriptor_element_parser.h"
#include "range.h"
#include "range_element_parser.h"


namespace dash {
namespace mpd {

bool MetricsElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  Metrics *elem = static_cast<Metrics*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("metrics") {
      elem->metrics_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* MetricsElementParser::CreateElement(
    const std::string &element) const {
  return new Metrics();
}

void MetricsElementParser::AttachChildElementToParent(ElementBase *parent,
    ElementBase *child) {
  Metrics *metrics_elem = static_cast<Metrics*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "Range") {
    metrics_elem->ranges_.push_back(static_cast<Range*>(child));
  } else if (child_name == "Reporting") {
    metrics_elem->reportings_.push_back(static_cast<Descriptor*>(child));
  } else {
    ElementBaseParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* MetricsElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "Range") {
    parser = std::make_unique < RangeElementParser > (name, parent);
  } else if (name == "Reporting") {
    parser = std::make_unique < DescriptorElementParser > (name, parent);
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
