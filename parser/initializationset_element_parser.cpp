/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "initializationset_element_parser.h"
#include "initializationset.h"

#include "descriptor.h"
#include "descriptor_element_parser.h"
#include "utils.h"


namespace dash {
namespace mpd {

bool InitializationSetElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  InitializationSet *elem = static_cast<InitializationSet*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("xlink:href") {
      elem->xlink_href_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("xlink:actuate") {
      elem->xlink_actuate_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("xlink:type") {
      elem->xlink_type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("id") {
      elem->id_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("inAllPeriods") {
      elem->in_all_periods_ = Utils::ConvertToBool(attrib[i + 1]);
    } else IF_ATTRIB_MATCHES("contentType") {
      elem->content_type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("par") {
      elem->par_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("maxWidth") {
      elem->max_width_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("maxHeight") {
      elem->max_height_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("maxFrameRate") {
      elem->max_frame_rate_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("initialization") {
      elem->initialization_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      RepresentationBaseElementParser::ParseStart(element_name, elem_out,
          tmp_attribs);
    }
  }

  return true;
}

ElementBase* InitializationSetElementParser::CreateElement(
    const std::string &element) const {
  return new InitializationSet();
}

void InitializationSetElementParser::AttachChildElementToParent(
    ElementBase *parent, ElementBase *child) {
  InitializationSet *is_elem = static_cast<InitializationSet*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "Accessibility") {
    is_elem->accessibility_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "Role") {
    is_elem->role_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "Rating") {
    is_elem->rating_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "Viewpoint") {
    is_elem->viewpoint_.push_back(static_cast<Descriptor*>(child));
  } else {
    RepresentationBaseElementParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* InitializationSetElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "Accessibility" || name == "Role" || name == "Rating"
      || name == "Viewpoint") {
    parser = std::make_unique < DescriptorElementParser > (name, parent);
  } else {
    return RepresentationBaseElementParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
