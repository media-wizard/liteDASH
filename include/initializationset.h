/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_INITIALIZATIONSET_H_
#define DASH_INITIALIZATIONSET_H_

#include <string>
#include <vector>

#include "representationbase.h"

namespace dash {
namespace mpd {

class Descriptor;

class InitializationSet: public RepresentationBase {
  public:
    InitializationSet();
    ~InitializationSet();
    const std::vector<Descriptor*>& GetAccessibility() const;
    const std::vector<Descriptor*>& GetRole() const;
    const std::vector<Descriptor*>& GetRating() const;
    const std::vector<Descriptor*>& GetViewpoint() const;
    const std::string& GetXlinkHref() const;
    const std::string& GetXlinkActuate() const;
    const std::string& GetXlinkType() const;
    uint32_t GetId() const;
    bool IsInAllPeriods() const;
    const std::string& GetContentType() const;
    const std::string& GetPar() const;
    uint32_t GetMaxWidth() const;
    uint32_t GetMaxHeight() const;
    const std::string& GetMaxFrameRate() const;
    const std::string& GetInitialization() const;

  private:
    std::vector<Descriptor*> accessibility_;
    std::vector<Descriptor*> role_;
    std::vector<Descriptor*> rating_;
    std::vector<Descriptor*> viewpoint_;
    std::string xlink_href_;
    std::string xlink_actuate_;
    std::string xlink_type_;
    uint32_t id_;
    bool in_all_periods_;
    std::string content_type_;
    std::string par_;
    uint32_t max_width_;
    uint32_t max_height_;
    std::string max_frame_rate_;
    std::string initialization_;

    friend class InitializationSetElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_INITIALIZATIONSET_H_ */
