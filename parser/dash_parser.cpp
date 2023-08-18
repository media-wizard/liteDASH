/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#include "dash_parser.h"
#include "elementbase.h"
#include "elementbase_parser.h"
#include "mpd_element_parser.h"

#include "utils.h"

#include <expat.h>
#include <iostream>
#include <stack>

namespace dash {
namespace mpd {

class DASHParser::InternalParser {
  public:
    std::unique_ptr<MPD> Parse(char *buff, size_t buff_size, const std::string &mpd_url);

  public:
    InternalParser();
    static void OnElementStart(void *usr_data, const char *element,
        const char **attribute);
    static void OnElementEnd(void *usr_data, const char *element);
    static void OnTextData(void *data, const char *content, int length);

    ElementBaseParser *GetElementParser(const std::string &name);
    void ClearInternalStates();
    void PushParserState(ElementBaseParser*, ElementBase*);
    void PopElement();
    const std::string &GetAttribute(const std::string &key);
    std::unique_ptr<ElementBaseParser> root_parser_ = nullptr;
    std::unique_ptr<MPD> current_dash_tree_ = nullptr;
    using ParserState = std::pair<ElementBaseParser *, ElementBase *>;
    std::stack<ParserState> active_parser_stack_;
    std::string current_sub_element_;
    bool not_an_mpd_ = false;
    std::string mpd_path_;
    GetExternalAttributes get_attrib_cb_;
};

DASHParser::DASHParser() :
    pImpl_(new InternalParser()) {
}

DASHParser::~DASHParser() {
  delete pImpl_;
}

std::unique_ptr<MPD> DASHParser::Parse(char *buff, size_t buff_size, const std::string &mpd_url) {
  return pImpl_->Parse(buff, buff_size, mpd_url);
}

DASHParser::InternalParser::InternalParser() {
  get_attrib_cb_ = std::bind(&DASHParser::InternalParser::GetAttribute, std::ref(*this), std::placeholders::_1);
}

ElementBaseParser* DASHParser::InternalParser::GetElementParser(
    const std::string &name) {
  ElementBaseParser *new_parser = nullptr;
  if (!active_parser_stack_.empty()) {
    ParserState &top_state = active_parser_stack_.top();
    new_parser = top_state.first->GetChildParser(name, top_state.first);
  } else if (name == "MPD") { //Check whether XML starts with the element "MPD" or not.
    // Parser for the root element
    root_parser_ = std::make_unique < MPDElementParser > (name, nullptr);
    new_parser = root_parser_.get();
  } else {
    std::cout << "Wrong XML. Starts with element[" << name << "]\n";
    new_parser = nullptr;
  }
  return new_parser;
}

void DASHParser::InternalParser::ClearInternalStates() {
  current_dash_tree_ = nullptr;
  std::stack<ParserState> fresh_stack;
  active_parser_stack_.swap(fresh_stack);
  current_sub_element_.clear();
  not_an_mpd_ = false;
  mpd_path_.clear();
}

void DASHParser::InternalParser::PushParserState(
    ElementBaseParser *cur_elem_parser, ElementBase *current_element) {
  ParserState state(cur_elem_parser, current_element);
  active_parser_stack_.push(state);
}

void DASHParser::InternalParser::PopElement() {
  if (!active_parser_stack_.empty()) {
    active_parser_stack_.pop();
  }
}

const std::string &DASHParser::InternalParser::GetAttribute(const std::string &key) {
  static std::string dummy_str("");
  if (key == "mpd_path") {
    return mpd_path_;
  }
  return dummy_str;
}

void DASHParser::InternalParser::OnElementStart(void *usr_data,
                                                const char *element,
                                                const char **attribute) {
  DASHParser::InternalParser *this_parser =
      (DASHParser::InternalParser*) usr_data;
  ElementBaseParser *cur_elem_parser = nullptr;
  ElementBase *cur_element = nullptr;

  if (this_parser->not_an_mpd_) {
    return;
  }

  if (!(this_parser->active_parser_stack_.empty())) {
    ParserState &top_state = this_parser->active_parser_stack_.top();
    cur_elem_parser = top_state.first;
    cur_element = top_state.second;
  }

  ElementBaseParser *new_elem_parser = this_parser->GetElementParser(element);
  if (new_elem_parser) {
    ElementBase *new_element;
    if (new_elem_parser == cur_elem_parser) {
      //Trivial subelements can be parsed by parent; only text data expected
      new_element = cur_element;
      this_parser->current_sub_element_ = element;
    } else {
      new_element = new_elem_parser->CreateElement(element);
      if (nullptr == this_parser->current_dash_tree_) {
        this_parser->current_dash_tree_ = std::unique_ptr < MPD
            > (static_cast<MPD*>(new_element));
      } else {
        cur_elem_parser->AttachChildElementToParent(cur_element, new_element);
      }
      new_elem_parser->ParseStart(element, new_element, attribute);
    }
    this_parser->PushParserState(new_elem_parser, new_element);
  } else {
    // XML_StopParser(this_parser->xpat_parser_, XML_FALSE);
    // XML_StopParser not working. Workaround to Avoid subsequent parsing
    this_parser->not_an_mpd_ = true;
  }
}

void DASHParser::InternalParser::OnElementEnd(void *usr_data,
    const char *name) {
  DASHParser::InternalParser *this_parser =
      (DASHParser::InternalParser*) usr_data;
  ElementBaseParser *element_parser = nullptr;
  ElementBase *cur_element;

  if (this_parser->not_an_mpd_) {
    return;
  }

  if (!(this_parser->active_parser_stack_.empty())) {
    ParserState &top_state = this_parser->active_parser_stack_.top();
    element_parser = top_state.first;
    cur_element = top_state.second;
  }
  if (element_parser) {
    element_parser->ParseEnd(name, cur_element, this_parser->get_attrib_cb_);
    this_parser->PopElement();
  }
  this_parser->current_sub_element_.clear();
}

void DASHParser::InternalParser::OnTextData(void *usr_data, const char *content,
    int length) {
  if (length > 1 || 0xa != content[0]) { //Ignore line feeds
    DASHParser::InternalParser *this_parser =
        (DASHParser::InternalParser*) usr_data;
    ElementBaseParser *element_parser = nullptr;
    ElementBase *cur_element;

    if (this_parser->not_an_mpd_) {
      return;
    }

    if (!(this_parser->active_parser_stack_.empty())) {
      ParserState &top_state = this_parser->active_parser_stack_.top();
      element_parser = top_state.first;
      cur_element = top_state.second;
    }
    if (element_parser) {
      element_parser->ParseTextData(cur_element,
          this_parser->current_sub_element_, content, length);
    }
  }
}

std::unique_ptr<MPD> DASHParser::InternalParser::Parse(char *buff,
    size_t buff_size, const std::string &mpd_url) {
  XML_Parser xpat_parser = XML_ParserCreate(NULL);
  XML_SetUserData(xpat_parser, this);
  XML_SetElementHandler(xpat_parser, DASHParser::InternalParser::OnElementStart,
      DASHParser::InternalParser::OnElementEnd);
  XML_SetCharacterDataHandler(xpat_parser,
      DASHParser::InternalParser::OnTextData);

  mpd_path_ = Utils::GetBasePath(mpd_url);

  /* parse the xml */
  if (XML_Parse(xpat_parser, buff, buff_size, XML_TRUE) == XML_STATUS_ERROR) {
    printf("Error: %s\n", XML_ErrorString(XML_GetErrorCode(xpat_parser)));
    ClearInternalStates();
    XML_ParserFree(xpat_parser);
    return nullptr;
  }

  XML_ParserFree(xpat_parser);
  std::unique_ptr<MPD> mpdTree = std::move(current_dash_tree_);
  ClearInternalStates();

  return mpdTree;
}

} // namespace mpd
} // namespace dash
