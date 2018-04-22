#ifndef ESP32_PUNS_H
#define ESP32_PUNS_H

#include "Game.h"

class Pictionary : public Game {
public:
  enum class State {
    GENERATE_COLOUR,
    WAIT_FOR_REACTION,
    FINALIZE
  };

  Pictionary(int players_cnt);

  bool continue_game() override;
  
private:
  State state;
  int colour;;
};

#endif

