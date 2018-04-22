#ifndef ESP32_LED_DRIVER_H
#define ESP32_LED_DRIVER_H

// libraries => git@github.com:samguyer/FastLED.git
#include <FastLED.h>

#define LED_DATA_PIN 23 
#define NUM_LEDS 4

enum LEDColour {
  RED = 0,
  YELLOW = 1,
  GREEN = 2,
  BLUE = 3,
};

class LEDDriver {
public:
  LEDDriver();

  void single_blink(int ms, int hue);
  void double_blink(int ms, int hue);
  void next_rainbow_step(int hue);
  void battery_level(int level);
  
private:
  CRGBArray<NUM_LEDS> leds;

  void set_first(int count, int hue);
};

extern LEDDriver led_driver;

#endif

