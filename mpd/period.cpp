/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "period.h"

#include "adaptationset.h"
#include "baseurl.h"
#include "contentprotection.h"
#include "eventstream.h"
#include "descriptor.h"
#include "label.h"
#include "preselection.h"
#include "segmentbase.h"
#include "segmentlist.h"
#include "segmenttemplate.h"
#include "servicedescription.h"
#include "subset.h"

namespace dash {
namespace mpd {

Period::Period() :
    ElementBase("Period"), segment_base_(NULL), segment_list_(NULL),
    segment_template_(NULL), asset_identifier_(NULL),
    xlink_actuate_("onRequest"), xlink_href_(""), xlink_type_("simple"),
    xlink_show_("embed"), id_(""), start_(""), duration_(""),
    is_bitstream_switching_(false) {
}

Period::~Period() {
  for (size_t i = 0; i < base_urls_.size(); i++)
    delete (base_urls_.at(i));
  for (size_t i = 0; i < adaptation_sets_.size(); i++)
    delete (adaptation_sets_.at(i));
  for (size_t i = 0; i < subsets_.size(); i++)
    delete (subsets_.at(i));
  for (size_t i = 0; i < supplemental_properties_.size(); i++)
    delete (supplemental_properties_.at(i));
  for (size_t i = 0; i < group_labels_.size(); i++)
    delete (group_labels_.at(i));
  for (size_t i = 0; i < event_streams_.size(); i++)
    delete (event_streams_.at(i));
  for (size_t i = 0; i < service_descriptions_.size(); i++)
    delete (service_descriptions_.at(i));
  for (size_t i = 0; i < content_protections_.size(); i++)
    delete (content_protections_.at(i));
  for (size_t i = 0; i < preselections_.size(); i++)
    delete (preselections_.at(i));
  delete (segment_base_);
  delete (segment_list_);
  delete (segment_template_);
  delete (asset_identifier_);
}

const std::vector<BaseUrl*>& Period::GetBaseURLs() const {
  return base_urls_;
}

SegmentBase* Period::GetSegmentBase() const {
  return segment_base_;
}

SegmentList* Period::GetSegmentList() const {
  return segment_list_;
}

SegmentTemplate* Period::GetSegmentTemplate() const {
  return segment_template_;
}

const Descriptor* Period::GetAssetIdentifier() const {
  return asset_identifier_;
}

const std::vector<EventStream*>& Period::GetEventStreams() const {
  return event_streams_;
}

const std::vector<ServiceDescription*>& Period::GetServiceDescriptions() const {
  return service_descriptions_;
}

const std::vector<ContentProtection*>& Period::GetContentProtections() const {
  return content_protections_;
}

const std::vector<AdaptationSet*>& Period::GetAdaptationSets() const {
  return adaptation_sets_;
}

const std::vector<Subset*>& Period::GetSubsets() const {
  return subsets_;
}

const std::vector<Descriptor*>& Period::GetSupplementalProperties() const {
  return supplemental_properties_;
}

const std::vector<Label*>& Period::GetGroupLabels() const {
  return group_labels_;
}

const std::vector<Preselection*>& Period::GetPreselections() const {
  return preselections_;
}

const std::string& Period::GetXlinkHref() const {
  return xlink_href_;
}

const std::string& Period::GetXlinkActuate() const {
  return xlink_actuate_;
}

const std::string& Period::GetXlinkType() const {
  return xlink_type_;
}

const std::string& Period::GetXlinkShow() const {
  return xlink_show_;
}

const std::string& Period::GetId() const {
  return id_;
}

const std::string& Period::GetStart() const {
  return start_;
}

const std::string& Period::GetDuration() const {
  return duration_;
}

bool Period::GetBitstreamSwitching() const {
  return is_bitstream_switching_;
}

} // namespace mpd
} // namespace dash
