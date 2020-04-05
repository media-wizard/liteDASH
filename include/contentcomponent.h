/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_CONTENTCOMPONENT_H_
#define DASH_CONTENTCOMPONENT_H_

#include <string>
#include <vector>

#include "elementbase.h"

namespace dash {
namespace mpd {

class Descriptor;

class ContentComponent: public ElementBase {
  public:
    ContentComponent();
    ~ContentComponent();
    const std::vector<Descriptor*>& GetAccessibility() const;
    const std::vector<Descriptor*>& GetRole() const;
    const std::vector<Descriptor*>& GetRating() const;
    const std::vector<Descriptor*>& GetViewpoint() const;
    uint32_t GetId() const;
    const std::string& GetLang() const;
    const std::string& GetContentType() const;
    const std::string& GetPar() const;
    const std::string& GetTag() const;

  private:
    std::vector<Descriptor*> accessibility_;
    std::vector<Descriptor*> role_;
    std::vector<Descriptor*> rating_;
    std::vector<Descriptor*> viewpoint_;
    uint32_t id_;
    std::string lang_;
    std::string content_type_;
    std::string par_;
    std::string tag_;

    friend class ContentComponentElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_CONTENTCOMPONENT_H_ */
