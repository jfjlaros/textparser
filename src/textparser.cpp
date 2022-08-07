#include <Arduino.h>

#include "textparser.h"


/*! Constructor.
 *
 * \param delimiter Field delimiter.
 */
TextParser::TextParser(char const* delimiter) : delimiter_(delimiter) {}


/*! Parse an integer.
 *
 * \param result Result.
 * \param endptr Pointer to C string.
 */
void TextParser::parse(int& result, char** endptr) {
  result = strtol(*endptr, endptr, 10);
}

/*! Parse a double.
 *
 * \param result Result.
 * \param endptr Pointer to C string.
 */
void TextParser::parse(double& result, char** endptr) {
  result = strtod(*endptr, endptr);
}

/*! Parse a C string.
 *
 * \param result Result.
 * \param endptr Pointer to C string.
 */
void TextParser::parse(char* result, char** endptr) {
  char* end = strstr(*endptr, delimiter_);
  while (**endptr and *endptr != end) {
    *result = **endptr;
    result++;
    (*endptr)++;
  }
  *result = 0;
}
