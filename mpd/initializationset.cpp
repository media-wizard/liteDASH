/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "initializationset.h"
#include "descriptor.h"

namespace dash {
namespace mpd {

InitializationSet::InitializationSet() :
    RepresentationBase("InitializationSet"), xlink_href_(""),
    xlink_actuate_("onRequest"), xlink_type_("simple"), content_type_(""),
    par_(""), max_width_(0), max_height_(0), max_frame_rate_(""),
    in_all_periods_(true), initialization_("") {
}

InitializationSet::~InitializationSet() {
  for (size_t i = 0; i < accessibility_.size(); i++)
    delete (accessibility_.at(i));
  for (size_t i = 0; i < role_.size(); i++)
    delete (role_.at(i));
  for (size_t i = 0; i < rating_.size(); i++)
    delete (rating_.at(i));
  for (size_t i = 0; i < viewpoint_.size(); i++)
    delete (viewpoint_.at(i));
}

const std::vector<Descriptor*>& InitializationSet::GetAccessibility() const {
  return accessibility_;
}

const std::vector<Descriptor*>& InitializationSet::GetRole() const {
  return role_;
}

const std::vector<Descriptor*>& InitializationSet::GetRating() const {
  return rating_;
}

const std::vector<Descriptor*>& InitializationSet::GetViewpoint() const {
  return viewpoint_;
}

const std::string& InitializationSet::GetXlinkHref() const {
  return xlink_href_;
}

const std::string& InitializationSet::GetXlinkActuate() const {
  return xlink_actuate_;
}

const std::string& InitializationSet::GetXlinkType() const {
  return xlink_type_;
}

uint32_t InitializationSet::GetId() const {
  return id_;
}

bool InitializationSet::IsInAllPeriods() const {
  return in_all_periods_;
}

const std::string& InitializationSet::GetContentType() const {
  return content_type_;
}

const std::string& InitializationSet::GetPar() const {
  return par_;
}

uint32_t InitializationSet::GetMaxWidth() const {
  return max_width_;
}

uint32_t InitializationSet::GetMaxHeight() const {
  return max_height_;
}

const std::string& InitializationSet::GetMaxFrameRate() const {
  return max_frame_rate_;
}

const std::string& InitializationSet::GetInitialization() const {
  return initialization_;
}

} // namespace mpd
} // namespace dash
