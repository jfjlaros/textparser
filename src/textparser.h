#pragma once

#include <stdlib.h>
#include <string.h>


/*! Line based text parser. */
class TextParser {
  char const* delimiter_;
  char const* eol_;
  char const* truth_;

  void consume_(char**);
  char* findEnd_(char*);
  inline void parseLine_(char**);
  template <class H, class... Tail>
    void parseLine_(char**, H&, Tail&...);

public:
  TextParser(char const*);
  TextParser(char const*, char const*);
  TextParser(char const*, char const*, char const*);

  void parse(bool&, char**);
  void parse(char&, char**);
  void parse(double&, char**);
  void parse(float&, char**);
  template <class T>
    void parse(T&, char**);
  template <size_t N>
    void parse(char (&)[N], char**);
  template <class T, size_t N>
    void parse(T (&)[N], char**);

  template <class... Args>
    void parseLine(char const*, Args&...);
};


inline void TextParser::parseLine_(char**) {}

template <class H, class... Tail>
void TextParser::parseLine_(char** line, H& head, Tail&... tail) {
  parse(head, line);
  consume_(line);
  parseLine_(line, tail...);
}


/*! Parse an integer type.
 *
 * \param result Result.
 * \param line Pointer to C string.
 */
template <class T>
void TextParser::parse(T& result, char** line) {
  result = strtol(*line, line, 10);
}

/*! Parse an C string.
 *
 * \param result Result.
 * \param line Pointer to C string.
 */
template <size_t N>
void TextParser::parse(char (&result)[N], char** line) {
  char* end = findEnd_(*line);

  char* result_ = result;
  for (size_t i = 0; i < N - 1 and *line < end; i++, result_++, (*line)++) {
    *result_ = **line;
  }
  *result_ = 0;

  *line = end;
}

/*! Parse an array.
  *
  * \param result Result.
  * \param line Pointer to C string.
  */
template <class T, size_t N>
void TextParser::parse(T (&result)[N], char** line) {
  for (size_t i = 0; i < N; i++) {
    parse(result[i], line);
    consume_(line);
  }
}


/*! Parse a line.
 *
 * \param line Line to be parsed.
 * \param args Variables to hold the parsed data.
 */
template <class... Args>
void TextParser::parseLine(char const* line, Args&... args) {
  char* line_ = const_cast<char*>(line);
  parseLine_(&line_, args...);
}
