/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "baseurl_element_parser.h"
#include "baseurl.h"

#include "utils.h"

namespace dash {
namespace mpd {

bool BaseURLElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  BaseUrl *elem = static_cast<BaseUrl*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("serviceLocation") {
      elem->service_location_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("byteRange") {
      elem->byte_range_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("availabilityTimeOffset") {
      elem->availability_time_offset_ = strtod(attrib[i + 1], NULL);
    } else IF_ATTRIB_MATCHES("availabilityTimeComplete") {
      elem->availability_time_complete_ = Utils::ConvertToBool(attrib[i + 1]);
    } else IF_ATTRIB_MATCHES("timeShiftBufferDepth") {
      elem->time_shift_buffer_depth_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("rangeAccess") {
      elem->range_access_ = Utils::ConvertToBool(attrib[i + 1]);
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

bool BaseURLElementParser::ParseTextData(ElementBase *elem_out,
    const std::string sub_element, const char *content, int length) {
  BaseUrl *elem = static_cast<BaseUrl*>(elem_out);
  elem->url_.append(content, length);
  return true;
}

bool BaseURLElementParser::ParseEnd(const std::string &element_name,
    ElementBase *elem_out, const GetExternalAttributes &get_attribs) {
  BaseUrl *elem = static_cast<BaseUrl *>(elem_out);
  if (elem->url_ == "./") {
    elem->url_ = get_attribs("mpd_path");
  }
  return true;
}

ElementBase* BaseURLElementParser::CreateElement(
    const std::string &element) const {
  return new BaseUrl();
}

} // namespace mpd
} // namespace dash