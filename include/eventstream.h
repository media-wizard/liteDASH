/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_EVENTSTREAM_H_
#define DASH_EVENTSTREAM_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class Event;

class EventStream: public ElementBase {
  public:
    EventStream(const std::string &name);
    ~EventStream();
    const std::vector<Event*>& GetEvents() const;
    const std::string& GetXlinkHref() const;
    const std::string& GetXlinkActuate() const;
    const std::string& GetSchemeIdUri() const;
    const std::string& GetValue() const;
    uint32_t GetTimescale() const;
    uint64_t GetPresentationTimeOffset() const;

  private:
    std::vector<Event*> events_;
    std::string xlink_href_;
    std::string xlink_actuate_;
    std::string scheme_id_uri_;
    std::string value_;
    uint32_t timescale_;
    uint64_t presentation_time_offset_;

    friend class EventStreamElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_EVENTSTREAM_H_ */
