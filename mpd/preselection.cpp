/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "preselection.h"
#include "descriptor.h"

namespace dash {
namespace mpd {

Preselection::Preselection() :
    RepresentationBase("Preselection"), id_("1"), lang_(""), order_("undefined") {
}

Preselection::~Preselection() {
  for (size_t i = 0; i < accessibility_.size(); i++)
    delete (accessibility_.at(i));
  for (size_t i = 0; i < role_.size(); i++)
    delete (role_.at(i));
  for (size_t i = 0; i < rating_.size(); i++)
    delete (rating_.at(i));
  for (size_t i = 0; i < viewpoint_.size(); i++)
    delete (viewpoint_.at(i));
}

const std::vector<Descriptor*>& Preselection::GetAccessibility() const {
  return accessibility_;
}

const std::vector<Descriptor*>& Preselection::GetRole() const {
  return role_;
}

const std::vector<Descriptor*>& Preselection::GetRating() const {
  return rating_;
}

const std::vector<Descriptor*>& Preselection::GetViewpoint() const {
  return viewpoint_;
}

const std::string& Preselection::GetId() const {
  return id_;
}

const std::vector<std::string>& Preselection::GetPreselectionComponents() const {
  return preselection_components_;
}

const std::string& Preselection::GetLang() const {
  return lang_;
}

const std::string& Preselection::GetOrder() const {
  return order_;
}

} // namespace mpd
} // namespace dash
