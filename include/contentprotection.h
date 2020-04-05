/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_CONTENTPROTECTION_H_
#define DASH_CONTENTPROTECTION_H_

#include "descriptor.h"

#include <string>

namespace dash {
namespace mpd {

class ContentProtection: public Descriptor {
  public:
    ContentProtection();
    const std::string& GetRobustness() const;
    const std::string& GetRefId() const;
    const std::string& GetRef() const;

  private:
    std::string robustness_;
    std::string ref_id_;
    std::string ref_;

    friend class ContentProtectionElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_CONTENTPROTECTION_H_ */
