/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_RANGE_H_
#define DASH_RANGE_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class Range: public ElementBase {
  public:
    Range();
    const std::string& GetStarttime() const;
    const std::string& GetDuration() const;

  private:
    std::string start_time_;
    std::string duration_;

    friend class RangeElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_RANGE_H_ */
