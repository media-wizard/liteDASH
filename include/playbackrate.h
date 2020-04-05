/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_PLAYBACKRATE_H_
#define DASH_PLAYBACKRATE_H_

#include "elementbase.h"

namespace dash {
namespace mpd {

class PlaybackRate: public ElementBase {
  public:
    PlaybackRate();
    double GetMax() const;
    double GetMin() const;

  private:
    double max_;
    double min_;

    friend class PlaybackRateElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* IPLAYBACKRATE_H_ */
