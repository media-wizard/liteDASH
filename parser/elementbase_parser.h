/*******************************************************************************
 * Copyright 2020 Vinod Damodaran
 *
 * Use of this source code is governed by a MIT-style license that can be found
 * in the LICENSE file.
 *******************************************************************************/

#ifndef DASH_ELEMENTBASE_PARSER_H_
#define DASH_ELEMENTBASE_PARSER_H_

#define IF_ATTRIB_MATCHES(pattern) if (!std::strcmp(pattern,  attrib[i]))

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <cstring>

namespace dash {
namespace mpd {

class ElementBase;

typedef std::function<const std::string&(const std::string&)> GetExternalAttributes;

class ElementBaseParser {
  public:
    ElementBaseParser(const std::string &element_name,
        ElementBaseParser *parent);
    virtual ~ElementBaseParser();

    virtual bool ParseStart(const std::string &element_name,
        ElementBase *elem_out, const char **attrib);
    virtual bool ParseEnd(const std::string &element_name,
        ElementBase *elem_out, const GetExternalAttributes &get_attribs);
    virtual bool ParseTextData(ElementBase *elem_out,
        const std::string sub_element, const char *content, int length);
    virtual ElementBase* CreateElement(const std::string &element) const;
    virtual ElementBaseParser* GetChildParser(const std::string &name,
        ElementBaseParser *parent);
    void InsertChildParser(const std::string &name,
        std::unique_ptr<ElementBaseParser> child);
    virtual void AttachChildElementToParent(ElementBase *parent,
        ElementBase *child);
    ElementBaseParser* GetParent() const;
    const std::string& GetElementName() const;

  protected:
    virtual ElementBaseParser* CreateChildParser(const std::string &name,
        ElementBaseParser *parent);
    std::string element_name_;
    ElementBaseParser *parent_;
    std::unordered_map<std::string, std::unique_ptr<ElementBaseParser>> children_;
};

} // namespace mpd
} // namespace dash

#endif /* DASH_ELEMENTBASE_PARSER_H_ */
