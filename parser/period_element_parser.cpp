/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "period_element_parser.h"
#include "period.h"

#include "adaptationset_element_parser.h"
#include "adaptationset.h"
#include "baseurl.h"
#include "baseurl_element_parser.h"
#include "contentprotection.h"
#include "contentprotection_element_parser.h"
#include "descriptor.h"
#include "descriptor_element_parser.h"
#include "eventstream.h"
#include "eventstream_element_parser.h"
#include "label.h"
#include "label_element_parser.h"
#include "preselection_element_parser.h"
#include "preselection.h"
#include "segmentbase.h"
#include "segmentbase_element_parser.h"
#include "segmentlist.h"
#include "segmentlist_element_parser.h"
#include "segmenttemplate.h"
#include "segmenttemplate_element_parser.h"
#include "servicedescription.h"
#include "servicedescription_element_parser.h"
#include "subset_element_parser.h"
#include "subset.h"

#include "utils.h"

namespace dash {
namespace mpd {

bool PeriodElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  Period *elem = static_cast<Period*>(elem_out);
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
      elem->id_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("start") {
      elem->start_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("duration") {
      elem->duration_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("bitstreamSwitching") {
      elem->is_bitstream_switching_ = Utils::ConvertToBool(attrib[i + 1]);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* PeriodElementParser::CreateElement(
    const std::string &element) const {
  return new Period();
}

void PeriodElementParser::AttachChildElementToParent(ElementBase *parent,
    ElementBase *child) {
  Period *period_elem = static_cast<Period*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "BaseURL") {
    period_elem->base_urls_.push_back(static_cast<BaseUrl*>(child));
  } else if (child_name == "SegmentBase") {
    period_elem->segment_base_ = static_cast<SegmentBase*>(child);
  } else if (child_name == "SegmentList") {
    period_elem->segment_list_ = static_cast<SegmentList*>(child);
  } else if (child_name == "SegmentTemplate") {
    period_elem->segment_template_ = static_cast<SegmentTemplate*>(child);
  } else if (child_name == "AssetIdentifier") {
    period_elem->asset_identifier_ = static_cast<Descriptor*>(child);
  } else if (child_name == "EventStream") {
    period_elem->event_streams_.push_back(static_cast<EventStream*>(child));
  } else if (child_name == "ServiceDescription") {
    period_elem->service_descriptions_.push_back(
        static_cast<ServiceDescription*>(child));
  } else if (child_name == "ContentProtection") {
    period_elem->content_protections_.push_back(
        static_cast<ContentProtection*>(child));
  } else if (child_name == "AdaptationSet") {
    period_elem->adaptation_sets_.push_back(static_cast<AdaptationSet*>(child));
  } else if (child_name == "Subset") {
    period_elem->subsets_.push_back(static_cast<Subset*>(child));
  } else if (child_name == "SupplementalProperty") {
    period_elem->supplemental_properties_.push_back(
        static_cast<Descriptor*>(child));
  } else if (child_name == "EmptyAdaptationSet") {
    period_elem->empty_adaptation_sets_.push_back(
        static_cast<AdaptationSet*>(child));
  } else if (child_name == "GroupLabel") {
    period_elem->group_labels_.push_back(static_cast<Label*>(child));
  } else if (child_name == "Preselection") {
    period_elem->preselections_.push_back(static_cast<Preselection*>(child));
  } else {
    ElementBaseParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* PeriodElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  // Create parsers for the supported children under this node
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "AdaptationSet") {
    parser = std::make_unique < AdaptationSetElementParser > (name, parent);
  } else if (name == "BaseURL") {
    parser = std::make_unique < BaseURLElementParser > (name, parent);
  } else if (name == "EventStream") {
    parser = std::make_unique < EventStreamElementParser > (name, parent);
  } else if (name == "SegmentBase") {
    parser = std::make_unique < SegmentBaseElementParser > (name, parent);
  } else if (name == "SegmentTemplate") {
    parser = std::make_unique < SegmentTemplateElementParser > (name, parent);
  } else if (name == "SegmentList") {
    parser = std::make_unique < SegmentListElementParser > (name, parent);
  } else if (name == "AssetIdentifier" || name == "SupplementalProperty") {
    parser = std::make_unique < DescriptorElementParser > (name, parent);
  } else if (name == "ServiceDescription") {
    parser = std::make_unique < ServiceDescriptionElementParser
        > (name, parent);
  } else if (name == "ContentProtection") {
    parser = std::make_unique < ContentProtectionElementParser > (name, parent);
  } else if (name == "Subset") {
    parser = std::make_unique < SubsetElementParser > (name, parent);
  } else if (name == "EmptyAdaptationSet") {
    parser = std::make_unique < AdaptationSetElementParser > (name, parent);
  } else if (name == "GroupLabel") {
    parser = std::make_unique < LabelElementParser > (name, parent);
  } else if (name == "Preselection") {
    parser = std::make_unique < PreselectionElementParser > (name, parent);
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
