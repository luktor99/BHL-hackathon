#ifndef ESP32_GAME_H
#define ESP32_GAME_H

#include "DistanceSensor.h"

class Game {
public:
  Game(int players_cnt);

  virtual bool continue_game() = 0;

protected:
  int players_cnt;
  unsigned long last_time;

  DistanceSensor distance_sensor[4];
};

extern Game *game_instance;

#endif

