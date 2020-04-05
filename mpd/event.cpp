/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "event.h"

namespace dash {
namespace mpd {

Event::Event() :
    ElementBase("Event"), presentation_time_(0), content_encoding_(""),
    message_data_("") {
}

uint64_t Event::GetPresentationTime() const {
  return presentation_time_;
}

const std::string& Event::GetDuration() const {
  return duration_;
}

uint32_t Event::GetId() const {
  return id_;
}

const std::string& Event::GetContentEncoding() const {
  return content_encoding_;
}

const std::string& Event::GetMessageData() const {
  return message_data_;
}

} // namespace mpd
} // namespace dash
