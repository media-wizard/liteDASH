/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "contentpopularityrate.h"
#include "popularityrate.h"

namespace dash {
namespace mpd {

ContentPopularityRate::ContentPopularityRate() :
    ElementBase("ContentPopularityRate"), source_(""), source_description_("") {
}

ContentPopularityRate::~ContentPopularityRate() {
  for (size_t i = 0; i < popularity_rates_.size(); i++)
    delete (popularity_rates_.at(i));
}

const std::vector<PopularityRate*>& ContentPopularityRate::GetPopularityRates() const {
  return popularity_rates_;
}

const std::string& ContentPopularityRate::GetSource() const {
  return source_;
}

const std::string& ContentPopularityRate::GetSourceDescription() const {
  return source_description_;
}

} // namespace mpd
} // namespace dash
