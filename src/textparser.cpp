#include "textparser.h"


TextParser::TextParser(CCPC delimiter)
    : delimiter_ {delimiter} {}

TextParser::TextParser(CCPC delimiter, CCPC eol)
    : delimiter_ {delimiter}, eol_ {eol} {}


void TextParser::parse(char& result, CCPC begin, CCPC end) const {
  result = 0;
  if (begin < end) {
    result = *begin;
  }
}

void TextParser::parse(double& result, CCPC begin, CCPC) const {
  result = strtod(begin, nullptr);
}

void TextParser::parse(float& result, CCPC begin, CCPC) const {
  result = strtod(begin, nullptr);
}


void TextParser::consume_(CCP* line) const {
  for (CCP p {delimiter_}; *p and **line and *p == **line; ++p, ++(*line));
}

CCP TextParser::findEnd_(CCP line) const {
  CCP end {strstr(line, delimiter_)};
  if (not (end or (eol_ and (end = strstr(line, eol_))))) {
    return line + strlen(line);
  }
  return end;
}
