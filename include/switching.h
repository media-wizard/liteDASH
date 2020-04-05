/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_SWITCHING_H_
#define DASH_SWITCHING_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class Switching: public ElementBase {
  public:
    Switching();
    uint32_t GetInterval() const;
    const std::string& GetType() const;

  private:
    uint32_t interval_;
    std::string type_;

    friend class SwitchingElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_SWITCHING_H_ */
