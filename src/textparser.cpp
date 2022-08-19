#include "textparser.h"


void TextParser::consume_(ccp* line) const {
  for (ccp p = delimiter_; *p and **line and **line == *p; p++, (*line)++);
}

ccp TextParser::findEnd_(ccp line) const {
  ccp end = strstr(line, delimiter_);
  if (not (end or (eol_ and (end = strstr(line, eol_))))) {
    return line + strlen(line);
  }
  return end;
}


/*! Constructor.
 *
 * \param delimiter Field delimiter.
 */
TextParser::TextParser(ccpc delimiter)
  : delimiter_(delimiter), eol_(nullptr), truth_(nullptr) {}

/*! Constructor.
 *
 * \param delimiter Field delimiter.
 * \param eol Line delimiter.
 */
TextParser::TextParser(ccpc delimiter, ccpc eol)
  : delimiter_(delimiter), eol_(eol), truth_(nullptr) {}

/*! Constructor.
 *
 * \param delimiter Field delimiter.
 * \param eol Line delimiter.
 * \param truth Truth representation.
 */
TextParser::TextParser(ccpc delimiter, ccpc eol, ccpc truth)
  : delimiter_(delimiter), eol_(eol), truth_(truth) {}


/*! Parse a bool.
 *
 * \param result Result.
 * \param begin Pointer to C string.
 * \param end Pointer to end of C string.
 */
void TextParser::parse(bool& result, ccpc begin, ccpc end) const {
  if (truth_) {
    ccp p = begin;
    for (ccp q = truth_; p < end and *q and *p == *q; p++, q++);
    result = p == end;
    return;
  }
  result = strtol(begin, nullptr, 10);
}

/*! Parse a char.
 *
 * \param result Result.
 * \param begin Pointer to C string.
 * \param end Pointer to end of C string.
 */
void TextParser::parse(char& result, ccpc begin, ccpc end) const {
  result = 0;
  if (begin < end) {
    result = *begin;
  }
}

/*! Parse a double.
 *
 * \param result Result.
 * \param begin Pointer to C string.
 * \param end Pointer to end of C string.
 */
void TextParser::parse(double& result, ccpc begin, ccpc) const {
  result = strtod(begin, nullptr);
}

/*! Parse a float.
 *
 * \param result Result.
 * \param begin Pointer to C string.
 * \param end Pointer to end of C string.
 */
void TextParser::parse(float& result, ccpc begin, ccpc) const {
  result = strtod(begin, nullptr);
}
