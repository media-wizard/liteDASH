/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "contentcomponent_element_parser.h"
#include "contentcomponent.h"

#include "descriptor.h"
#include "descriptor_element_parser.h"
#include "utils.h"


namespace dash {
namespace mpd {

bool ContentComponentElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  ContentComponent *elem = static_cast<ContentComponent*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("id") {
      elem->id_ = strtoul(attrib[i + 1], NULL, 10);
    } else IF_ATTRIB_MATCHES("lang") {
      elem->lang_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("contentType") {
      elem->content_type_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("par") {
      elem->par_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("tag") {
      elem->tag_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      ElementBaseParser::ParseStart(element_name, elem_out, tmp_attribs);
    }
  }

  return true;
}

ElementBase* ContentComponentElementParser::CreateElement(
    const std::string &element) const {
  return new ContentComponent();
}

void ContentComponentElementParser::AttachChildElementToParent(
    ElementBase *parent, ElementBase *child) {
  ContentComponent *cc_elem = static_cast<ContentComponent*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "Accessibility") {
    cc_elem->accessibility_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "Role") {
    cc_elem->role_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "Rating") {
    cc_elem->rating_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "Viewpoint") {
    cc_elem->viewpoint_.push_back(static_cast<Descriptor*>(child));
  } else {
    ElementBaseParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* ContentComponentElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser = nullptr;
  if (name == "Accessibility" || name == "Role" || name == "Rating"
      || name == "Viewpoint") {
    parser = std::make_unique < DescriptorElementParser > (name, parent);
  } else {
    return ElementBaseParser::CreateChildParser(name, parent);
  }

  ElementBaseParser *raw_parser = parser.get();
  InsertChildParser(name, std::move(parser));
  return raw_parser;
}

} // namespace mpd
} // namespace dash
