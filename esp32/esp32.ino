#include <FastLED.h>
#define NUM_LEDS 2
#define DATA_PIN 23 
CRGBArray<NUM_LEDS> leds;

//#include "DistanceSensor.h"
#define DISTANCE_PIN_1 36
#define DISTANCE_PIN_2 39
#define DISTANCE_PIN_3 34
#define DISTANCE_PIN_4 35

class DistanceSensor {
public:
  DistanceSensor(int pin, int activationThreashold);
  int getVoltage() const;
  bool isActivated() const;
  
private:
  const int pin;
  const int activationThreashold;
};

DistanceSensor::DistanceSensor(int pin, int activationThreashold)
  : pin(pin), activationThreashold(activationThreashold)
{}

int DistanceSensor::getVoltage() const {
  return analogRead(pin);
}

bool DistanceSensor::isActivated() const {
  return getVoltage() > activationThreashold;
}

// code
DistanceSensor distanceSensor1(DISTANCE_PIN_1, 1000);
void setup() {
  Serial.begin(115200);
  FastLED.addLeds<WS2812, DATA_PIN>(leds, NUM_LEDS);

}

static uint8_t hue = 0;
void loop() {
  Serial.println("Mariusz test");

  for(int i = 0; i < NUM_LEDS; i++) {   
    // fade everything out
    leds.fadeToBlackBy(40);

    // let's set an led value
    leds[i] = CHSV(hue++,255,255);
//    leds[i] = CHSV(0, 0, 0);
  }
  FastLED.show();

  int value = distanceSensor1.getVoltage();
  bool isActive = distanceSensor1.isActivated();
  Serial.print("distanceSensor1: value = ");
  Serial.print(value);
  Serial.print(" isActivated = ");
  Serial.println(isActive);
  
  delay(500);
}
