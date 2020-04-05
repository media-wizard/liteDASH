/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_DESCRIPTOR_H_
#define DASH_DESCRIPTOR_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class Descriptor: public ElementBase {
  public:
    Descriptor(const std::string &name);
    const std::string& GetSchemeIdUri() const;
    const std::string& GetValue() const;
    const std::string& GetId() const;

  private:
    std::string scheme_id_uri_;
    std::string value_;
    std::string id_;

    friend class DescriptorElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_DESCRIPTOR_H_ */
