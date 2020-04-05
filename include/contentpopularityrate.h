/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_CONTENTPOPULARITYRATE_H_
#define DASH_CONTENTPOPULARITYRATE_H_

#include <string>
#include <vector>

#include "elementbase.h"

namespace dash {
namespace mpd {

class PopularityRate;

class ContentPopularityRate: public ElementBase {
  public:
    ContentPopularityRate();
    ~ContentPopularityRate();
    const std::vector<PopularityRate*>& GetPopularityRates() const;
    const std::string& GetSource() const;
    const std::string& GetSourceDescription() const;

  private:
    std::vector<PopularityRate*> popularity_rates_;
    std::string source_;
    std::string source_description_;

    friend class ContentPopularityRateElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_CONTENTPOPULARITYRATE_H_ */
