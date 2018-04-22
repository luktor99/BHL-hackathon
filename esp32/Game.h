#ifndef ESP32_GAME_H
#define ESP32_GAME_H

#include "DistanceSensor.h"
#include <random>
#include "LEDDriver.h"

class Game {
public:
  Game(int players_cnt);

  virtual bool continue_game() = 0;

  enum isValidAnswer{
    UNDEFINED = 0,
    VALID = 1,
    INVALID = 2,
  }answered;

protected:
  int players_cnt;
  unsigned long last_time;

  LEDColour getRandomColour();

  DistanceSensor distance_sensor[4];

 LEDColour IntToLEDColour(int colour){
 switch(colour){
      case 0:
        return LEDColour::RED;
      case 1:
        return LEDColour::YELLOW;
      case 2:
        return LEDColour::GREEN;
      case 3:
        return LEDColour::BLUE;
    }
}
 int LEDColourToInt(LEDColour colour){
 switch(colour){
      case LEDColour::RED:
        return 0;
      case LEDColour::YELLOW:
        return 1;
      case LEDColour::GREEN:
        return 2;
      case LEDColour::BLUE:
        return 3;
    }

  }
};

extern Game *game_instance;

#endif

