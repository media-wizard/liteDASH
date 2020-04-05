/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "mpd.h"

#include "baseurl.h"
#include "contentprotection.h"
#include "descriptor.h"
#include "initializationset.h"
#include "leapsecondinformation.h"
#include "metrics.h"
#include "patchlocation.h"
#include "period.h"
#include "programinformation.h"
#include "servicedescription.h"
#include "uintvwithid.h"

namespace dash {
namespace mpd {

MPD::MPD() :
    ElementBase("MPD"), leap_second_information_(NULL), id_(""),
    type_("static"), availability_start_time_(""), availability_end_time_(""),
    publish_time_(""), media_presentation_duration_(""),
    minimum_update_period_(""), min_buffer_time_(""),
    time_shift_buffer_depth_(""), suggested_presentation_delay_(""),
    max_segment_duration_(""), max_subsegment_duration_("") {
}

MPD::~MPD() {
  for (size_t i = 0; i < program_informations_.size(); i++)
    delete (program_informations_.at(i));
  for (size_t i = 0; i < metrics_.size(); i++)
    delete (metrics_.at(i));
  for (size_t i = 0; i < essential_properties_.size(); i++)
    delete (essential_properties_.at(i));
  for (size_t i = 0; i < supplemental_properties_.size(); i++)
    delete (supplemental_properties_.at(i));
  for (size_t i = 0; i < utc_timings_.size(); i++)
    delete (utc_timings_.at(i));
  for (size_t i = 0; i < content_protections_.size(); i++)
    delete (content_protections_.at(i));
  for (size_t i = 0; i < periods_.size(); i++)
    delete (periods_.at(i));
  for (size_t i = 0; i < base_urls_.size(); i++)
    delete (base_urls_.at(i));
  for (size_t i = 0; i < service_descriptions_.size(); i++)
    delete (service_descriptions_.at(i));
  for (size_t i = 0; i < initialization_sets_.size(); i++)
    delete (initialization_sets_.at(i));
  for (size_t i = 0; i < initialization_groups_.size(); i++)
    delete (initialization_groups_.at(i));
  for (size_t i = 0; i < initialization_presentations_.size(); i++)
    delete (initialization_presentations_.at(i));

  delete (leap_second_information_);
}

const std::vector<ProgramInformation*>& MPD::GetProgramInformations() const {
  return program_informations_;
}

const std::vector<BaseUrl*>& MPD::GetBaseUrls() const {
  return base_urls_;
}

const std::vector<std::string>& MPD::GetLocations() const {
  return locations_;
}

const std::vector<PatchLocation*>& MPD::GetPatchLocations() const {
  return patch_locations_;
}

const std::vector<ServiceDescription*>& MPD::GetServiceDescriptions() const {
  return service_descriptions_;
}

const std::vector<InitializationSet*>& MPD::GetInitializationSets() const {
  return initialization_sets_;
}

const std::vector<UIntVWithID*>& MPD::GetInitializationGroups() const {
  return initialization_groups_;
}

const std::vector<UIntVWithID*>& MPD::GetInitializationPresentations() const {
  return initialization_presentations_;
}

const std::vector<ContentProtection*>& MPD::GetContentProtections() const {
  return content_protections_;
}

const std::vector<Period*>& MPD::GetPeriods() const {
  return periods_;
}

const std::vector<Metrics*>& MPD::GetMetrics() const {
  return metrics_;
}

const std::vector<Descriptor*>& MPD::GetEssentialProperties() const {
  return essential_properties_;
}

const std::vector<Descriptor*>& MPD::GetSupplementalProperties() const {
  return supplemental_properties_;
}

const std::vector<Descriptor*>& MPD::GetUTCTimings() const {
  return utc_timings_;
}

const LeapSecondInformation* MPD::GetLeapSecondInformation() const {
  return leap_second_information_;
}

const std::string& MPD::GetId() const {
  return id_;
}

const std::vector<std::string>& MPD::GetProfiles() const {
  return profiles_;
}

const std::string& MPD::GetType() const {
  return type_;
}

const std::string& MPD::GetAvailabilityStarttime() const {
  return availability_start_time_;
}

const std::string& MPD::GetPublishTime() const {
  return publish_time_;
}

const std::string& MPD::GetAvailabilityEndtime() const {
  return availability_end_time_;
}

const std::string& MPD::GetMediaPresentationDuration() const {
  return media_presentation_duration_;
}

const std::string& MPD::GetMinimumUpdatePeriod() const {
  return minimum_update_period_;
}

const std::string& MPD::GetMinBufferTime() const {
  return min_buffer_time_;
}

const std::string& MPD::GetTimeShiftBufferDepth() const {
  return time_shift_buffer_depth_;
}

const std::string& MPD::GetSuggestedPresentationDelay() const {
  return suggested_presentation_delay_;
}

const std::string& MPD::GetMaxSegmentDuration() const {
  return max_segment_duration_;
}

const std::string& MPD::GetMaxSubsegmentDuration() const {
  return max_subsegment_duration_;
}

} // namespace mpd
} // namespace dash
