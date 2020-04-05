/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_SEGMENTTEMPLATE_H_
#define DASH_SEGMENTTEMPLATE_H_

#include <string>

#include "multiplesegmentbase.h"

namespace dash {
namespace mpd {

class SegmentTemplate: public MultipleSegmentBase {
  public:
    SegmentTemplate();
    const std::string& Getmedia() const;
    const std::string& Getindex() const;
    const std::string& Getinitialization() const;
    const std::string& GetbitstreamSwitching() const;

  private:
    std::string media_;
    std::string index_;
    std::string initialization_;
    std::string bitstream_switching_;

    friend class SegmentTemplateElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_SEGMENTTEMPLATE_H_ */
