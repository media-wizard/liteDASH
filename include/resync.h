/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_RESYNC_H_
#define DASH_RESYNC_H_

#include "elementbase.h"

namespace dash {
namespace mpd {

class Resync: public ElementBase {
  public:
    Resync();
    uint32_t GetType() const;
    uint32_t GetDT() const;
    float GetDIMax() const;
    float GetDIMin() const;
    bool HasMarker() const;

  private:
    uint32_t type_;
    uint32_t dT_;
    float dIMax_;
    float dIMin_;
    bool marker_;

    friend class ResyncElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_RESYNC_H_ */
