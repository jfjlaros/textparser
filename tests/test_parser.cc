#include <string.h>

#include <catch.hpp>

#include "../src/textparser.h"

TextParser parser(", ");

TEST_CASE("Integer", "[basic]") {
  int a;
  char* line = const_cast<char*>("3");
  parser.parse(a, &line);

  REQUIRE(a == 3);
}

TEST_CASE("Double", "[basic]") {
  double a;
  char* line = const_cast<char*>("3.1");
  parser.parse(a, &line);

  REQUIRE(a == 3.1);
}

TEST_CASE("String", "[basic]") {
  char a[10];
  char* line = const_cast<char*>("three");
  parser.parse(a, &line);

  REQUIRE(not strcmp(a, "three"));
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
  double c;
  parser.parseLine("three, 1, 4.1", a, b, c);

  REQUIRE(not strcmp(a, "three"));
  REQUIRE(b == 1);
  REQUIRE(c == 4.1);
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
  REQUIRE(a[1] == 1);
}

TEST_CASE("Delimiter too short for string", "[delim]") {
  char a[2][10];
  parser.parseLine("three,one", a);

  REQUIRE(not strcmp(a[0], "three,one"));
  REQUIRE(not strcmp(a[1], ""));
}
