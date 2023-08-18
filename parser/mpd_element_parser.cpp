/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "mpd_element_parser.h"
#include "mpd.h"

#include "baseurl.h"
#include "baseurl_element_parser.h"
#include "contentprotection.h"
#include "contentprotection_element_parser.h"
#include "descriptor.h"
#include "descriptor_element_parser.h"
#include "initializationset.h"
#include "initializationset_element_parser.h"
#include "leapsecondinformation.h"
#include "leapsecondinformation_element_parser.h"
#include "metrics.h"
#include "metrics_element_parser.h"
#include "patchlocation.h"
#include "patchlocation_element_parser.h"
#include "period.h"
#include "period_element_parser.h"
#include "programinformation.h"
#include "programinformation_element_parser.h"
#include "servicedescription.h"
#include "servicedescription_element_parser.h"
#include "uintvwithid.h"
#include "uintvwithid_element_parser.h"
#include "utils.h"


namespace dash {
namespace mpd {

bool MPDElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  MPD *elem = static_cast<MPD*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("id") {
      elem->id_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("profiles") {
      Utils::SplitStrValues(attrib[i + 1], ',', elem->profiles_);
    } else IF_ATTRIB_MATCHES("type") {
      elem->type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("availabilityStartTime") {
      elem->availability_start_time_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("availabilityEndTime") {
      elem->availability_end_time_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("publishTime") {
      elem->publish_time_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("mediaPresentationDuration") {
      elem->media_presentation_duration_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("minimumUpdatePeriod") {
      elem->minimum_update_period_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("minBufferTime") {
      elem->min_buffer_time_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("timeShiftBufferDepth") {
      elem->time_shift_buffer_depth_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("suggestedPresentationDelay") {
      elem->suggested_presentation_delay_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("maxSegmentDuration") {
      elem->max_segment_duration_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("maxSubsegmentDuration") {
      elem->max_subsegment_duration_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  tmp_location_.clear();
  return true;
}

bool MPDElementParser::ParseEnd(const std::string &element_name,
    ElementBase *elem_out, const GetExternalAttributes &get_attribs) {
  if (element_name == "Location") {
    MPD *elem = static_cast<MPD*>(elem_out);
    elem->locations_.push_back(tmp_location_);
  }
  tmp_location_.clear();
  return true;
}

bool MPDElementParser::ParseTextData(ElementBase *elem_out,
    const std::string element_name, const char *content, int length) {
  if (element_name == "Location") {
    tmp_location_.append(content, length);
  }
  return true;
}

ElementBase* MPDElementParser::CreateElement(const std::string &element) const {
  return new MPD();
}

void MPDElementParser::AttachChildElementToParent(ElementBase *parent,
    ElementBase *child) {
  MPD *mpd_elem = static_cast<MPD*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "ProgramInformation") {
    mpd_elem->program_informations_.push_back(
        static_cast<ProgramInformation*>(child));
  } else if (child_name == "BaseURL") {
    mpd_elem->base_urls_.push_back(static_cast<BaseUrl*>(child));
  } else if (child_name == "PatchLocation") {
    mpd_elem->patch_locations_.push_back(static_cast<PatchLocation*>(child));
  } else if (child_name == "ServiceDescription") {
    mpd_elem->service_descriptions_.push_back(
        static_cast<ServiceDescription*>(child));
  } else if (child_name == "InitializationSet") {
    mpd_elem->initialization_sets_.push_back(
        static_cast<InitializationSet*>(child));
  } else if (child_name == "InitializationGroup") {
    mpd_elem->initialization_groups_.push_back(
        static_cast<UIntVWithID*>(child));
  } else if (child_name == "InitializationPresentation") {
    mpd_elem->initialization_presentations_.push_back(
        static_cast<UIntVWithID*>(child));
  } else if (child_name == "ContentProtection") {
    mpd_elem->content_protections_.push_back(
        static_cast<ContentProtection*>(child));
  } else if (child_name == "Period") {
    mpd_elem->periods_.push_back(static_cast<Period*>(child));
  } else if (child_name == "Metrics") {
    mpd_elem->metrics_.push_back(static_cast<Metrics*>(child));
  } else if (child_name == "EssentialProperty") {
    mpd_elem->essential_properties_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "SupplementalProperty") {
    mpd_elem->supplemental_properties_.push_back(
        static_cast<Descriptor*>(child));
  } else if (child_name == "UTCTiming") {
    mpd_elem->utc_timings_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "LeapSecondInformation") {
    mpd_elem->leap_second_information_ =
        static_cast<LeapSecondInformation*>(child);
  } else {
    ElementBaseParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* MPDElementParser::CreateChildParser(const std::string &name,
    ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "ProgramInformation") {
    parser = std::make_unique < ProgramInformationElementParser
        > (name, parent);
  } else if (name == "BaseURL") {
    parser = std::make_unique < BaseURLElementParser > (name, parent);
  } else if (name == "Location") {
    return this;
  } else if (name == "PatchLocation") {
    parser = std::make_unique < PatchLocationElementParser > (name, parent);
  } else if (name == "ServiceDescription") {
    parser = std::make_unique < ServiceDescriptionElementParser
        > (name, parent);
  } else if (name == "InitializationSet") {
    parser = std::make_unique < InitializationSetElementParser > (name, parent);
  } else if (name == "InitializationGroup") {
    parser = std::make_unique < UIntVWithIDElementParser > (name, parent);
  } else if (name == "InitializationPresentation") {
    parser = std::make_unique < UIntVWithIDElementParser > (name, parent);
  } else if (name == "Period") {
    parser = std::make_unique < PeriodElementParser > (name, parent);
  } else if (name == "ContentProtection") {
    parser = std::make_unique < ContentProtectionElementParser > (name, parent);
  } else if (name == "Metrics") {
    parser = std::make_unique < MetricsElementParser > (name, parent);
  } else if (name == "EssentialProperty") {
    parser = std::make_unique < DescriptorElementParser > (name, parent);
  } else if (name == "SupplementalProperty") {
    parser = std::make_unique < DescriptorElementParser > (name, parent);
  } else if (name == "UTCTiming") {
    parser = std::make_unique < DescriptorElementParser > (name, parent);
  } else if (name == "LeapSecondInformation") {
    parser = std::make_unique < LeapSecondInformationElementParser
        > (name, parent);
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
