/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "eventstream.h"
#include "event.h"

namespace dash {
namespace mpd {

EventStream::EventStream(const std::string &name) :
    ElementBase(name), xlink_href_(""), xlink_actuate_("onRequest"),
    scheme_id_uri_(""), value_(""), presentation_time_offset_(0),
    timescale_(1) {
}

EventStream::~EventStream() {
  for (size_t i = 0; i < events_.size(); i++)
    delete (events_.at(i));
}

const std::vector<Event*>& EventStream::GetEvents() const {
  return events_;
}

const std::string& EventStream::GetXlinkHref() const {
  return xlink_href_;
}

const std::string& EventStream::GetXlinkActuate() const {
  return xlink_actuate_;
}

const std::string& EventStream::GetSchemeIdUri() const {
  return scheme_id_uri_;
}

const std::string& EventStream::GetValue() const {
  return value_;
}

uint32_t EventStream::GetTimescale() const {
  return timescale_;
}

uint64_t EventStream::GetPresentationTimeOffset() const {
  return presentation_time_offset_;
}


} // namespace mpd
} // namespace dash
