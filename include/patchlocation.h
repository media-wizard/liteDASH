/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_PATCHLOCATION_H_
#define DASH_PATCHLOCATION_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class PatchLocation: public ElementBase {
  public:
    PatchLocation();
    const std::string& GetUrl() const;
    double GetTtl() const;

  private:
    std::string url_;
    double ttl_;

    friend class PatchLocationElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_PATCHLOCATION_H_ */
