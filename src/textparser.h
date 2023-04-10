#pragma once

#include <string.h>

#include "texttypes.h"

/*! Line based text parser. */
class TextParser {
public:
  /*! Constructor.
   *
   * \param[in] delimiter Field delimiter.
   */
  TextParser(CCPC delimiter);

  /*! \copydoc TextParser(CCPC)
   *
   * \param[in] eol Line delimiter.
   */
  TextParser(CCPC delimiter, CCPC eol);


  /*! Parse a field.
   *
   * \param[out] result Result.
   * \param[in] begin Pointer to C string.
   * \param[in] end Pointer to end of C string.
   */
  void parse(char& result, CCPC begin, CCPC end) const;

  /*! \copydoc parse(char&, CCPC, CCPC) const */
  void parse(double& result, CCPC begin, CCPC end) const;

  /*! \copydoc parse(char&, CCPC, CCPC) const */
  void parse(float& result, CCPC begin, CCPC end) const;

  /*!
   * \tparam n String length.
   *
   * \copydoc parse(char&, CCPC, CCPC) const
   */
  template <size_t n>
    void parse(char (&result)[n], CCPC begin, CCPC end) const;

  /*!
   * \tparam truth Truth value.
   *
   * \copydoc parse(char&, CCPC, CCPC) const
   */
  template <CCP truth>
    void parse(Bool<truth>& result, CCPC begin, CCPC end) const;

  /*!
   * \tparam T Integer type.
   * \tparam base Integer base.
   *
   * \copydoc parse(char&, CCPC, CCPC) const
   */
  template <class T, size_t base>
    void parse(Number<T, base>& result, CCPC begin, CCPC end) const;

  /*!
   * \tparam T Integer type.
   * \tparam labels Labels.
   *
   * \copydoc parse(char&, CCPC, CCPC) const
   */
  template <class T, CCP* labels>
    void parse(Category<T, labels>& result, CCPC begin, CCPC end) const;

  /*!
   * \tparam T Integer type.
   *
   * \copydoc parse(char&, CCPC, CCPC) const
   */
  template <class T>
    void parse(T& result, CCPC begin, CCPC end) const;


  /*! Parse a line.
   *
   * \tparam Ts Output variable types.
   *
   * \param[in] line Line to be parsed.
   * \param[out] args Variables to hold the parsed data.
   */
  template <class... Ts>
    void parseLine(CCPC line, Ts&... args) const;

private:
  void consume_(CCP*) const;
  CCP findEnd_(CCP) const;

  template <class T>
    void parseField_(CCP*, T&) const;

  inline void parseLine_(CCP*) const;
  template <size_t n, class... Ts>
    void parseLine_(CCP*, char (&)[n], Ts&...) const;
  template <class T, size_t n, class... Ts>
    void parseLine_(CCP*, T (&)[n], Ts&...) const;
  template <class T, class... Ts>
    void parseLine_(CCP*, T&, Ts&...) const;

  CCP delimiter_ {};
  CCP eol_ {nullptr};
};


template <size_t n>
void TextParser::parse(char (&result)[n], CCPC begin, CCPC end) const {
  char* p {result};
  for (CCP q {begin}; p < result + n - 1 and q < end; ++p, ++q) {
    *p = *q;
  }
  *p = 0;
}

template <CCP truth>
void TextParser::parse(Bool<truth>& result, CCPC begin, CCPC end) const {
  result.value = strmatch(begin, end, truth);
}

template <class T, CCP* labels>
void TextParser::parse(
    Category<T, labels>& result, CCPC begin, CCPC end) const {
  result.value = -1;
  for (size_t i {0}; labels[i]; ++i) {
    if (strmatch(begin, end, labels[i])) {
      result.value = i;
      return;
    }
  }
}

template <class T, size_t base>
void TextParser::parse(Number<T, base>& result, CCPC begin, CCPC) const {
  result.value = strtol(begin, nullptr, base);
}

template <class T>
void TextParser::parse(T& result, CCPC begin, CCPC) const {
  result = strtol(begin, nullptr, 10);
}


template <class... Ts>
void TextParser::parseLine(CCPC line, Ts&... args) const {
  CCP line_ {line};
  parseLine_(&line_, args...);
}


template <class T>
void TextParser::parseField_(CCP* line, T& data) const {
  CCPC end {findEnd_(*line)};
  parse(data, *line, end);
  *line = end;
  consume_(line);
}


inline void TextParser::parseLine_(CCP*) const {}

template <size_t n, class... Ts>
void TextParser::parseLine_(CCP* line, char (&arr)[n], Ts&... tail) const {
  parseField_(line, arr);
  parseLine_(line, tail...);
}

template <class T, size_t n, class... Ts>
void TextParser::parseLine_(CCP* line, T (&arr)[n], Ts&... tail) const {
  for (T& element: arr) {
    parseField_(line, element);
  }
  parseLine_(line, tail...);
}

template <class T, class... Ts>
void TextParser::parseLine_(CCP* line, T& head, Ts&... tail) const {
  parseField_(line, head);
  parseLine_(line, tail...);
}
