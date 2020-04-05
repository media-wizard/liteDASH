/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_FAILOVERCONTENT_H_
#define DASH_FAILOVERCONTENT_H_

#include <vector>

#include "elementbase.h"

namespace dash {
namespace mpd {

class FCS;

class FailoverContent: public ElementBase {
  public:
    FailoverContent();
    ~FailoverContent();
    const std::vector<FCS*>& GetFCS() const;
    bool IsValid() const;

  private:
    std::vector<FCS*> fcs_;
    bool valid_;

    friend class FailoverContentElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_FAILOVERCONTENT_H_ */
