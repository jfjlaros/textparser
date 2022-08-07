#pragma once


/*! Line based text parser. */
class TextParser {
  char const* delimiter_;

  inline void parseLine_(char**);
  template <class H, class... Tail>
    void parseLine_(char**, H&, Tail&...);

public:
  TextParser(char const*);

  void parse(int&, char**);
  void parse(double&, char**);
  void parse(char*, char**);

  template <class... Args>
    void parseLine(char const*, Args&...);
};


inline void TextParser::parseLine_(char**) {}

template <class H, class... Tail>
void TextParser::parseLine_(char** endptr, H& head, Tail&... tail) {
  parse(head, endptr);
  *endptr += strlen(delimiter_);
  parseLine_(endptr, tail...);
}

/*! Parse a line.
 *
 * \param line Line to be parsed.
 * \param args Variables to hold the parsed data.
 */
template <class... Args>
void TextParser::parseLine(char const* line, Args&... args) {
  char* endptr = const_cast<char*>(line);
  parseLine_(&endptr, args...);
}
