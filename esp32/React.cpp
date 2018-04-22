#include "React.h"
#include <random>

const unsigned long React::max_waiting_time = 20000;

React::React(int players_cnt)
        : Game(players_cnt),
          time_stamp(0),
          state(State::GENERATE_COLOUR),
          colour(0)
{}

bool React::continue_game() {
    switch(state) {
        case State::GENERATE_COLOUR:
            std::default_random_engine generator;
            std::uniform_int_distribution<int> distribution(0,3);
            colour = distribution(generator);
            led_driver.single_blink(50, static_cast<LEDColour>(colour));
            time_stamp = millis();
            state = State::WAIT_FOR_REACTION;
            break;
        case State::WAIT_FOR_REACTION
            unsigned long time_diff = millis() - time_stamp;
            for(int i=0; i < 4; ++i){
              if(distance_sensor[static_cast<LEDColour>(i)].is_activated()){
                
              }
            }
            if(time_diff > max_time_diff)
              state = State::UPDATE_SCORES;
            break;
        case State::UPDATE_SCORES:
            

        case State::FINALIZE:
            // check if next game
            // go to base state
            break;
    }
    return false;
}
