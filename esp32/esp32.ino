// DistanceSensor.h ///////////////////////////////////////////////////////
#define DISTANCE_PIN_1 36
#define DISTANCE_PIN_2 39
#define DISTANCE_PIN_3 34
#define DISTANCE_PIN_4 35

class DistanceSensor {
public:
  DistanceSensor(int pin, int activation_threashold);
  
  int get_voltage() const;
  bool is_activated() const;
  
private:
  const int pin;
  const int activation_threashold;
};

// DistanceSensor.cpp ////////////////////////////////////////////////////
DistanceSensor::DistanceSensor(int pin, int activation_threashold)
  : pin(pin), activation_threashold(activation_threashold)
{}

int DistanceSensor::get_voltage() const {
  return analogRead(pin);
}

bool DistanceSensor::is_activated() const {
  return get_voltage() > activation_threashold;
}

// LEDDriver.h ///////////////////////////////////////////////////////////
#include <FastLED.h>

#define LED_DATA_PIN 23 
#define NUM_LEDS 10

class LEDDriver {
public:
  LEDDriver();

  void nextWaveStep(int hue);
  
private:
  CRGBArray<NUM_LEDS> leds;
};

// LEDDriver.cpp /////////////////////////////////////////////////////////
LEDDriver::LEDDriver() {
  FastLED.addLeds<WS2812, LED_DATA_PIN>(leds, NUM_LEDS);
}

void LEDDriver::nextWaveStep(int hue) {
  int sector_size = 255 / 4;
  
  for(int i = 0; i < NUM_LEDS; i++) {   
    // fade everything out
    leds.fadeToBlackBy(40);

    if (i < 1)
      leds[i] = CHSV(i * sector_size + hue,255,255);
    else
      leds[i] = CHSV(0, 0, 0);
  } 
  FastLED.show();
}

// code //////////////////////////////////////////////////////////////////
DistanceSensor distance_sensor_1(DISTANCE_PIN_1, 1000);
LEDDriver led_driver;

void setup() {
  Serial.begin(115200);  
}

enum class MelkaState {
  INITIALIZE,
  WAIT_FOR_MASTER,
  WAIT_FOR_PLAYERS,
  GAME,
  AFTER_GAME
};

static uint8_t hue = 0;
MelkaState melka_state = MelkaState::INITIALIZE;
void loop() {
  Serial.println("Loop iteration:");

  switch(melka_state) {
  case MelkaState::INITIALIZE:
    Serial.println("INITIALIZE");
    melka_state = MelkaState::WAIT_FOR_MASTER;  
    break;
  case MelkaState::WAIT_FOR_MASTER:
    Serial.println("WAIT_FOR_MASTER");
    led_driver.nextWaveStep(hue);
    hue += 10;
    // waitForServerRequest?
    break;
  case MelkaState::WAIT_FOR_PLAYERS:
    break;
  case MelkaState::GAME:
    break;
  case MelkaState::AFTER_GAME:
    break;
  }
  
  int value = distance_sensor_1.get_voltage();
  bool isActive = distance_sensor_1.is_activated();
  Serial.print("distance_sensor_1: value = ");
  Serial.print(value);
  Serial.print(" is_activated = ");
  Serial.println(isActive);

  
  
  delay(1000);
}
