#include <string.h>

#include <catch.hpp>

#include "../src/textparser.h"

char const truth[] = "TRUE";
char const* labels[] = {"red", "green", "blue", nullptr};
TextParser parser(", ");


TEST_CASE("Integer", "[basic]") {
  int a;
  ccpc line = "3";

  parser.parse(a, line, line + 1);
  REQUIRE(a == 3);
}

TEST_CASE("Short unsigned integer", "[basic]") {
  short unsigned int a;
  ccpc line = "3";

  parser.parse(a, line, line + 1);
  REQUIRE(a == 3);
}

TEST_CASE("Long long integer", "[basic]") {
  long long int a;
  ccpc line = "3";

  parser.parse(a, line, line + 1);
  REQUIRE(a == 3);
}

TEST_CASE("Double", "[basic]") {
  double a;
  ccpc line = "3.1";

  parser.parse(a, line, line + 3);
  REQUIRE(a == 3.1);
}

TEST_CASE("Float", "[basic]") {
  float a;
  ccpc line = "3.1";

  parser.parse(a, line, line + 3);
  REQUIRE(a == 3.1f);
}

TEST_CASE("Hexadecimal number", "[basic]") {
  Number<int, 16> a;
  ccpc line = "0x1f";

  parser.parse(a, line, line + 4);
  REQUIRE(a.value == 31);
}

TEST_CASE("Binary number", "[basic]") {
  Number<uint8_t, 2> a;
  ccpc line = "11111";

  parser.parse(a, line, line + 5);
  REQUIRE(a.value == 31);
}

TEST_CASE("Char", "[basic]") {
  char a;
  ccpc line = "a";

  parser.parse(a, line, line + 1);
  REQUIRE(a == 'a');
}

TEST_CASE("Bool as integer", "[basic]") {
  bool a;
  ccp line = "1";

  parser.parse(a, line, line + 1);
  REQUIRE(a);

  line = "3";
  parser.parse(a, line, line + 1);
  REQUIRE(a);

  line = "314";
  parser.parse(a, line, line + 3);
  REQUIRE(a);

  line = "0";
  parser.parse(a, line, line + 1);
  REQUIRE(not a);
}

TEST_CASE("Bool as text", "[basic]") {
  Bool<truth> a;
  ccp line = "TRUE";

  parser.parse(a, line, line + 4);
  REQUIRE(a.value);

  line = "FALSE";
  parser.parse(a, line, line + 5);
  REQUIRE(not a.value);

  line = "TRU";
  parser.parse(a, line, line + 3);
  REQUIRE(not a.value);

  line = "TRUEE";
  parser.parse(a, line, line + 5);
  REQUIRE(not a.value);
}

TEST_CASE("Category", "[basic]") {
  Category<int, labels> a;
  ccp line = "red";

  parser.parse(a, line, line + 3);
  REQUIRE(a.value == 0);

  line = "green";
  parser.parse(a, line, line + 5);
  REQUIRE(a.value == 1);

  line = "blue";
  parser.parse(a, line, line + 4);
  REQUIRE(a.value == 2);

  line = "yellow";
  parser.parse(a, line, line + 6);
  REQUIRE(a.value == -1);
}

TEST_CASE("C string", "[basic]") {
  char a[10];
  ccpc line = "three";

  parser.parse(a, line, line + 5);
  REQUIRE(not strcmp(a, "three"));
}

TEST_CASE("C string too long", "[basic]") {
  char a[4];
  ccpc line = "three";

  parser.parse(a, line, line + 5);
  REQUIRE(not strcmp(a, "thr"));
}


TEST_CASE("Line with only integers", "[line]") {
  int a[3];

  parser.parseLine("3, 1, 4", a);
  REQUIRE(a[0] == 3);
  REQUIRE(a[1] == 1);
  REQUIRE(a[2] == 4);
}

