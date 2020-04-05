/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_PROGRAMINFORMATION_H_
#define DASH_PROGRAMINFORMATION_H_

#include <string>

#include "elementbase.h"

namespace dash {
namespace mpd {

class ProgramInformation: public ElementBase {
  public:
    ProgramInformation();
    const std::string& GetTitle() const;
    const std::string& GetSource() const;
    const std::string& GetCopyright() const;
    const std::string& GetLang() const;
    const std::string& GetMoreInformationURL() const;

  private:
    std::string title_;
    std::string source_;
    std::string copyright_;
    std::string lang_;
    std::string more_information_url_;

    friend class ProgramInformationElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_PROGRAMINFORMATION_H_ */
