/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "resync.h"

namespace dash {
namespace mpd {

Resync::Resync() :
    ElementBase("Resync"), type_(0), dIMin_(0), marker_(false) {
}

uint32_t Resync::GetType() const {
  return type_;
}

uint32_t Resync::GetDT() const {
  return dT_;
}

float Resync::GetDIMax() const {
  return dIMax_;
}

float Resync::GetDIMin() const {
  return dIMin_;
}

bool Resync::HasMarker() const {
  return marker_;
}

} // namespace mpd
} // namespace dash
