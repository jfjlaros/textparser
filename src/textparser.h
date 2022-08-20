#pragma once

#include <stdlib.h>
#include <string.h>

typedef char const* ccp;
typedef char const* const ccpc;  //!< Constant pointer to a constant string.

/*! Number. */
template <class T>
struct Number {
  T value;            //!< Value.
  size_t const base;  //!< Base.
};

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
  /*! Constructor.
   *
   * \param[in] delimiter Field delimiter.
   */
  TextParser(ccpc delimiter);

  /*! \copydoc TextParser(ccpc)
   *
   * \param[in] eol Line delimiter.
   */
  TextParser(ccpc delimiter, ccpc eol);

  /*! \copydoc TextParser(ccpc, ccpc)
   *
   * \param[in] truth Truth representation.
   */
  TextParser(ccpc delimiter, ccpc eol, ccpc truth);


  /*! Parse a field.
   *
   * \param[out] result Result.
   * \param[in] begin Pointer to C string.
   * \param[in] end Pointer to end of C string.
   */
  void parse(bool& result, ccpc begin, ccpc end) const;

  /*! \copydoc parse(bool&, ccpc, ccpc) const */
  void parse(char& result, ccpc begin, ccpc end) const;

  /*! \copydoc parse(bool&, ccpc, ccpc) const */
  void parse(double& result, ccpc begin, ccpc end) const;

  /*! \copydoc parse(bool&, ccpc, ccpc) const */
  void parse(float& result, ccpc begin, ccpc end) const;

  /*!
   * \tparam N String length.
   *
   * \copydoc parse(bool&, ccpc, ccpc) const
   */
  template <size_t N>
    void parse(char (&result)[N], ccpc begin, ccpc end) const;

  /*!
   * \tparam T Integer type.
   *
   * \copydoc parse(bool&, ccpc, ccpc) const
   */
  template <class T>
    void parse(T& result, ccpc begin, ccpc end) const;


  /*! \copydoc parse(T&, ccpc, ccpc) const */
  template <class T>
    void parse(Number<T>& result, ccpc begin, ccpc end) const;

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


template <size_t N>
void TextParser::parse(char (&result)[N], ccpc begin, ccpc end) const {
  char* p = result;
  for (ccp q = begin; p < result + N - 1 and q < end; p++, q++) {
    *p = *q;
  }
  *p = 0;
}

template <class T>
void TextParser::parse(T& result, ccpc begin, ccpc) const {
  result = strtol(begin, nullptr, 10);
}

template <class T>
void TextParser::parse(Number<T>& result, ccpc begin, ccpc) const {
  result.value = strtol(begin, nullptr, result.base);
}


template <class... Args>
void TextParser::parseLine(ccpc line, Args&... args) const {
  ccp line_ = line;
  parseLine_(&line_, args...);
}
