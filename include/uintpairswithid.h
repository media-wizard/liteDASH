/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_UINTPAIRSWITHID_H_
#define DASH_UINTPAIRSWITHID_H_

#include <string>
#include <vector>

#include "elementbase.h"
#include "uintpairs.h"

namespace dash {
namespace mpd {

class UIntPairsWithID: public ElementBase {
  public:
    UIntPairsWithID(const std::string &name);
    ~UIntPairsWithID();
    const std::vector<UIntPairs*>& GetQualityLatency() const;
    const std::string& GetType() const;

  private:
    std::vector<UIntPairs*> ql_pairs_;
    std::string type_;

    friend class UIntPairsWithIDElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_UINTPAIRSWITHID_H_ */
