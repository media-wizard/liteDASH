/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include <stdlib.h>     /* strtoul */
#include "utils.h"

namespace dash {
namespace mpd {

bool Utils::SplitStrValues(const std::string &in_str, const char delim,
    std::vector<std::string> &out_vec) {
  size_t in_length = in_str.length();
  size_t pos = 0;
  std::string value;

  while (pos <= in_length) {
    if (pos >= in_length || in_str[pos] == delim) {
      //TODO: strip
      out_vec.push_back(value);
      value.clear();
    } else {
      value += in_str[pos];
    }
    pos++;
  }
  return true;
}

void Utils::SplitUIntValues(const std::string &in_str, const char delim,
    std::vector<uint32_t> &out_vec) {
  size_t in_length = in_str.length();
  size_t pos = 0;
  std::string value;

  while (pos <= in_length) {
    if (pos >= in_length || in_str[pos] == delim) {
      uint32_t uint_val = strtoul(value.c_str(), NULL, 10);
      out_vec.push_back(uint_val);
      value.clear();
    } else {
      value += in_str[pos];
    }
    pos++;
  }
}

bool Utils::ConvertToBool(const std::string &in_str) {
  return
      (in_str == "true" || in_str == "TRUE" || in_str == "True") ? true : false;
}

std::string Utils::GetBasePath(const std::string &url)
{
    int pos = url.find_last_of('/');
    return url.substr(0, pos + 1);
}

} // namespace mpd
} // namespace dash
