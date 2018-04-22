 #include "LEDDriver.h"

 LEDDriver led_driver;

 LEDDriver::LEDDriver() {
  FastLED.addLeds<WS2812, LED_DATA_PIN>(leds, NUM_LEDS);
}

void LEDDriver::single_blink(int ms, int hue) {
  set_first(4, hue);
  delay(ms);
  set_first(0, 0);
  delay(ms);
}

void LEDDriver::double_blink(int ms, int hue) {
  single_blink(ms, hue);
  single_blink(ms, hue);
}

void LEDDriver::next_rainbow_step(int hue) {
  int sector_size = 255 / 4;
  
  for(int i = 0; i < NUM_LEDS; i++)
    leds[i] = CHSV(i * sector_size + hue,255,255);
  FastLED.show();
}

void LEDDriver::battery_level(int level) {
  int colour;
  switch(level) {
  case 1:
    set_first(1, LEDColour::RED);
    break;
  case 2:
    set_first(2, LEDColour::YELLOW);
    break;
  case 3:
    set_first(3, LEDColour::BLUE);
    break;
  case 4:
    set_first(4, LEDColour::GREEN);
    break;
  }
}

void LEDDriver::set_first(int count, int hue) {
  int cnt = 0;
  for (;cnt < count; ++cnt)
    leds[cnt] = CHSV(hue,255,255);
  for (;cnt < NUM_LEDS; ++cnt)
    leds[cnt] = CHSV(0,0,0);
  FastLED.show();
}

