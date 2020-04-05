/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "producerreferencetime.h"

#include "descriptor.h"

namespace dash {
namespace mpd {

ProducerReferenceTime::ProducerReferenceTime() :
    ElementBase("ProducerReferenceTime"), utc_timing_(NULL), inband_(false),
    type_("encoder") {
}

ProducerReferenceTime::~ProducerReferenceTime() {
  delete (utc_timing_);
}

const Descriptor* ProducerReferenceTime::GetUTCTiming() const {
  return utc_timing_;
}

uint32_t ProducerReferenceTime::GetId() const {
  return id_;
}

bool ProducerReferenceTime::IsInband() const {
  return inband_;
}

const std::string& ProducerReferenceTime::GetType() const {
  return type_;
}

const std::string& ProducerReferenceTime::GetApplicationScheme() const {
  return application_scheme_;
}

const std::string& ProducerReferenceTime::GetWallClockTime() const {
  return wall_clock_time_;
}

uint64_t ProducerReferenceTime::GetPresentationTime() const {
  return presentation_time_;
}

} // namespace mpd
} // namespace dash
