/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_ADAPTATIONSET_H_
#define DASH_ADAPTATIONSET_H_

#include <string>
#include <vector>

#include "representationbase.h"

namespace dash {
namespace mpd {

class Descriptor;
class ContentComponent;
class BaseUrl;
class SegmentBase;
class SegmentList;
class SegmentTemplate;
class Representation;

class AdaptationSet: public RepresentationBase {
  public:
    AdaptationSet();
    ~AdaptationSet();
    const std::vector<Descriptor*>& GetAccessibility() const;
    const std::vector<Descriptor*>& GetRole() const;
    const std::vector<Descriptor*>& GetRating() const;
    const std::vector<Descriptor*>& GetViewpoint() const;
    const std::vector<ContentComponent*>& GetContentComponent() const;
    const std::vector<BaseUrl*>& GetBaseURLs() const;
    const SegmentBase* GetSegmentBase() const;
    const SegmentList* GetSegmentList() const;
    const SegmentTemplate* GetSegmentTemplate() const;
    const std::vector<Representation*>& GetRepresentation() const;
    const std::string& GetXlinkHref() const;
    const std::string& GetXlinkActuate() const;
    const std::string& GetXlinkType() const;
    const std::string& GetXlinkShow() const;
    uint32_t GetId() const;
    uint32_t GetGroup() const;
    const std::string& GetLang() const;
    const std::string& GetContentType() const;
    const std::string& GetPar() const;
    uint32_t GetMinBandwidth() const;
    uint32_t GetMaxBandwidth() const;
    uint32_t GetMinWidth() const;
    uint32_t GetMaxWidth() const;
    uint32_t GetMinHeight() const;
    uint32_t GetMaxHeight() const;
    const std::string& GetMinFramerate() const;
    const std::string& GetMaxFramerate() const;
    bool GetSegmentAligment() const;
    bool GetSubsegmentAlignment() const;
    uint8_t GetSubsegmentStartsWithSAP() const;
    bool GetBitstreamSwitching() const;
    const std::vector<uint32_t>& GetInitializationSetRef() const;
    const std::string& GetInitializationPrincipal() const;

  private:
    std::vector<Descriptor*> accessibility_;
    std::vector<Descriptor*> role_;
    std::vector<Descriptor*> rating_;
    std::vector<Descriptor*> viewpoint_;
    std::vector<ContentComponent*> content_component_;
    std::vector<BaseUrl*> base_urls_;
    SegmentBase *segment_base_;
    SegmentList *segment_list_;
    SegmentTemplate *segment_template_;
    std::vector<Representation*> representation_;
    std::string xlink_href_;
    std::string xlink_actuate_;
    std::string xlink_type_;
    std::string xlink_show_;
    uint32_t id_;
    uint32_t group_;
    std::string lang_;
    std::string content_type_;
    std::string par_;
    uint32_t min_bandwidth_;
    uint32_t max_bandwidth_;
    uint32_t min_width_;
    uint32_t max_width_;
    uint32_t min_height_;
    uint32_t max_height_;
    std::string min_framerate_;
    std::string max_framerate_;
    bool segment_alignment_;
    bool subsegment_alignment_;
    uint8_t subsegment_starts_with_SAP_;
    bool is_bitstream_switching_;
    std::vector<uint32_t> initialization_set_Ref_;
    std::string initialization_principal_;

    friend class AdaptationSetElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_ADAPTATIONSET_H_ */
