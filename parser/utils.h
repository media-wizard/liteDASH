/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_UTILS_H_
#define DASH_UTILS_H_

#include <string>
#include <vector>
#include <cstdint>

namespace dash {
namespace mpd {

class Utils {
  public:
    static bool SplitStrValues(const std::string &in_str, const char delim,
        std::vector<std::string> &out_vec);
    static void SplitUIntValues(const std::string &in_str, const char delim,
        std::vector<uint32_t> &out_vec);
    static bool ConvertToBool(const std::string &in_str);
    static std::string GetBasePath(const std::string &url);
};

} // namespace mpd
} // namespace dash

#endif /* DASH_UTILS_H_ */
