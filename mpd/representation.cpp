/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "representation.h"

#include "baseurl.h"
#include "extendedbandwidth.h"
#include "representationbase.h"
#include "segmentlist.h"
#include "segmenttemplate.h"
#include "subrepresentation.h"

namespace dash {
namespace mpd {

Representation::Representation() :
    RepresentationBase("Representation"), segment_base_(NULL),
    segment_list_(NULL), segment_template_(NULL), id_(""), bandwidth_(0),
    quality_ranking_(0) {
}

Representation::~Representation() {
  for (size_t i = 0; i < base_urls_.size(); i++)
    delete (base_urls_.at(i));
  for (size_t i = 0; i < extended_bandwidths_.size(); i++)
    delete (extended_bandwidths_.at(i));
  for (size_t i = 0; i < sub_representations_.size(); i++)
    delete (sub_representations_.at(i));

  delete (segment_template_);
  delete (segment_base_);
  delete (segment_list_);
}

const std::vector<BaseUrl*>& Representation::GetBaseURLs() const {
  return base_urls_;
}

const std::vector<ExtendedBandwidth*>& Representation::GetExtendedBandwidths() const {
  return extended_bandwidths_;
}

const std::vector<SubRepresentation*>& Representation::GetSubRepresentations() const {
  return sub_representations_;
}

const SegmentBase* Representation::GetSegmentBase() const {
  return segment_base_;
}

const SegmentList* Representation::GetSegmentList() const {
  return segment_list_;
}

const SegmentTemplate* Representation::GetSegmentTemplate() const {
  return segment_template_;
}

const std::string& Representation::GetId() const {
  return id_;
}

uint32_t Representation::GetBandwidth() const {
  return bandwidth_;
}

uint32_t Representation::GetQualityRanking() const {
  return quality_ranking_;
}

const std::vector<std::string>& Representation::GetDependencyId() const {
  return dependency_id_;
}

const std::vector<std::string>& Representation::GetAssociationId() const {
  return association_id_;
}

const std::string& Representation::GetAssociationType() const {
  return association_type_;
}

const std::vector<std::string>& Representation::GetMediaStreamStructureId() const {
  return media_stream_structureId_;
}

} // namespace mpd
} // namespace dash
