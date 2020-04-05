/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "contentcomponent.h"
#include "descriptor.h"

namespace dash {
namespace mpd {

ContentComponent::ContentComponent() :
    ElementBase("ContentComponent"), id_(0), lang_(""), content_type_(""),
    par_(""), tag_("") {
}

ContentComponent::~ContentComponent() {
  for (size_t i = 0; i < accessibility_.size(); i++)
    delete (accessibility_.at(i));
  for (size_t i = 0; i < role_.size(); i++)
    delete (role_.at(i));
  for (size_t i = 0; i < rating_.size(); i++)
    delete (rating_.at(i));
  for (size_t i = 0; i < viewpoint_.size(); i++)
    delete (viewpoint_.at(i));
}

const std::vector<Descriptor*>& ContentComponent::GetAccessibility() const {
  return accessibility_;
}

const std::vector<Descriptor*>& ContentComponent::GetRole() const {
  return role_;
}

const std::vector<Descriptor*>& ContentComponent::GetRating() const {
  return rating_;
}

const std::vector<Descriptor*>& ContentComponent::GetViewpoint() const {
  return viewpoint_;
}

uint32_t ContentComponent::GetId() const {
  return id_;
}

const std::string& ContentComponent::GetLang() const {
  return lang_;
}

const std::string& ContentComponent::GetContentType() const {
  return content_type_;
}

const std::string& ContentComponent::GetPar() const {
  return par_;
}

const std::string& ContentComponent::GetTag() const {
  return tag_;
}

} // namespace mpd
} // namespace dash