TEST_CASE("Line with only doubles", "[line]") {
  double a[3];

  parser.parseLine("3.1, 4.1, 5.9", a);
  REQUIRE(a[0] == 3.1);
  REQUIRE(a[1] == 4.1);
  REQUIRE(a[2] == 5.9);
}

TEST_CASE("Line with only strings", "[line]") {
  char a[3][10];

  parser.parseLine("three, one, four", a);
  REQUIRE(not strcmp(a[0], "three"));
  REQUIRE(not strcmp(a[1], "one"));
  REQUIRE(not strcmp(a[2], "four"));
}

TEST_CASE("Line with mixed types", "[line]") {
  char a[10];
  int b;
  char c;
  double d;
  Number<long, 16> e;
  Category<int, labels> f;

  parser.parseLine("three, 1, f, 1.5, 0x5c, green", a, b, c, d, e, f);
  REQUIRE(not strcmp(a, "three"));
  REQUIRE(b == 1);
  REQUIRE(c == 'f');
  REQUIRE(d == 1.5);
  REQUIRE(e.value == 92);
  REQUIRE(f.value == 1);
}

TEST_CASE("Line with mixed boolean types", "[line]") {
  ccpc line = "1, 0, TRUE, FALSE";
  bool a[2];
  Bool<truth> b[2];

  parser.parseLine(line, a, b);
  REQUIRE(a[0]);
  REQUIRE(not a[1]);
  REQUIRE(b[0].value);
  REQUIRE(not b[1].value);
}


TEST_CASE("Line too short for array", "[line]") {
  int a[3] = {1, 1, 1};

  parser.parseLine("3, 1", a);
  REQUIRE(a[0] == 3);
  REQUIRE(a[1] == 1);
  REQUIRE(a[2] == 0);
}

TEST_CASE("Line too short for mixed types", "[line]") {
  char a[10];
  int b;
  double c = 1.0;

  parser.parseLine("three, 1", a, b, c);
  REQUIRE(not strcmp(a, "three"));
  REQUIRE(b == 1);
  REQUIRE(c == 0.0);
}

TEST_CASE("Empty line", "[line]") {
  bool a = true;
  parser.parseLine("", a);
  REQUIRE(not a);

  char b = 1;
  parser.parseLine("", b);
  REQUIRE(not b);

  float c = 1;
  parser.parseLine("", c);
  REQUIRE(not c);

  int d = 1;
  parser.parseLine("", d);
  REQUIRE(not d);

  char e[2] = "1";
  parser.parseLine("", e);
  REQUIRE(not strlen(e));

  int f[2] = {1, 1};
  parser.parseLine("", f);
  REQUIRE(not (f[0] or f[1]));
}


TEST_CASE("C string too long in line", "[line]") {
  char a[4];
  char b[4];

  parser.parseLine("three, one", a, b);
  REQUIRE(not strcmp(a, "thr"));
  REQUIRE(not strcmp(b, "one"));
}

TEST_CASE("No end of line", "[eol]") {
  char a[10];

  parser.parseLine("three\r\n", a);
  REQUIRE(not strcmp(a, "three\r\n"));
}

TEST_CASE("End of line", "[eol]") {
  TextParser parser_(", ", "\r\n");
  char a[10];

  parser_.parseLine("three\r\n", a);
  REQUIRE(not strcmp(a, "three"));
}

TEST_CASE("End of line too short", "[eol]") {
  TextParser parser_(", ", "\r\n");
  char a[10];

  parser_.parseLine("three\r", a);
  REQUIRE(not strcmp(a, "three\r"));
}


TEST_CASE("Delimiter too short", "[delim]") {
  int a[2];

  parser.parseLine("3,1", a);
  REQUIRE(a[0] == 3);
  REQUIRE(a[1] == 0);
}

TEST_CASE("Delimiter too short for string", "[delim]") {
  char a[2][10];

  parser.parseLine("three,one", a);
  REQUIRE(not strcmp(a[0], "three,one"));
  REQUIRE(not strcmp(a[1], ""));
}
