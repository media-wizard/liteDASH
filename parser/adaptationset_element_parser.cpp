/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "adaptationset_element_parser.h"
#include "adaptationset.h"

#include "baseurl_element_parser.h"
#include "baseurl.h"
#include "contentcomponent_element_parser.h"
#include "contentcomponent.h"
#include "descriptor_element_parser.h"
#include "descriptor.h"
#include "representation_element_parser.h"
#include "representation.h"
#include "segmentbase_element_parser.h"
#include "segmentbase.h"
#include "segmentlist_element_parser.h"
#include "segmentlist.h"
#include "segmenttemplate_element_parser.h"
#include "segmenttemplate.h"
#include "utils.h"


namespace dash {
namespace mpd {

bool AdaptationSetElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  AdaptationSet *elem = static_cast<AdaptationSet*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("xlink:href") {
      elem->xlink_href_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("xlink:actuate") {
      elem->xlink_actuate_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("xlink:type") {
      elem->xlink_type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("xlink:show") {
      elem->xlink_show_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("id") {
      elem->id_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("group") {
      elem->group_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("lang") {
      elem->lang_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("contentType") {
      elem->content_type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("par") {
      elem->par_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("minBandwidth") {
      elem->min_bandwidth_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("maxBandwidth") {
      elem->max_bandwidth_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("minWidth") {
      elem->min_width_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("maxWidth") {
      elem->max_width_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("minHeight") {
      elem->min_height_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("maxHeight") {
      elem->max_height_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("minFrameRate") {
      elem->min_framerate_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("maxFrameRate") {
      elem->max_framerate_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("segmentAlignment") {
      elem->segment_alignment_ = Utils::ConvertToBool(attrib[i + 1]);
    } else IF_ATTRIB_MATCHES("subsegmentAlignment") {
      elem->subsegment_alignment_ = Utils::ConvertToBool(attrib[i + 1]);
    } else IF_ATTRIB_MATCHES("subsegmentStartsWithSAP") {
      elem->subsegment_starts_with_SAP_ = (uint8_t) strtoul(attrib[i + 1], NULL,
          10);
    } else IF_ATTRIB_MATCHES("bitstreamSwitching") {
      elem->is_bitstream_switching_ = Utils::ConvertToBool(attrib[i + 1]);
    } else IF_ATTRIB_MATCHES("initializationSetRef") {
      Utils::SplitUIntValues(attrib[i + 1], ',', elem->initialization_set_Ref_);
    } else IF_ATTRIB_MATCHES("initializationPrincipal") {
      elem->initialization_principal_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      RepresentationBaseElementParser::ParseStart(element_name, elem_out,
          tmp_attribs);
    }
  }
  return true;
}

ElementBase* AdaptationSetElementParser::CreateElement(
    const std::string &element) const {
  return new AdaptationSet();
}

void AdaptationSetElementParser::AttachChildElementToParent(ElementBase *parent,
    ElementBase *child) {
  AdaptationSet *as_elem = static_cast<AdaptationSet*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "Representation") {
    as_elem->representation_.push_back(static_cast<Representation*>(child));
  } else if (child_name == "BaseURL") {
    as_elem->base_urls_.push_back(static_cast<BaseUrl*>(child));
  } else if (child_name == "ContentComponent") {
    as_elem->content_component_.push_back(
        static_cast<ContentComponent*>(child));
  } else if (child_name == "SegmentBase") {
    as_elem->segment_base_ = static_cast<SegmentBase*>(child);
  } else if (child_name == "SegmentList") {
    as_elem->segment_list_ = static_cast<SegmentList*>(child);
  } else if (child_name == "SegmentTemplate") {
    as_elem->segment_template_ = static_cast<SegmentTemplate*>(child);
  } else if (child_name == "Accessibility") {
    as_elem->accessibility_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "Role") {
    as_elem->role_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "Rating") {
    as_elem->rating_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "Viewpoint") {
    as_elem->viewpoint_.push_back(static_cast<Descriptor*>(child));
  } else {
    RepresentationBaseElementParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* AdaptationSetElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "Representation") {
    parser = std::make_unique < RepresentationElementParser > (name, parent);
  } else if (name == "BaseURL") {
    parser = std::make_unique < BaseURLElementParser > (name, parent);
  } else if (name == "ContentComponent") {
    parser = std::make_unique < ContentComponentElementParser > (name, parent);
  } else if (name == "SegmentBase") {
    parser = std::make_unique < SegmentBaseElementParser > (name, parent);
  } else if (name == "SegmentList") {
    parser = std::make_unique < SegmentListElementParser > (name, parent);
  } else if (name == "SegmentTemplate") {
    parser = std::make_unique < SegmentTemplateElementParser > (name, parent);
  } else if (name == "Accessibility" || name == "Role" || name == "Rating"
      || name == "Viewpoint") {
    parser = std::make_unique < DescriptorElementParser > (name, parent);
  } else {
    return RepresentationBaseElementParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
