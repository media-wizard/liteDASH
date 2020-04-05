/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_SEGMENTLIST_H_
#define DASH_SEGMENTLIST_H_

#include <string>
#include <vector>

#include "multiplesegmentbase.h"

namespace dash {
namespace mpd {

class SegmentURL;

class SegmentList: public MultipleSegmentBase {
  public:
    SegmentList();
    ~SegmentList();
    const std::vector<SegmentURL*>& GetSegmentURLs() const;
    const std::string& GetXlinkHref() const;
    const std::string& GetXlinkActuate() const;
    const std::string& GetXlinkType() const;
    const std::string& GetXlinkShow() const;

  private:
    std::vector<SegmentURL*> segment_urls_;
    std::string xlink_href_;
    std::string xlink_actuate_;
    std::string xlink_type_;
    std::string xlink_show_;

    friend class SegmentListElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_SEGMENTLIST_H_ */
