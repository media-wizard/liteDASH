/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "subrepresentation.h"

namespace dash {
namespace mpd {

SubRepresentation::SubRepresentation() :
    RepresentationBase("SubRepresentation"), level_(0), band_width_(0) {
}

uint32_t SubRepresentation::GetLevel() const {
  return level_;
}

const std::vector<uint32_t>& SubRepresentation::GetDependencyLevel() const {
  return dependency_level_;
}

uint32_t SubRepresentation::GetBandWidth() const {
  return band_width_;
}

const std::vector<std::string>& SubRepresentation::GetContentComponent() const {
  return content_component_;
}

} // namespace mpd
} // namespace dash
