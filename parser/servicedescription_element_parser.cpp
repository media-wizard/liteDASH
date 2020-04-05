/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "servicedescription_element_parser.h"
#include "servicedescription.h"

#include "descriptor.h"
#include "descriptor_element_parser.h"
#include "latency.h"
#include "latency_element_parser.h"
#include "playbackrate.h"
#include "playbackrate_element_parser.h"
#include "operatingquality.h"
#include "operatingquality_element_parser.h"
#include "operatingbandwidth.h"
#include "operatingbandwidth_element_parser.h"


namespace dash {
namespace mpd {

bool ServiceDescriptionElementParser::ParseStart(
    const std::string &element_name, ElementBase *elem_out,
    const char **attrib) {
  ServiceDescription *elem = static_cast<ServiceDescription*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("id") {
      elem->id_ = strtoul(attrib[i + 1], NULL, 10);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* ServiceDescriptionElementParser::CreateElement(
    const std::string &element) const {
  return new ServiceDescription();
}

void ServiceDescriptionElementParser::AttachChildElementToParent(
    ElementBase *parent, ElementBase *child) {
  ServiceDescription *sd_elem = static_cast<ServiceDescription*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "Scope") {
    sd_elem->scope_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "Latency") {
    sd_elem->latency_.push_back(static_cast<Latency*>(child));
  } else if (child_name == "PlaybackRate") {
    sd_elem->playback_rate_.push_back(static_cast<PlaybackRate*>(child));
  } else if (child_name == "OperatingQuality") {
    sd_elem->operating_quality_.push_back(
        static_cast<OperatingQuality*>(child));
  } else if (child_name == "OperatingBandwidth") {
    sd_elem->operating_bandwidth_.push_back(
        static_cast<OperatingBandwidth*>(child));
  } else {
    ElementBaseParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* ServiceDescriptionElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "Scope") {
    parser = std::make_unique < DescriptorElementParser > (name, parent);
  } else if (name == "Latency") {
    parser = std::make_unique < LatencyElementParser > (name, parent);
  } else if (name == "PlaybackRate") {
    parser = std::make_unique < PlaybackRateElementParser > (name, parent);
  } else if (name == "OperatingQuality") {
    parser = std::make_unique < OperatingQualityElementParser > (name, parent);
  } else if (name == "OperatingBandwidth") {
    parser = std::make_unique < OperatingBandwidthElementParser
        > (name, parent);
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
