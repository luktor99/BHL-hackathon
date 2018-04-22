#ifndef ESP32_PUNS_H
#define ESP32_PUNS_H

#include "Game.h"

class Pictionary : public Game {
public:
  enum class State {
    UPDATE_SCORES,
    WAIT_FOR_REACTION,
    FINALIZE
  };

  Pictionary(int players_cnt);

  bool continue_game() override;
  PlayerColours getActivatedSensor();
  void getActivatedSensor(PlayerColours col);
  
private:
 
  State state;
  PlayerColours colour;
};

#endif

