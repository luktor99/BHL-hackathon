#include "Pictionary.h"
#include "LEDDriver.h"

#include <Arduino.h>

Pictionary::Pictionary(int players_cnt)
  : Game(players_cnt),
  state(State::WAIT_FOR_REACTION),
  colour(0)
{ }

bool Pictionary::continue_game() {
  switch(state) 
  {
  case State::WAIT_FOR_REACTION: 

    for(int i=0; i < 4; ++i)
    {
      if(distance_sensor[static_cast<LEDColour>(i)].is_activated())
      {
                         
      }
    }
    
    state = State::UPDATE_SCORES;
    break;
  
  case State::FINALIZE:
    // check if next game
    // go to base state
    break;
  }
}

