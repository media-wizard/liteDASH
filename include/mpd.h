/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_MPD_H_
#define DASH_MPD_H_

#include <string>
#include <vector>

#include "elementbase.h"

namespace dash {
namespace mpd {

class ProgramInformation;
class BaseUrl;
class PatchLocation;
class ServiceDescription;
class InitializationSet;
class UIntVWithID;
class ContentProtection;
class Period;
class Descriptor;
class Metrics;
class LeapSecondInformation;

class MPD: public ElementBase {
  public:
    MPD();
    ~MPD();
    const std::vector<ProgramInformation*>& GetProgramInformations() const;
    const std::vector<BaseUrl*>& GetBaseUrls() const;
    const std::vector<std::string>& GetLocations() const;
    const std::vector<PatchLocation*>& GetPatchLocations() const;
    const std::vector<ServiceDescription*>& GetServiceDescriptions() const;
    const std::vector<InitializationSet*>& GetInitializationSets() const;
    const std::vector<UIntVWithID*>& GetInitializationGroups() const;
    const std::vector<UIntVWithID*>& GetInitializationPresentations() const;
    const std::vector<ContentProtection*>& GetContentProtections() const;
    const std::vector<Period*>& GetPeriods() const;
    const std::vector<Descriptor*>& GetEssentialProperties() const;
    const std::vector<Descriptor*>& GetSupplementalProperties() const;
    const std::vector<Descriptor*>& GetUTCTimings() const;
    const std::vector<Metrics*>& GetMetrics() const;
    const LeapSecondInformation* GetLeapSecondInformation() const;
    const std::string& GetId() const;
    const std::vector<std::string>& GetProfiles() const;
    const std::string& GetType() const;
    const std::string& GetAvailabilityStarttime() const;
    const std::string& GetAvailabilityEndtime() const;
    const std::string& GetPublishTime() const;
    const std::string& GetMediaPresentationDuration() const;
    const std::string& GetMinimumUpdatePeriod() const;
    const std::string& GetMinBufferTime() const;
    const std::string& GetTimeShiftBufferDepth() const;
    const std::string& GetSuggestedPresentationDelay() const;
    const std::string& GetMaxSegmentDuration() const;
    const std::string& GetMaxSubsegmentDuration() const;

  private:
    std::vector<ProgramInformation*> program_informations_;
    std::vector<BaseUrl*> base_urls_;
    std::vector<std::string> locations_;
    std::vector<PatchLocation*> patch_locations_;
    std::vector<ServiceDescription*> service_descriptions_;
    std::vector<InitializationSet*> initialization_sets_;
    std::vector<UIntVWithID*> initialization_groups_;
    std::vector<UIntVWithID*> initialization_presentations_;
    std::vector<ContentProtection*> content_protections_;
    std::vector<Period*> periods_;
    std::vector<Metrics*> metrics_;
    std::vector<Descriptor*> essential_properties_;
    std::vector<Descriptor*> supplemental_properties_;
    std::vector<Descriptor*> utc_timings_;
    LeapSecondInformation *leap_second_information_;
    std::string id_;
    std::vector<std::string> profiles_;
    std::string type_;
    std::string availability_start_time_;
    std::string availability_end_time_;
    std::string publish_time_;
    std::string media_presentation_duration_;
    std::string minimum_update_period_;
    std::string min_buffer_time_;
    std::string time_shift_buffer_depth_;
    std::string suggested_presentation_delay_;
    std::string max_segment_duration_;
    std::string max_subsegment_duration_;

    friend class MPDElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_MPD_H_ */
