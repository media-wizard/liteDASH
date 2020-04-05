/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_LABEL_H_
#define DASH_LABEL_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class Label: public ElementBase {
  public:
    Label();
    uint32_t GetId() const;
    const std::string& GetLang() const;

  private:
    uint32_t id_;
    std::string lang_;

    friend class LabelElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_LABEL_H_ */
