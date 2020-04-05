/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "preselection_element_parser.h"
#include "preselection.h"

#include "descriptor_element_parser.h"
#include "descriptor.h"
#include "utils.h"


namespace dash {
namespace mpd {

bool PreselectionElementParser::ParseStart(const std::string &element_name,
    ElementBase *elem_out, const char **attrib) {
  Preselection *elem = static_cast<Preselection*>(elem_out);
  for (int i = 0; attrib[i]; i += 2) {
    IF_ATTRIB_MATCHES("id") {
      elem->id_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("preselectionComponents") {
      Utils::SplitStrValues(attrib[i + 1], ',', elem->preselection_components_);
    } else IF_ATTRIB_MATCHES("lang") {
      elem->lang_ = attrib[i + 1];
    } else IF_ATTRIB_MATCHES("order") {
      elem->order_ = attrib[i + 1];
    } else {
      const char *tmp_attribs[3] = { attrib[i], attrib[i + 1], nullptr };
      RepresentationBaseElementParser::ParseStart(element_name, elem_out,
          tmp_attribs);
    }
  }
  return true;
}

ElementBase* PreselectionElementParser::CreateElement(
    const std::string &element) const {
  return new Preselection();
}

void PreselectionElementParser::AttachChildElementToParent(ElementBase *parent,
    ElementBase *child) {
  Preselection *elem = static_cast<Preselection*>(parent);
  const std::string &child_name = child->GetName();
  if (child_name == "Accessibility") {
    elem->accessibility_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "Role") {
    elem->role_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "Rating") {
    elem->rating_.push_back(static_cast<Descriptor*>(child));
  } else if (child_name == "Viewpoint") {
    elem->viewpoint_.push_back(static_cast<Descriptor*>(child));
  } else {
    RepresentationBaseElementParser::AttachChildElementToParent(parent, child);
  }
}

ElementBaseParser* PreselectionElementParser::CreateChildParser(
    const std::string &name, ElementBaseParser *parent) {
  std::unique_ptr<ElementBaseParser> parser;
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
