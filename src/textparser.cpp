#include "textparser.h"


void TextParser::consume_(char** line) {
  for (char const *c = delimiter_; *c; c++) {
    if (not **line or **line != *c) {
      return;
    }
    (*line)++;
  }
}

char* TextParser::findEnd_(char* line) {
  char* end = strstr(line, delimiter_);
  if (not (end or (eol_ and (end = strstr(line, eol_))))) {
    return line + strlen(line);
  }
  return end;
}


/*! Constructor.
 *
 * \param delimiter Field delimiter.
 */
TextParser::TextParser(char const* delimiter)
  : delimiter_(delimiter), eol_(nullptr), truth_(nullptr) {}

/*! Constructor.
 *
 * \param delimiter Field delimiter.
 * \param eol Line delimiter.
 */
TextParser::TextParser(char const* delimiter, char const* eol)
  : delimiter_(delimiter), eol_(eol), truth_(nullptr) {}

/*! Constructor.
 *
 * \param delimiter Field delimiter.
 * \param eol Line delimiter.
 * \param truth Truth representation.
 */
TextParser::TextParser(
    char const* delimiter, char const* eol, char const* truth)
  : delimiter_(delimiter), eol_(eol), truth_(truth) {}


/*! Parse a bool.
 *
 * \param result Result.
 * \param line Pointer to C string.
 */
void TextParser::parse(bool& result, char** line) {
  if (truth_) {
    char* begin = *line;
    *line = findEnd_(*line);

    size_t textLen = static_cast<size_t>(*line - begin);
    result = false;
    if (strlen(truth_) == textLen) {
      result = not strncmp(begin, truth_, textLen);
    }
    return;
  }

  result = strtol(*line, line, 10);
}

/*! Parse a char.
 *
 * \param result Result.
 * \param line Pointer to C string.
 */
void TextParser::parse(char& result, char** line) {
  result = **line;
  if (**line) {
    (*line)++;
  }
}

/*! Parse a double.
 *
 * \param result Result.
 * \param line Pointer to C string.
 */
void TextParser::parse(double& result, char** line) {
  result = strtod(*line, line);
}

/*! Parse a float.
 *
 * \param result Result.
 * \param line Pointer to C string.
 */
void TextParser::parse(float& result, char** line) {
  result = strtod(*line, line);
}
