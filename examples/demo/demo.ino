#include <textparser.h>


void setup() {
  Serial.begin(9600);

  TextParser parser(", ");

  char const* lines[] = {
    "hello, 1.23, 45",
    "world, 2.34, 56"};
  for (char const* line: lines) {
    char a[10];
    double b;
    int c;
    parser.parseLine(line, a, b, c);
    Serial.println(a);
    Serial.println(b);
    Serial.println(c);
  }
}

void loop() {}
