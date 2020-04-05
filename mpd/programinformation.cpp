/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "programinformation.h"

namespace dash {
namespace mpd {

ProgramInformation::ProgramInformation() :
    ElementBase("ProgramInformation"), title_(""), source_(""), copyright_(""),
    lang_(""), more_information_url_("") {
}

const std::string& ProgramInformation::GetTitle() const {
  return title_;
}

const std::string& ProgramInformation::GetSource() const {
  return source_;
}

const std::string& ProgramInformation::GetCopyright() const {
  return copyright_;
}

const std::string& ProgramInformation::GetLang() const {
  return lang_;
}

const std::string& ProgramInformation::GetMoreInformationURL() const {
  return more_information_url_;
}

} // namespace mpd
} // namespace dash
