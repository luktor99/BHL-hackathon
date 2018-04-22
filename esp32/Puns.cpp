#include "Puns.h"
#include "LEDDriver.h"

#include <Arduino.h>

Puns::Puns(int players_cnt)
  : Game(players_cnt),
  state(State::GENERATE_COLOUR),
  colour(0)
{}

bool Puns::continue_game() {
  switch(state) {
  case State::GENERATE_COLOUR:
     // get random colour
    colour = 0;
    state = State::WAIT_FOR_REACTION;
    break;
  case State::WAIT_FOR_REACTION: 
    state = State::FINALIZE;
    break;
  
  case State::FINALIZE:
    // check if next game
    // go to base state
    break;
  }
}

