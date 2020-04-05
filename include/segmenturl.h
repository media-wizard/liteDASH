/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_SEGMENTURL_H_
#define DASH_SEGMENTURL_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class SegmentURL: public ElementBase {
  public:
    SegmentURL();
    const std::string& GetMediaURI() const;
    const std::string& GetMediaRange() const;
    const std::string& GetIndexURI() const;
    const std::string& GetIndexRange() const;

  private:
    std::string media_URI_;
    std::string media_range_;
    std::string index_URI_;
    std::string index_range_;

    friend class SegmentURLElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_SEGMENTURL_H_ */
