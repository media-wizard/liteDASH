/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "adaptationset.h"

#include "baseurl.h"
#include "contentcomponent.h"
#include "descriptor.h"
#include "representation.h"
#include "segmentbase.h"
#include "segmentlist.h"
#include "segmenttemplate.h"

#include <cstdlib>

namespace dash {
namespace mpd {

AdaptationSet::AdaptationSet() :
		RepresentationBase("AdaptationSet"), segment_base_(NULL),
    segment_list_(NULL), segment_template_(NULL), xlink_href_(""),
    xlink_actuate_("onRequest"), xlink_type_(""), xlink_show_(""),
    id_(0), lang_(""), content_type_(""), par_(""), min_bandwidth_(0),
    max_bandwidth_(0), min_width_(0), max_width_(0), min_height_(0),
    max_height_(0), min_framerate_(""), max_framerate_(""),
    segment_alignment_(false), subsegment_alignment_(false),
    is_bitstream_switching_(false), initialization_principal_("") {
}

AdaptationSet::~AdaptationSet() {
	for (size_t i = 0; i < accessibility_.size(); i++)
		delete (accessibility_.at(i));
	for (size_t i = 0; i < role_.size(); i++)
		delete (role_.at(i));
	for (size_t i = 0; i < rating_.size(); i++)
		delete (rating_.at(i));
	for (size_t i = 0; i < viewpoint_.size(); i++)
		delete (viewpoint_.at(i));
	for (size_t i = 0; i < content_component_.size(); i++)
		delete (content_component_.at(i));
	for (size_t i = 0; i < base_urls_.size(); i++)
		delete (base_urls_.at(i));
	for (size_t i = 0; i < representation_.size(); i++)
		delete (representation_.at(i));

	delete (segment_base_);
	delete (segment_list_);
	delete (segment_template_);
}

const std::vector<Descriptor*>& AdaptationSet::GetAccessibility() const {
	return accessibility_;
}

const std::vector<Descriptor*>& AdaptationSet::GetRole() const {
	return role_;
}

const std::vector<Descriptor*>& AdaptationSet::GetRating() const {
	return rating_;
}

const std::vector<Descriptor*>& AdaptationSet::GetViewpoint() const {
	return viewpoint_;
}

const std::vector<ContentComponent*>& AdaptationSet::GetContentComponent() const {
	return content_component_;
}

const std::vector<BaseUrl*>& AdaptationSet::GetBaseURLs() const {
	return base_urls_;
}

const SegmentBase* AdaptationSet::GetSegmentBase() const {
	return segment_base_;
}

const SegmentList* AdaptationSet::GetSegmentList() const {
	return segment_list_;
}

const SegmentTemplate* AdaptationSet::GetSegmentTemplate() const {
	return segment_template_;
}

const std::vector<Representation*>& AdaptationSet::GetRepresentation() const {
	return representation_;
}

const std::string& AdaptationSet::GetXlinkHref() const {
	return xlink_href_;
}

const std::string& AdaptationSet::GetXlinkActuate() const {
	return xlink_actuate_;
}

const std::string& AdaptationSet::GetXlinkType() const {
	return xlink_type_;
}

const std::string& AdaptationSet::GetXlinkShow() const {
	return xlink_show_;
}

uint32_t AdaptationSet::GetId() const {
	return id_;
}

uint32_t AdaptationSet::GetGroup() const {
	return group_;
}

const std::string& AdaptationSet::GetLang() const {
	return lang_;
}

const std::string& AdaptationSet::GetContentType() const {
	return content_type_;
}

const std::string& AdaptationSet::GetPar() const {
	return par_;
}

uint32_t AdaptationSet::GetMinBandwidth() const {
	return min_bandwidth_;
}

uint32_t AdaptationSet::GetMaxBandwidth() const {
	return max_bandwidth_;
}

uint32_t AdaptationSet::GetMinWidth() const {
	return min_width_;
}

uint32_t AdaptationSet::GetMaxWidth() const {
	return max_width_;
}

uint32_t AdaptationSet::GetMinHeight() const {
	return min_height_;
}

uint32_t AdaptationSet::GetMaxHeight() const {
	return max_height_;
}

const std::string& AdaptationSet::GetMinFramerate() const {
	return min_framerate_;
}

const std::string& AdaptationSet::GetMaxFramerate() const {
	return max_framerate_;
}

bool AdaptationSet::GetSegmentAligment() const {
	return segment_alignment_;
}

bool AdaptationSet::GetSubsegmentAlignment() const {
	return subsegment_alignment_;
}

uint8_t AdaptationSet::GetSubsegmentStartsWithSAP() const {
	return subsegment_starts_with_SAP_;
}

bool AdaptationSet::GetBitstreamSwitching() const {
	return is_bitstream_switching_;
}

const std::vector<uint32_t>& AdaptationSet::GetInitializationSetRef() const {
	return initialization_set_Ref_;
}

const std::string& AdaptationSet::GetInitializationPrincipal() const {
	return initialization_principal_;
}

} // namespace mpd
} // namespace dash
