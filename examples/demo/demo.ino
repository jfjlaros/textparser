#include <textparser.h>

char const truth[] = "Yes";
char const* labels[] = {"red", "green", "blue", nullptr};


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

  parser.parseLine("one, 2, 3.4", a, b, c);
  Serial.print(a);
  Serial.print(' ');
  Serial.print(b);
  Serial.print(' ');
  Serial.println(c);
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

void demo5() {
  // `Bool` type for easy decoding.
  TextParser parser(", ", "\r\n");
  bool a[2];
  Bool<truth> b[2];  // Text based booleans.

  parser.parseLine("0, 1, No, Yes", a, b);
  Serial.print(a[0]);
  Serial.print(' ');
  Serial.print(a[1]);
  Serial.print(' ');
  Serial.print(b[0].value);
  Serial.print(' ');
  Serial.println(b[1].value);
}

void demo6() {
  // `Number` type for easy decoding.
  TextParser parser(", ", "\r\n");
  int a;
  Number<int, 16> b;  // Hexadecimal number.
  Number<int, 2> c;   // Binary number.

  parser.parseLine("1, 0x17, 101101", a, b, c);
  Serial.print(a);
  Serial.print(' ');
  Serial.print(b.value);
  Serial.print(' ');
  Serial.println(c.value);
}

void demo7() {
  // `Category` type for easy decoding.
  TextParser parser(", ", "\r\n");
  Category<int, labels> a[3];

  parser.parseLine("red, blue, yellow", a);
  Serial.print(a[0].value);
  Serial.print(' ');
  Serial.print(a[1].value);
  Serial.print(' ');
  Serial.println(a[2].value);
}


void setup() {
  Serial.begin(9600);

  demo1();
  demo2();
  demo3();
  demo4();
  demo5();
  demo6();
  demo7();
}

void loop() {}
