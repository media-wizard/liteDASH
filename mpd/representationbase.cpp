/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "representationbase.h"

#include "contentpopularityrate.h"
#include "contentprotection.h"
#include "descriptor.h"
#include "eventstream.h"
#include "label.h"
#include "producerreferencetime.h"
#include "randomaccess.h"
#include "resync.h"
#include "switching.h"

namespace dash {
namespace mpd {

RepresentationBase::RepresentationBase(const std::string &name) :
    ElementBase(name), output_protection_(NULL), width_(0), height_(0),
    sar_(""), frame_rate_(""), audio_sampling_rate_(""), mime_type_(""),
    maximum_SAP_period_(0.0), start_with_SAP_(0), max_playout_rate_(0.0),
    coding_dependency_(false), scan_type_(""), selection_priority_(1) {
}

RepresentationBase::~RepresentationBase() {
  for (size_t i = 0; i < frame_packing_.size(); i++)
    delete (frame_packing_.at(i));
  for (size_t i = 0; i < audio_channel_configuration_.size(); i++)
    delete (audio_channel_configuration_.at(i));
  for (size_t i = 0; i < content_protections_.size(); i++)
    delete (content_protections_.at(i));
  for (size_t i = 0; i < essential_properties_.size(); i++)
    delete (essential_properties_.at(i));
  for (size_t i = 0; i < supplemental_properties_.size(); i++)
    delete (supplemental_properties_.at(i));
  for (size_t i = 0; i < event_streams_.size(); i++)
    delete (event_streams_.at(i));
  for (size_t i = 0; i < switchings_.size(); i++)
    delete (switchings_.at(i));
  for (size_t i = 0; i < random_accesses_.size(); i++)
    delete (random_accesses_.at(i));
  for (size_t i = 0; i < group_labels_.size(); i++)
    delete (group_labels_.at(i));
  for (size_t i = 0; i < labels_.size(); i++)
    delete (labels_.at(i));
  for (size_t i = 0; i < content_popularity_rates_.size(); i++)
    delete (content_popularity_rates_.at(i));
  for (size_t i = 0; i < producer_reference_times_.size(); i++)
    delete (producer_reference_times_.at(i));
  for (size_t i = 0; i < resyncs_.size(); i++)
    delete (resyncs_.at(i));
  delete (output_protection_);
}

const std::vector<Descriptor*>& RepresentationBase::GetFramePacking() const {
  return frame_packing_;
}

const std::vector<Descriptor*>& RepresentationBase::GetAudioChannelConfiguration() const {
  return audio_channel_configuration_;
}

const std::vector<ContentProtection*>& RepresentationBase::GetContentProtections() const {
  return content_protections_;
}

const Descriptor* RepresentationBase::GetOutputProtection() const {
  return output_protection_;
}

const std::vector<Descriptor*>& RepresentationBase::GetEssentialProperties() const {
  return essential_properties_;
}

const std::vector<Descriptor*>& RepresentationBase::GetSupplementalProperties() const {
  return supplemental_properties_;
}

const std::vector<EventStream*>& RepresentationBase::GetEventStreams() const {
  return event_streams_;
}

const std::vector<Switching*>& RepresentationBase::GetSwitchings() const {
  return switchings_;
}

const std::vector<RandomAccess*>& RepresentationBase::GetRandomAccesses() const {
  return random_accesses_;
}

const std::vector<Label*>& RepresentationBase::GetGroupLabels() const {
  return group_labels_;
}

const std::vector<Label*>& RepresentationBase::GetLabels() const {
  return labels_;
}

const std::vector<ContentPopularityRate*>& RepresentationBase::GetContentPopularityRates() const {
  return content_popularity_rates_;
}

const std::vector<ProducerReferenceTime*>& RepresentationBase::GetProducerReferenceTimes() const {
  return producer_reference_times_;
}

const std::vector<Resync*>& RepresentationBase::GetResyncs() const {
  return resyncs_;
}

const std::vector<std::string>& RepresentationBase::GetProfiles() const {
  return profiles_;
}

uint32_t RepresentationBase::GetWidth() const {
  return width_;
}

uint32_t RepresentationBase::GetHeight() const {
  return height_;
}

const std::string& RepresentationBase::GetSar() const {
  return sar_;
}

const std::string& RepresentationBase::GetFrameRate() const {
  return frame_rate_;
}

const std::string& RepresentationBase::GetAudioSamplingRate() const {
  return audio_sampling_rate_;
}

const std::string& RepresentationBase::GetMimeType() const {
  return mime_type_;
}

const std::vector<std::string>& RepresentationBase::GetSegmentProfiles() const {
  return segment_profiles_;
}

const std::vector<std::string>& RepresentationBase::GetCodecs() const {
  return codecs_;
}

const std::vector<std::string>& RepresentationBase::GetContainerProfiles() const {
  return container_profiles_;
}

double RepresentationBase::GetMaximumSAPPeriod() const {
  return maximum_SAP_period_;
}

uint8_t RepresentationBase::GetStartWithSAP() const {
  return start_with_SAP_;
}

double RepresentationBase::GetMaxPlayoutRate() const {
  return max_playout_rate_;
}

bool RepresentationBase::HasCodingDependency() const {
  return coding_dependency_;
}

std::string RepresentationBase::GetScanType() const {
  return scan_type_;
}

uint32_t RepresentationBase::GetSelectionPriority() const {
  return selection_priority_;
}

std::string RepresentationBase::GetTag() const {
  return tag_;
}

} // namespace mpd
} // namespace dash
