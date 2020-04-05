/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_PRESELECTION_H_
#define DASH_PRESELECTION_H_

#include <string>
#include <vector>

#include "representationbase.h"

namespace dash {
namespace mpd {

class Descriptor;

class Preselection: public RepresentationBase {
  public:
    Preselection();
    ~Preselection();
    const std::vector<Descriptor*>& GetAccessibility() const;
    const std::vector<Descriptor*>& GetRole() const;
    const std::vector<Descriptor*>& GetRating() const;
    const std::vector<Descriptor*>& GetViewpoint() const;
    const std::string& GetId() const;
    const std::vector<std::string>& GetPreselectionComponents() const;
    const std::string& GetLang() const;
    const std::string& GetOrder() const;

  private:
    std::vector<Descriptor*> accessibility_;
    std::vector<Descriptor*> role_;
    std::vector<Descriptor*> rating_;
    std::vector<Descriptor*> viewpoint_;
    std::string id_;
    std::vector<std::string> preselection_components_;
    std::string lang_;
    std::string order_;

    friend class PreselectionElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_PRESELECTION_H_ */
