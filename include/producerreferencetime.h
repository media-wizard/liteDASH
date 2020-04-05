/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_PRODUCERREFERENCETIME_H_
#define DASH_PRODUCERREFERENCETIME_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class Descriptor;

class ProducerReferenceTime: public ElementBase {
  public:
    ProducerReferenceTime();
    ~ProducerReferenceTime();
    const Descriptor* GetUTCTiming() const;
    uint32_t GetId() const;
    bool IsInband() const;
    const std::string& GetType() const;
    const std::string& GetApplicationScheme() const;
    const std::string& GetWallClockTime() const;
    uint64_t GetPresentationTime() const;

  private:
    Descriptor *utc_timing_;
    uint32_t id_;
    bool inband_;
    std::string type_;
    std::string application_scheme_;
    std::string wall_clock_time_;
    uint64_t presentation_time_;

    friend class ProducerReferenceTimeElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_PRODUCERREFERENCETIME_H_ */
