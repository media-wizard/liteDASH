/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "representationbase_element_parser.h"
#include "representationbase.h"

#include "contentpopularityrate_element_parser.h"
#include "contentpopularityrate.h"
#include "contentprotection_element_parser.h"
#include "contentprotection.h"
#include "descriptor_element_parser.h"
#include "descriptor.h"
#include "eventstream_element_parser.h"
#include "eventstream.h"
#include "label_element_parser.h"
#include "label.h"
#include "producerreferencetime_element_parser.h"
#include "producerreferencetime.h"
#include "randomaccess_element_parser.h"
#include "randomaccess.h"
#include "resync_element_parser.h"
#include "resync.h"
#include "switching_element_parser.h"
#include "switching.h"

#include "utils.h"


namespace dash {
namespace mpd {

bool RepresentationBaseElementParser::ParseStart(
    const std::string &element_name, ElementBase *elem_out,
    const char **attrib) {
  RepresentationBase *elem = static_cast<RepresentationBase*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("profiles") {
      Utils::SplitStrValues(attrib[i + 1], ',', elem->profiles_);
    } else IF_ATTRIB_MATCHES("width") {
      elem->width_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("height") {
      elem->height_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("sar") {
      elem->sar_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("frameRate") {
      elem->frame_rate_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("audioSamplingRate") {
      elem->audio_sampling_rate_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("mimeType") {
      elem->mime_type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("segmentProfiles") {
      Utils::SplitStrValues(attrib[i + 1], ',', elem->segment_profiles_);
    } else IF_ATTRIB_MATCHES("codecs") {
      Utils::SplitStrValues(attrib[i + 1], ',', elem->codecs_);
    } else IF_ATTRIB_MATCHES("containerProfiles") {
      Utils::SplitStrValues(attrib[i + 1], ',', elem->container_profiles_);
    } else IF_ATTRIB_MATCHES("maximumSAPPeriod") {
      elem->maximum_SAP_period_ = strtod(attrib[i + 1], NULL);
    } else IF_ATTRIB_MATCHES("startWithSAP") {
      elem->start_with_SAP_ = (uint8_t)(strtoul(attrib[i + 1], NULL, 10));
    } else IF_ATTRIB_MATCHES("maxPlayoutRate") {
      elem->max_playout_rate_ = strtod(attrib[i + 1], NULL);
    } else IF_ATTRIB_MATCHES("codingDependency") {
      elem->coding_dependency_ = Utils::ConvertToBool(attrib[i + 1]);
    } else IF_ATTRIB_MATCHES("scanType") {
      elem->scan_type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("selectionPriority") {
      elem->selection_priority_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("tag") {
      elem->tag_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }
  return true;
}

void RepresentationBaseElementParser::AttachChildElementToParent(
    ElementBase *parent, ElementBase *child) {
  RepresentationBase *rb_elem = static_cast<RepresentationBase*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "FramePacking") {
    rb_elem->frame_packing_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "AudioChannelConfiguration") {
    rb_elem->audio_channel_configuration_.push_back(
        static_cast<Descriptor*>(child));
  } else if (child_name == "ContentProtection") {
    rb_elem->content_protections_.push_back(
        static_cast<ContentProtection*>(child));
  } else if (child_name == "OutputProtection") {
    rb_elem->output_protection_ = static_cast<Descriptor*>(child);
  } else if (child_name == "EssentialProperty") {
    rb_elem->essential_properties_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "SupplementalProperty") {
    rb_elem->supplemental_properties_.push_back(
        static_cast<Descriptor*>(child));
  } else if (child_name == "InbandEventStream") {
    rb_elem->event_streams_.push_back(static_cast<EventStream*>(child));
  } else if (child_name == "Switching") {
    rb_elem->switchings_.push_back(static_cast<Switching*>(child));
  } else if (child_name == "RandomAccess") {
    rb_elem->random_accesses_.push_back(static_cast<RandomAccess*>(child));
  } else if (child_name == "GroupLabel") {
    rb_elem->group_labels_.push_back(static_cast<Label*>(child));
  } else if (child_name == "Label") {
    rb_elem->labels_.push_back(static_cast<Label*>(child));
  } else if (child_name == "ProducerReferenceTime") {
    rb_elem->producer_reference_times_.push_back(
        static_cast<ProducerReferenceTime*>(child));
  } else if (child_name == "ContentPopularityRate") {
    rb_elem->content_popularity_rates_.push_back(
        static_cast<ContentPopularityRate*>(child));
  } else if (child_name == "Resync") {
    rb_elem->resyncs_.push_back(static_cast<Resync*>(child));
  } else {
    ElementBaseParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* RepresentationBaseElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "FramePacking" || name == "AudioChannelConfiguration"
      || name == "OutputProtection" || name == "EssentialProperty"
      || name == "SupplementalProperty") {
    parser = std::make_unique < DescriptorElementParser > (name, parent);
  } else if (name == "ContentProtection") {
    parser = std::make_unique < ContentProtectionElementParser > (name, parent);
  } else if (name == "InbandEventStream") {
    parser = std::make_unique < EventStreamElementParser > (name, parent);
  } else if (name == "Switching") {
    parser = std::make_unique < SwitchingElementParser > (name, parent);
  } else if (name == "RandomAccess") {
    parser = std::make_unique < RandomAccessElementParser > (name, parent);
  } else if (name == "GroupLabel" || name == "Label") {
    parser = std::make_unique < LabelElementParser > (name, parent);
  } else if (name == "ProducerReferenceTime") {
    parser = std::make_unique < ProducerReferenceTimeElementParser
        > (name, parent);
  } else if (name == "ContentPopularityRate") {
    parser = std::make_unique < ContentPopularityRateElementParser
        > (name, parent);
  } else if (name == "Resync") {
    parser = std::make_unique < ResyncElementParser > (name, parent);
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
