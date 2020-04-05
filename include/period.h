/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_PERIOD_H_
#define DASH_PERIOD_H_

#include <string>
#include <vector>

#include "elementbase.h"

namespace dash {
namespace mpd {

class AdaptationSet;
class BaseUrl;
class ContentProtection;
class Descriptor;
class EventStream;
class Label;
class Preselection;
class SegmentBase;
class SegmentList;
class SegmentTemplate;
class ServiceDescription;
class Subset;

class Period: public ElementBase {
  public:
    Period();
    ~Period();
    const std::vector<BaseUrl*>& GetBaseURLs() const;
    SegmentBase* GetSegmentBase() const;
    SegmentList* GetSegmentList() const;
    SegmentTemplate* GetSegmentTemplate() const;
    const Descriptor* GetAssetIdentifier() const;
    const std::vector<EventStream*>& GetEventStreams() const;
    const std::vector<ServiceDescription*>& GetServiceDescriptions() const;
    const std::vector<ContentProtection*>& GetContentProtections() const;
    const std::vector<AdaptationSet*>& GetAdaptationSets() const;
    const std::vector<Subset*>& GetSubsets() const;
    const std::vector<Descriptor*>& GetSupplementalProperties() const;
    const std::vector<Label*>& GetGroupLabels() const;
    const std::vector<Preselection*>& GetPreselections() const;
    const std::string& GetXlinkHref() const;
    const std::string& GetXlinkActuate() const;
    const std::string& GetXlinkType() const;
    const std::string& GetXlinkShow() const;
    const std::string& GetId() const;
    const std::string& GetStart() const;
    const std::string& GetDuration() const;
    bool GetBitstreamSwitching() const;

  private:
    std::vector<BaseUrl*> base_urls_;
    SegmentBase *segment_base_;
    SegmentList *segment_list_;
    SegmentTemplate *segment_template_;
    Descriptor *asset_identifier_;
    std::vector<EventStream*> event_streams_;
    std::vector<ServiceDescription*> service_descriptions_;
    std::vector<ContentProtection*> content_protections_;
    std::vector<AdaptationSet*> adaptation_sets_;
    std::vector<AdaptationSet*> empty_adaptation_sets_;
    std::vector<Subset*> subsets_;
    std::vector<Descriptor*> supplemental_properties_;
    std::vector<Label*> group_labels_;
    std::vector<Preselection*> preselections_;
    std::string xlink_href_;
    std::string xlink_actuate_;
    std::string xlink_type_;
    std::string xlink_show_;
    std::string id_;
    std::string start_;
    std::string duration_;
    bool is_bitstream_switching_;

    friend class PeriodElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_PERIOD_H_ */
