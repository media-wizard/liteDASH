/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_REPRESENTATIONBASE_H_
#define DASH_REPRESENTATIONBASE_H_

#include <string>
#include <vector>

#include "elementbase.h"

namespace dash {
namespace mpd {

class ContentPopularityRate;
class ContentProtection;
class Descriptor;
class EventStream;
class Label;
class ProducerReferenceTime;
class RandomAccess;
class Resync;
class Switching;

class RepresentationBase: public ElementBase {
  public:
    RepresentationBase(const std::string &name);
    virtual ~RepresentationBase();
    const std::vector<Descriptor*>& GetFramePacking() const;
    const std::vector<Descriptor*>& GetAudioChannelConfiguration() const;
    const std::vector<ContentProtection*>& GetContentProtections() const;
    const Descriptor* GetOutputProtection() const;
    const std::vector<Descriptor*>& GetEssentialProperties() const;
    const std::vector<Descriptor*>& GetSupplementalProperties() const;
    const std::vector<EventStream*>& GetEventStreams() const;
    const std::vector<Switching*>& GetSwitchings() const;
    const std::vector<RandomAccess*>& GetRandomAccesses() const;
    const std::vector<Label*>& GetGroupLabels() const;
    const std::vector<Label*>& GetLabels() const;
    const std::vector<ContentPopularityRate*>& GetContentPopularityRates() const;
    const std::vector<ProducerReferenceTime*>& GetProducerReferenceTimes() const;
    const std::vector<Resync*>& GetResyncs() const;
    const std::vector<std::string>& GetProfiles() const;
    uint32_t GetWidth() const;
    uint32_t GetHeight() const;
    const std::string& GetSar() const;
    const std::string& GetFrameRate() const; //VINOD FIX
    const std::string& GetAudioSamplingRate() const;
    const std::string& GetMimeType() const;
    const std::vector<std::string>& GetSegmentProfiles() const;
    const std::vector<std::string>& GetCodecs() const;
    const std::vector<std::string>& GetContainerProfiles() const;
    double GetMaximumSAPPeriod() const;
    uint8_t GetStartWithSAP() const;
    double GetMaxPlayoutRate() const;
    bool HasCodingDependency() const;
    std::string GetScanType() const;
    uint32_t GetSelectionPriority() const;
    std::string GetTag() const;

  private:
    std::vector<Descriptor*> frame_packing_;
    std::vector<Descriptor*> audio_channel_configuration_;
    std::vector<ContentProtection*> content_protections_;
    Descriptor *output_protection_;
    std::vector<Descriptor*> essential_properties_;
    std::vector<Descriptor*> supplemental_properties_;
    std::vector<EventStream*> event_streams_;
    std::vector<Switching*> switchings_;
    std::vector<RandomAccess*> random_accesses_;
    std::vector<Label*> group_labels_;
    std::vector<Label*> labels_;
    std::vector<ContentPopularityRate*> content_popularity_rates_;
    std::vector<ProducerReferenceTime*> producer_reference_times_;
    std::vector<Resync*> resyncs_;
    std::vector<std::string> profiles_;
    uint32_t width_;
    uint32_t height_;
    std::string sar_;
    std::string frame_rate_;
    std::string audio_sampling_rate_;
    std::string mime_type_;
    std::vector<std::string> segment_profiles_;
    std::vector<std::string> codecs_;
    std::vector<std::string> container_profiles_;
    double maximum_SAP_period_;
    uint8_t start_with_SAP_;
    double max_playout_rate_;
    bool coding_dependency_;
    std::string scan_type_;
    uint32_t selection_priority_;
    std::string tag_;

    friend class RepresentationBaseElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_REPRESENTATIONBASE_H_ */
