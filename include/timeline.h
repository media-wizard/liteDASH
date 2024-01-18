/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_TIMELINE_H_
#define DASH_TIMELINE_H_

#include "elementbase.h"

namespace dash {
namespace mpd {

class Timeline: public ElementBase {
  public:
    Timeline();
    uint64_t GetStartTime() const;
    uint32_t GetDuration() const;
    uint32_t GetRepeatCount() const;

  private:
    uint64_t t_;
    uint32_t n_;
    uint32_t d_;
    uint32_t r_;
    uint32_t k_;

    friend class TimelineElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_TIMELINE_H_ */
