/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_FCS_H_
#define DASH_FCS_H_

#include "elementbase.h"

namespace dash {
namespace mpd {

class FCS: public ElementBase {
  public:
    FCS();
    uint64_t GetPresentationTime() const;
    uint64_t GetDuration() const;

  private:
    uint64_t presentation_time_;
    uint64_t duration_;

    friend class FCSElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_FCS_H_ */
