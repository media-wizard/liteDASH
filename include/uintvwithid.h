/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_UINTVWITHID_H_
#define DASH_UINTVWITHID_H_

#include <string>
#include <vector>

#include "elementbase.h"

namespace dash {
namespace mpd {

class UIntVWithID: public ElementBase {
  public:
    UIntVWithID(const std::string &name);
    const std::vector<uint32_t>& GetList() const;
    uint32_t GetId() const;
    const std::vector<std::string>& GetProfiles() const;
    const std::string& GetContentType() const;

  private:
    std::vector<uint32_t> list_;
    uint32_t id_;
    std::vector<std::string> profiles_;
    std::string content_type_;

    friend class UIntVWithIDElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_UINTVWITHID_H_ */
