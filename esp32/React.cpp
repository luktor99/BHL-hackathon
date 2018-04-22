#include "React.h"
#include "LEDDriver.h"

#include <Arduino.h>

unsigned long React::max_waiting_time = 20000;

React::React(int players_cnt)
  : Game(players_cnt),
  time_stamp(0),
  state(State::GENERATE_COLOUR),
  colour(0)
{}

bool React::continue_game() {
  switch(state) {
  case State::GENERATE_COLOUR:
     // get random colour
    colour = 0;
    led_driver.single_blink(50, LEDColour::BLUE);
    time_stamp = millis();
    state = State::WAIT_FOR_REACTION;
    break;
  case State::WAIT_FOR_REACTION: {
    unsigned long time_diff = millis() - time_stamp;
    if (distance_sensor[colour].is_activated() || time_diff > max_waiting_time) {
      // update player points table
      // check game over condition
      state = State::FINALIZE;
    }
    break;
  }
  case State::FINALIZE:
    // check if next game
    // go to base state
    break;
  }
}

