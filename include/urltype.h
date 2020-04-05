/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_URLTYPE_H_
#define DASH_URLTYPE_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class URLType: public ElementBase {
  public:
    URLType(const std::string &name);
    const std::string& GetSourceURL() const;
    const std::string& GetRange() const;

  private:
    std::string source_url_;
    std::string range_;

    friend class URLTypeElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_URLTYPE_H_ */
