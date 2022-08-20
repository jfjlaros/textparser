#pragma once

#include <stdlib.h>
#include <string.h>

typedef char const* ccp;  //!< Pointer to a constant string.
typedef ccp const ccpc;   //!< Constant pointer to a constant string.

/*! Integer number.
 *
 * \tparam T Integer type.
 * \tparam base Integer base.
 */
template <class T, size_t base>
struct Number {
  T value;  //!< Value.
};

/*! Boolean.
 *
 * \tparam truth Truth value.
 */
template <ccp truth>
struct Bool {
  bool value;  //!< Value.
};

/*! Line based text parser. */
class TextParser {
  ccpc delimiter_;
  ccpc eol_;

  void consume_(ccp*) const;
  ccp findEnd_(ccp) const;

  template <class T>
    void parseField_(ccp*, T&) const;

  inline void parseLine_(ccp*) const;
  template <size_t n, class... Tail>
    void parseLine_(ccp*, char (&)[n], Tail&...) const;
  template <class T, size_t n, class... Tail>
    void parseLine_(ccp*, T (&)[n], Tail&...) const;
  template <class H, class... Tail>
    void parseLine_(ccp*, H&, Tail&...) const;

public:
  /*! Constructor.
   *
   * \param[in] delimiter Field delimiter.
   */
  TextParser(ccpc delimiter) : delimiter_(delimiter), eol_(nullptr) {}

  /*! \copydoc TextParser(ccpc)
   *
   * \param[in] eol Line delimiter.
   */
  TextParser(ccpc delimiter, ccpc eol) : delimiter_(delimiter), eol_(eol) {}


  /*! Parse a field.
   *
   * \param[out] result Result.
   * \param[in] begin Pointer to C string.
   * \param[in] end Pointer to end of C string.
   */
  void parse(char& result, ccpc begin, ccpc end) const;

  /*! \copydoc parse(char&, ccpc, ccpc) const */
  void parse(double& result, ccpc begin, ccpc end) const;

  /*! \copydoc parse(char&, ccpc, ccpc) const */
  void parse(float& result, ccpc begin, ccpc end) const;

  /*!
   * \tparam n String length.
   *
   * \copydoc parse(char&, ccpc, ccpc) const
   */
  template <size_t n>
    void parse(char (&result)[n], ccpc begin, ccpc end) const;

  /*!
   * \tparam truth Truth value.
   *
   * \copydoc parse(char&, ccpc, ccpc) const
   */
  template <ccp truth>
    void parse(Bool<truth>& result, ccpc begin, ccpc end) const;

  /*!
   * \tparam T Integer type.
   * \tparam base Integer base.
   *
   * \copydoc parse(char&, ccpc, ccpc) const
   */
  template <class T, size_t base>
    void parse(Number<T, base>& result, ccpc begin, ccpc end) const;

  /*!
   * \tparam T Integer type.
   *
   * \copydoc parse(char&, ccpc, ccpc) const
   */
  template <class T>
    void parse(T& result, ccpc begin, ccpc end) const;


  /*! Parse a line.
   *
   * \tparam Args Output variable types.
   *
   * \param[in] line Line to be parsed.
   * \param[out] args Variables to hold the parsed data.
   */
  template <class... Args>
    void parseLine(ccpc line, Args&... args) const;
};


inline void TextParser::parseLine_(ccp*) const {}

template <class T>
void TextParser::parseField_(ccp* line, T& data) const {
  ccpc end = findEnd_(*line);
  parse(data, *line, end);
  *line = end;
  consume_(line);
}

template <size_t n, class... Tail>
void TextParser::parseLine_(ccp* line, char (&h)[n], Tail&... tail) const {
  parseField_(line, h);
  parseLine_(line, tail...);
}

template <class T, size_t n, class... Tail>
void TextParser::parseLine_(ccp* line, T (&h)[n], Tail&... tail) const {
  for (size_t i = 0; i < n; i++) {
    parseField_(line, h[i]);
  }
  parseLine_(line, tail...);
}

template <class H, class... Tail>
void TextParser::parseLine_(ccp* line, H& h, Tail&... tail) const {
  parseField_(line, h);
  parseLine_(line, tail...);
}


template <size_t n>
void TextParser::parse(char (&result)[n], ccpc begin, ccpc end) const {
  char* p = result;
  for (ccp q = begin; p < result + n - 1 and q < end; p++, q++) {
    *p = *q;
  }
  *p = 0;
}

template <ccp truth>
void TextParser::parse(Bool<truth>& result, ccpc begin, ccpc end) const {
  ccp p;
  ccp q;
  for (p = begin, q = truth; p < end and *q and *p == *q; p++, q++);
  result.value = p == end and not *q;
}

template <class T, size_t base>
void TextParser::parse(Number<T, base>& result, ccpc begin, ccpc) const {
  result.value = strtol(begin, nullptr, base);
}

template <class T>
void TextParser::parse(T& result, ccpc begin, ccpc) const {
  result = strtol(begin, nullptr, 10);
}


template <class... Args>
void TextParser::parseLine(ccpc line, Args&... args) const {
  ccp line_ = line;
  parseLine_(&line_, args...);
}
