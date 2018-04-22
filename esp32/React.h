#ifndef ESP32_REACT_H
#define ESP32_REACT_H

#include "Game.h"

class React : public Game {
public:
  enum class State {
    GENERATE_COLOUR,
    WAIT_FOR_REACTION,
    FINALIZE
  };

  React(int players_cnt);

  bool continue_game() override;
  
private:
  unsigned long time_stamp;
  State state;
  int colour;

  static unsigned long max_waiting_time;
};

#endif

