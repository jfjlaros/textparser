#include <Arduino.h>

#include "textparser.h"


void TextParser::consume_(char** line) {
  for (char const *c = delimiter_; *c; c++) {
    if (not **line or **line != *c) {
      return;
    }
    (*line)++;
  }
}


/*! Constructor.
 *
 * \param delimiter Field delimiter.
 */
TextParser::TextParser(char const* delimiter)
  : delimiter_(delimiter), eol_("") {}

/*! Constructor.
 *
 * \param delimiter Field delimiter.
 * \param end Line delimiter.
 */
TextParser::TextParser(char const* delimiter, char const* eol)
  : delimiter_(delimiter), eol_(eol) {}


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
  result = strtof(*line, line);
}

/*! Parse a C string.
 *
 * \param result Result.
 * \param line Pointer to C string.
 */
void TextParser::parse(char* result, char** line) {
  char* end = strstr(*line, delimiter_);
  if (not end and *eol_) {
    end = strstr(*line, eol_);
  }
  while (**line and *line != end) {
    *result = **line;
    result++;
    (*line)++;
  }
  *result = 0;
}
