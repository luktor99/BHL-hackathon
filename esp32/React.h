#ifndef ESP32_REACT_H
#define ESP32_REACT_H

#include "Game.h"
#include "PlayersStats.h"

class React : public Game {
public:
  enum class State {
    GAME_START,
    GENERATE_COLOUR,
    WAIT_FOR_REACTION,
    UPDATE_SCORES,
    FINALIZE
  };

  React(int players_cnt);

  bool continue_game() override;
  
private:
  unsigned long time_stamp;
  State state;
  LEDColour colour;

  int player_times[4];

  static unsigned long max_waiting_time;
};

#endif

