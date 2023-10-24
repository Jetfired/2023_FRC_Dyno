//https://github.com/adafruit/Adafruit_Learning_System_Guides/blob/main/ANO_Rotary_Encoder/ANO_Rotary_Encoder_NeoPixel_Arduino_Example/ANO_Rotary_Encoder_NeoPixel_Arduino_Example.ino
//https://www.mathertel.de/Arduino/RotaryEncoderLibrary.aspx
//https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
//https://learn.adafruit.com/adafruit-rotary-trinkey/arduino-examples

//STARTUP:
//Download Arduino
//Go to File > Prefrences > Additional boards manager URLs and put in "http://arduino.esp8266.com/stable/package_esp8266com_index.json"
//Install the ESP8266 board module
//Install the following Libraries "Encoder" by Paul Stoffregen, "RotaryEncoder" by Matthias Hertel, and "HID-Project" by NicoHood

//Ensure the pins are correct (encoder pin pairs: [D1, D2], [D5, D6])

#include <RotaryEncoder.h>

#define PIN_ENCODER_A1 4
#define PIN_ENCODER_B1 5
#define PIN_ENCODER_A2 12
#define PIN_ENCODER_B2 14

RotaryEncoder *encoder1 = nullptr;
RotaryEncoder *encoder2 = nullptr;

IRAM_ATTR void checkPosition1() {
  encoder1->tick();
}
IRAM_ATTR void checkPosition2() {
  encoder2->tick();
}

int last_rotary1 = 0;
int last_rotary2 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  encoder1 = new RotaryEncoder(PIN_ENCODER_A1, PIN_ENCODER_B1, RotaryEncoder::LatchMode::TWO03);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A1), checkPosition1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_B1), checkPosition1, CHANGE);

  encoder2 = new RotaryEncoder(PIN_ENCODER_A2, PIN_ENCODER_B2, RotaryEncoder::LatchMode::TWO03);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A2), checkPosition2, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_B2), checkPosition2, CHANGE);
}

void loop() {
  encoder1->tick();
  // put your main code here, to run repeatedly:
  int curr_rotary1 = encoder1->getPosition();
  RotaryEncoder::Direction direction1 = encoder1->getDirection();
  if (curr_rotary1 != last_rotary1) {
    Serial.print("ENCODER 1  |  Time: ");
    Serial.print(millis());
    Serial.print(" | Encoder value: ");
    Serial.print(curr_rotary1);
    Serial.print(" | direction: ");
    Serial.println((int)direction1);
  }
  last_rotary1 = curr_rotary1;

  encoder2->tick();
  // put your main code here, to run repeatedly:
  int curr_rotary2 = encoder2->getPosition();
  RotaryEncoder::Direction direction2 = encoder2->getDirection();
  if (curr_rotary2 != last_rotary2) {
    Serial.print("ENCODER 2  | Time: ");
    Serial.print(millis());
    Serial.print(" | Encoder value: ");
    Serial.print(curr_rotary2);
    Serial.print(" | direction: ");
    Serial.println((int)direction2);
  }
  last_rotary2 = curr_rotary2;
}
