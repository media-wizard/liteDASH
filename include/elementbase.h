/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_ELEMENT_BASE_H_
#define DASH_ELEMENT_BASE_H_

#include <map>
#include <string>
#include <vector>

namespace dash {
namespace mpd {

class ElementBase {
  public:
    ElementBase(const std::string &name);
    virtual ~ElementBase();
    const std::string& GetName() const;
    const std::vector<ElementBase*> GetRawChildElements() const;
    const std::map<std::string, std::string> GetRawAttributes() const;

  private:
    std::string name_;
    std::vector<ElementBase*> raw_child_elements_;
    std::map<std::string, std::string> raw_attribs_;

    friend class ElementBaseParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_ELEMENT_BASE_H_ */
