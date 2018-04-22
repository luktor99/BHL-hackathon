#ifndef ESP32_LED_DRIVER_H
#define ESP32_LED_DRIVER_H

// libraries => git@github.com:samguyer/FastLED.git
#include <FastLED.h>

#define LED_DATA_PIN 23 
#define NUM_LEDS 4

struct LEDColour {
  static const int RED = 0;
  static const int YELLOW = 42;
  static const int GREEN = 85;
  static const int BLUE = 171;
};

class LEDDriver {
public:
  LEDDriver();

  void single_blink(int ms, int hue);
  void double_blink(int ms, int hue);
  void next_rainbow_step(int hue);
  void battery_level(int level);

   void set_first(int count, int hue);
  
private:
  CRGBArray<NUM_LEDS> leds;

 
};

extern LEDDriver led_driver;

#endif

