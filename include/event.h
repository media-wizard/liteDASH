/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_EVENT_H_
#define DASH_EVENT_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class Event: public ElementBase {
  public:
    Event();
    uint64_t GetPresentationTime() const;
    const std::string& GetDuration() const;
    uint32_t GetId() const;
    const std::string& GetContentEncoding() const;
    const std::string& GetMessageData() const;

  private:
    uint64_t presentation_time_;
    std::string duration_;
    uint32_t id_;
    std::string content_encoding_;
    std::string message_data_;

    friend class EventElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_EVENT_H_ */
