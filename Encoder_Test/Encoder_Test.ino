//https://github.com/adafruit/Adafruit_Learning_System_Guides/blob/main/ANO_Rotary_Encoder/ANO_Rotary_Encoder_NeoPixel_Arduino_Example/ANO_Rotary_Encoder_NeoPixel_Arduino_Example.ino
//https://www.mathertel.de/Arduino/RotaryEncoderLibrary.aspx
//https://lastminuteengineers.com/rotary-encoder-arduino-tutorial/
//https://learn.adafruit.com/adafruit-rotary-trinkey/arduino-examples

//STARTUP:
//Download Arduino
//Go to File > Prefrences > Additional boards manager URLs and put in "http://arduino.esp8266.com/stable/package_esp8266com_index.json"
//Install the ESP8266 board module
//Install the following Libraries "Encoder" by Paul Stoffregen, "RotaryEncoder" by Matthias Hertel, and "HID-Project" by NicoHood

//Ensure the pins are correct (pin locations are D1 and D2)

#include <RotaryEncoder.h>

#define PIN_ENCODER_A 4
#define PIN_ENCODER_B 5

RotaryEncoder *encoder = nullptr;

IRAM_ATTR void checkPosition() {
  encoder->tick();
}

int last_rotary = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  encoder = new RotaryEncoder(PIN_ENCODER_A, PIN_ENCODER_B, RotaryEncoder::LatchMode::TWO03);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_A), checkPosition, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIN_ENCODER_B), checkPosition, CHANGE);
}

void loop() {
  encoder->tick();
  // put your main code here, to run repeatedly:
  int curr_rotary = encoder->getPosition();
  RotaryEncoder::Direction direction = encoder->getDirection();
  if (curr_rotary != last_rotary) {
    Serial.print("Time: ");
    Serial.print(millis());
    Serial.print(" | Encoder value: ");
    Serial.print(curr_rotary);
    Serial.print(" | direction: ");
    Serial.println((int)direction);
  }
  last_rotary = curr_rotary;
}
