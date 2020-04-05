/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_SUBSET_H_
#define DASH_SUBSET_H_

#include <string>
#include <vector>

#include "elementbase.h"

namespace dash {
namespace mpd {

class Subset: public ElementBase {
  public:
    Subset();
    const std::vector<uint32_t>& Contains() const;
    const std::string& GetId() const;

  private:
    std::vector<uint32_t> contains_;
    std::string id_;

    friend class SubsetElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_SUBSET_H_ */
