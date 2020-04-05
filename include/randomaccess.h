/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_RANDOMACCESS_H_
#define DASH_RANDOMACCESS_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class RandomAccess: public ElementBase {
  public:
    RandomAccess();
    uint32_t GetInterval() const;
    const std::string& GetType() const;
    const std::string& GetMinBufferTime() const;
    uint32_t GetBandwidth() const;

  private:
    uint32_t interval_;
    std::string type_;
    std::string min_buffer_time_;
    uint32_t bandwidth_;

    friend class RandomAccessElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_RANDOMACCESS_H_ */
