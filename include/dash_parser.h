/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_PARSER_H_
#define DASH_PARSER_H_

#include <memory>

#include "mpd.h"

namespace dash {
namespace mpd {

class DASHParser {
  public:
    DASHParser();
    ~DASHParser();
    std::unique_ptr<MPD> Parse(char *buff, size_t buff_size, const std::string &mpd_url);

  private:
    class InternalParser;
    InternalParser *pImpl_;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_PARSER_H_ */
