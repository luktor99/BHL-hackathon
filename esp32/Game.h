#ifndef ESP32_GAME_H
#define ESP32_GAME_H

#include "DistanceSensor.h"
#include <random>

enum PlayerColours : int {
  red = 0,
  yellow = 1,
  green = 2,
  blue = 3,
  undefined = 4,
};

class Game {
public:
  Game(int players_cnt);

  virtual bool continue_game() = 0;

protected:
  int players_cnt;
  unsigned long last_time;

  PlayerColours getRandomColour();

  DistanceSensor distance_sensor[4];
};

extern Game *game_instance;

#endif

