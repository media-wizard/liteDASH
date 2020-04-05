/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_SUBREPRESENTATION_H_
#define DASH_SUBREPRESENTATION_H_

#include <string>
#include <vector>

#include "representationbase.h"

namespace dash {
namespace mpd {

class SubRepresentation: public RepresentationBase {
  public:
    SubRepresentation();
    uint32_t GetLevel() const;
    const std::vector<uint32_t>& GetDependencyLevel() const;
    uint32_t GetBandWidth() const;
    const std::vector<std::string>& GetContentComponent() const;

  private:
    uint32_t level_;
    std::vector<uint32_t> dependency_level_;
    uint32_t band_width_;
    std::vector<std::string> content_component_;

    friend class SubRepresentationElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_SUBREPRESENTATION_H_ */
