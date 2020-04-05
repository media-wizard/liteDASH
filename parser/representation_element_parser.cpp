/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "representation_element_parser.h"
#include "representation.h"

#include "baseurl_element_parser.h"
#include "baseurl.h"
#include "extendedbandwidth_element_parser.h"
#include "extendedbandwidth.h"
#include "segmentbase_element_parser.h"
#include "segmentbase.h"
#include "segmentlist_element_parser.h"
#include "segmentlist.h"
#include "segmenttemplate_element_parser.h"
#include "segmenttemplate.h"
#include "segmenturl_element_parser.h"
#include "segmenturl.h"
#include "subrepresentation_element_parser.h"
#include "subrepresentation.h"

#include "utils.h"


namespace dash {
namespace mpd {

bool RepresentationElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  Representation *elem = static_cast<Representation*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("id") {
      elem->id_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("bandwidth") {
      elem->bandwidth_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("qualityRanking") {
      elem->quality_ranking_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("dependencyId") {
      Utils::SplitStrValues(attrib[i + 1], ',', elem->dependency_id_);
    } else IF_ATTRIB_MATCHES("associationId") {
      Utils::SplitStrValues(attrib[i + 1], ',', elem->association_id_);
    } else IF_ATTRIB_MATCHES("associationType") {
      elem->association_type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("mediaStreamStructureId") {
      Utils::SplitStrValues(attrib[i + 1], ',',
          elem->media_stream_structureId_);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      RepresentationBaseElementParser::ParseStart(element_name, elem_out,
          tmp_attribs);
    }
  }
  return true;
}

ElementBase* RepresentationElementParser::CreateElement(
    const std::string &element) const {
  return new Representation();
}

void RepresentationElementParser::AttachChildElementToParent(
    ElementBase *parent, ElementBase *child) {
  Representation *rep_elem = static_cast<Representation*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "BaseURL") {
    rep_elem->base_urls_.push_back(static_cast<BaseUrl*>(child));
  } else if (child_name == "ExtendedBandwidth") {
    rep_elem->extended_bandwidths_.push_back(
        static_cast<ExtendedBandwidth*>(child));
  } else if (child_name == "SubRepresentation") {
    rep_elem->sub_representations_.push_back(
        static_cast<SubRepresentation*>(child));
  } else if (child_name == "SegmentBase") {
    rep_elem->segment_base_ = static_cast<SegmentBase*>(child);
  } else if (child_name == "SegmentList") {
    rep_elem->segment_list_ = static_cast<SegmentList*>(child);
  } else if (child_name == "SegmentTemplate") {
    rep_elem->segment_template_ = static_cast<SegmentTemplate*>(child);
  } else {
    RepresentationBaseElementParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* RepresentationElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "BaseURL") {
    parser = std::make_unique < BaseURLElementParser > (name, parent);
  } else if (name == "ExtendedBandwidth") {
    parser = std::make_unique < ExtendedBandwidthElementParser > (name, parent);
  } else if (name == "SubRepresentation") {
    parser = std::make_unique < SubRepresentationElementParser > (name, parent);
  } else if (name == "SegmentBase") {
    parser = std::make_unique < SegmentBaseElementParser > (name, parent);
  } else if (name == "SegmentList") {
    parser = std::make_unique < SegmentListElementParser > (name, parent);
  } else if (name == "SegmentTemplate") {
    parser = std::make_unique < SegmentTemplateElementParser > (name, parent);
  } else {
    return RepresentationBaseElementParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
