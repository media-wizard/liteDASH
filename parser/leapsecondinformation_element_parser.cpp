/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "leapsecondinformation_element_parser.h"
#include "leapsecondinformation.h"


namespace dash {
namespace mpd {

bool LeapSecondInformationElementParser::ParseStart(
    const std::string &element_name, ElementBase *elem_out,
    const char **attrib) {
  LeapSecondInformation *elem = static_cast<LeapSecondInformation*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("availabilityStartLeapOffset") {
      elem->availability_start_leap_offset_ = strtol(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("nextAvailabilityStartLeapOffset") {
      elem->next_availability_start_leap_offset_ = strtol(attrib[i + 1], NULL,
          10);
    } else IF_ATTRIB_MATCHES("nextLeapChangeTime") {
      elem->next_leap_change_time_ = attrib[i + 1]; //TODO: It is in dateTime format
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

ElementBase* LeapSecondInformationElementParser::CreateElement(
    const std::string &element) const {
  return new LeapSecondInformation();
}

} // namespace mpd
} // namespace dash
