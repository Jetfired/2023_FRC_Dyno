//https://github.com/adafruit/Adafruit_Learning_System_Guides/blob/main/ANO_Rotary_Encoder/ANO_Rotary_Encoder_NeoPixel_Arduino_Example/ANO_Rotary_Encoder_NeoPixel_Arduino_Example.ino
//https://www.mathertel.de/Arduino/RotaryEncoderLibrary.aspx
//https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
//https://learn.adafruit.com/adafruit-rotary-trinkey/arduino-examples

#include <RotaryEncoder.h>

#define PIN_ENCODER_A 1
#define PIN_ENCODER_B 3

RotaryEncoder encoder(PIN_ENCODER_A, PIN_ENCODER_B, RotaryEncoder::LatchMode::FOUR3);

void checkPosition() {
  encoder.tick();
}

int last_rotary = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  attachInterrupt(PIN_ENCODER_A, checkPosition, CHANGE);
  attachInterrupt(PIN_ENCODER_B, checkPosition, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  int curr_rotary = encoder.getPosition();
  RotaryEncoder::Direction direction = encoder.getDirection();
  if (curr_rotary != last_rotary) {
    Serial.print("Encoder value: ");
    Serial.print(curr_rotary);
    Serial.print(" direction: ");
    Serial.print((int)direction);
  }
  last_rotary = curr_rotary;
}





