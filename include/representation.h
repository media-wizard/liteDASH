/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_REPRESENTATION_H_
#define DASH_REPRESENTATION_H_

#include <string>
#include <vector>

#include "representationbase.h"

namespace dash {
namespace mpd {

class BaseUrl;
class ExtendedBandwidth;
class SegmentBase;
class SegmentList;
class SegmentTemplate;
class SubRepresentation;

class Representation: public RepresentationBase {
  public:
    Representation();
    ~Representation();
    const std::vector<BaseUrl*>& GetBaseURLs() const;
    const std::vector<ExtendedBandwidth*>& GetExtendedBandwidths() const;
    const std::vector<SubRepresentation*>& GetSubRepresentations() const;
    const SegmentBase* GetSegmentBase() const;
    const SegmentList* GetSegmentList() const;
    const SegmentTemplate* GetSegmentTemplate() const;
    const std::string& GetId() const;
    uint32_t GetBandwidth() const;
    uint32_t GetQualityRanking() const;
    const std::vector<std::string>& GetDependencyId() const;
    const std::vector<std::string>& GetAssociationId() const;
    const std::string& GetAssociationType() const;
    const std::vector<std::string>& GetMediaStreamStructureId() const;

  private:
    std::vector<BaseUrl*> base_urls_;
    std::vector<ExtendedBandwidth*> extended_bandwidths_;
    std::vector<SubRepresentation*> sub_representations_;
    SegmentBase *segment_base_;
    SegmentList *segment_list_;
    SegmentTemplate *segment_template_;
    std::string id_;
    uint32_t bandwidth_;
    uint32_t quality_ranking_;
    std::vector<std::string> dependency_id_;
    std::vector<std::string> association_id_;
    std::string association_type_;
    std::vector<std::string> media_stream_structureId_;

    friend class RepresentationElementParser;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_REPRESENTATION_H_ */
