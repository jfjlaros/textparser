#include <textparser.h>


void setup() {
  TextParser level1(",");
  char commands[3][6];
  level1.parseLine("!13=1,?2=,?3", commands);

  for (char* const cmd: commands) {
    TextParser level2("=");
    char action[4];
    bool state;
    level2.parseLine(cmd, action, state);

    TextParser level3("");
    char direction;
    uint8_t pin;
    level3.parseLine(action, direction, pin);

    Serial.print(direction);
    Serial.print(' ');
    Serial.print(pin);
    Serial.print(' ');
    Serial.println(state);
  }
}

void loop() {}
