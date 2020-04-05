/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "latency_element_parser.h"
#include "latency.h"

#include "uintpairswithid_element_parser.h"
#include "uintpairswithid.h"


namespace dash {
namespace mpd {

bool LatencyElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  Latency *elem = static_cast<Latency*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("referenceId") {
      elem->reference_id_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("target") {
      elem->target_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("max") {
      elem->max_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("min") {
      elem->min_ = strtoul(attrib[i + 1], NULL, 10);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* LatencyElementParser::CreateElement(
    const std::string &element) const {
  return new Latency();
}

void LatencyElementParser::AttachChildElementToParent(ElementBase *parent,
    ElementBase *child) {
  Latency *elem = static_cast<Latency*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "QualityLatency") {
    elem->quality_latency_pairs_.push_back(
        static_cast<UIntPairsWithID*>(child));
  } else {
    ElementBaseParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* LatencyElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "QualityLatency") {
    parser = std::make_unique < UIntPairsWithIDElementParser > (name, parent);
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
