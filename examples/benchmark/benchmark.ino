#include <textparser.h>


void noLib() {
  int a[5];
  char const line[] = "1, 2, 3, 4, 5";
  char* endptr = const_cast<char*>(line);

  for (size_t i = 0; i < 5; i++) {
    a[i] = strtol(endptr, &endptr, 10);
    (*endptr) += 2;
  }

  for (int const& i: a) {
    Serial.print(i);
    Serial.print(' ');
  }
  Serial.println();
}

void lib() {
  TextParser parser(", ");
  int a[5];
  parser.parseLine("1, 2, 3, 4, 5", a);

  for (int const& i: a) {
    Serial.print(i);
    Serial.print(' ');
  }
  Serial.println();
}


void setup() {
  //noLib();  // 2538 bytes program storage space, 204 bytes dynamic memory.
  //lib();    // 2620 bytes program storage space, 206 bytes dynamic memory.
}

void loop() {}
