#include <textparser.h>


void demo1() {
  // If all fields are of the same type, we can use an array.
  TextParser parser(", ");
  int a[5];
  parser.parseLine("1, 2, 3, 4, 5", a);

  for (int const& i: a) {
    Serial.print(i);
    Serial.print(' ');
  }
  Serial.println();
}

void demo2() {
  // If the fields have different types, we can use multiple variables.
  TextParser parser(", ");
  char a[10];
  int b;
  double c;
  Number<int> d = {0, 16};  // Hexadecimal number.
  parser.parseLine("one, 2, 3.4", a, b, c, d);

  Serial.print(a);
  Serial.print(' ');
  Serial.print(b);
  Serial.print(' ');
  Serial.println(c);
  Serial.print(' ');
  Serial.println(d);
}

void demo3() {
  // Line endings can be removed by providing a line delimiter.
  TextParser parser(", ", "\r\n");
  char a[10];
  parser.parseLine("abc\r\n", a);

  Serial.print(a);
  Serial.println('.');
}

void demo4() {
  // A two dimensional array can be used to extract substrings.
  TextParser parser(" ", ".");
  char words[5][6];
  parser.parseLine("This is a nice line.", words);

  for (char* const w: words) {
    Serial.print(w);
    Serial.print(' ');
  }
  Serial.println();
}


void setup() {
  Serial.begin(9600);

  demo1();
  demo2();
  demo3();
  demo4();
}

void loop() {}
