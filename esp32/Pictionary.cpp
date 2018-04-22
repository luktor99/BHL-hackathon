#include "Pictionary.h"
#include "LEDDriver.h"

#include <Arduino.h>

Pictionary::Pictionary(int players_cnt)
  : Game(players_cnt),
  state(State::GENERATE_COLOUR)
{}

bool Pictionary::continue_game() {
//  switch(state) {
//  case State::GENERATE_COLOUR:
//  {
//
//    const auto color = getRandomColour();
//    led_driver.set_first(color, static_cast<LEDColour>(colour));
//
//    // To DO; SEND info to client.
//    state = State::WAIT_FOR_REACTION;
//  }
//    break;
//  case State::WAIT_FOR_REACTION: 
//    state = State::FINALIZE;
//    break;
//  
//  case State::FINALIZE:
//    // check if next game
//    // go to base state
//    break;
//  }
}

