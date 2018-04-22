#ifndef ESP32_PUNS_H
#define ESP32_PUNS_H

#include "Game.h"

class Pictionary : public Game {
public:
  enum class State {
    GENERATE_COLOUR,
    WAIT_FOR_REACTION,
    WAIT_FOR_ANSWER,
    FINALIZE
  };

  Pictionary(int players_cnt);
  bool continue_game() override;
  
private:
  State state;
};

#endif

