#include "textparser.h"


void TextParser::consume_(ccp* line) const {
  for (ccp p = delimiter_; *p and **line and *p == **line; p++, (*line)++);
}

ccp TextParser::findEnd_(ccp line) const {
  ccp end = strstr(line, delimiter_);
  if (not (end or (eol_ and (end = strstr(line, eol_))))) {
    return line + strlen(line);
  }
  return end;
}


bool strmatch(ccpc begin, ccpc end, ccpc str) {
  ccp p;
  ccp q;
  for (p = begin, q = str; p < end and *q and *p == *q; p++, q++);
  return p == end and not *q;
}


void TextParser::parse(char& result, ccpc begin, ccpc end) const {
  result = 0;
  if (begin < end) {
    result = *begin;
  }
}

void TextParser::parse(double& result, ccpc begin, ccpc) const {
  result = strtod(begin, nullptr);
}

void TextParser::parse(float& result, ccpc begin, ccpc) const {
  result = strtod(begin, nullptr);
}
