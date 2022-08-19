#pragma once

#include <stdlib.h>
#include <string.h>

typedef char const* ccp;
typedef ccp const ccpc;

/*! Line based text parser. */
class TextParser {
  ccpc delimiter_;
  ccpc eol_;
  ccpc truth_;

  void consume_(ccp*) const;
  ccp findEnd_(ccp) const;

  template <class T>
    void parseField_(ccp*, T&) const;

  inline void parseLine_(ccp*) const;
  template <size_t N, class... Tail>
    void parseLine_(ccp*, char (&)[N], Tail&...) const;
  template <class T, size_t N, class... Tail>
    void parseLine_(ccp*, T (&)[N], Tail&...) const;
  template <class H, class... Tail>
    void parseLine_(ccp*, H&, Tail&...) const;

public:
  TextParser(ccpc);
  TextParser(ccpc, ccpc);
  TextParser(ccpc, ccpc, ccpc);

  void parse(bool&, ccpc, ccpc) const;
  void parse(char&, ccpc, ccpc) const;
  void parse(double&, ccpc, ccpc) const;
  void parse(float&, ccpc, ccpc) const;
  template <size_t N>
    void parse(char (&)[N], ccpc, ccpc) const;
  template <class T>
    void parse(T&, ccpc, ccpc) const;

  template <class... Args>
    void parseLine(ccpc, Args&...) const;
};


inline void TextParser::parseLine_(ccp*) const {}

template <class T>
void TextParser::parseField_(ccp* line, T& data) const {
  ccpc end = findEnd_(*line);
  parse(data, *line, end);
  *line = end;
  consume_(line);
}

template <size_t N, class... Tail>
void TextParser::parseLine_(ccp* line, char (&h)[N], Tail&... tail) const {
  parseField_(line, h);
  parseLine_(line, tail...);
}

template <class T, size_t N, class... Tail>
void TextParser::parseLine_(ccp* line, T (&h)[N], Tail&... tail) const {
  for (size_t i = 0; i < N; i++) {
    parseField_(line, h[i]);
  }
  parseLine_(line, tail...);
}

template <class H, class... Tail>
void TextParser::parseLine_(ccp* line, H& h, Tail&... tail) const {
  parseField_(line, h);
  parseLine_(line, tail...);
}


/*! Parse a C string.
 *
 * \param result Result.
 * \param begin Pointer to C string.
 * \param end Pointer to end of C string.
 */
template <size_t N>
void TextParser::parse(char (&result)[N], ccpc begin, ccpc end) const {
  char* p = result;
  for (ccp q = begin; p < result + N - 1 and q < end; p++, q++) {
    *p = *q;
  }
  *p = 0;
}

/*! Parse an integer type.
 *
 * \param result Result.
 * \param begin Pointer to C string.
 * \param end Pointer to end of C string.
 */
template <class T>
void TextParser::parse(T& result, ccpc begin, ccpc) const {
  result = strtol(begin, nullptr, 10);
}


/*! Parse a line.
 *
 * \param line Line to be parsed.
 * \param args Variables to hold the parsed data.
 */
template <class... Args>
void TextParser::parseLine(ccpc line, Args&... args) const {
  ccp line_ = line;
  parseLine_(&line_, args...);
}
