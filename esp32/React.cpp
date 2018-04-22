#include "React.h"
#include <random>

unsigned long React::max_waiting_time = 20000;
const unsigned long waiting_time = 3000;

React::React(int players_cnt)
        : Game(players_cnt),
          time_stamp(0),
          state(State::GAME_START),
          colour(0)
{}

bool React::continue_game() {
    switch(state) {
        case State::GAME_START:
            for(int i = 0; i < 4; ++i){
               player_times[i] = max_waiting_time;
            }
            break;
        case State::GENERATE_COLOUR:
            colour = getRandomColour();
            led_driver.single_blink(50, static_cast<LEDColour>(colour));
            time_stamp = millis();
            state = State::WAIT_FOR_REACTION;
            break;
        case State::WAIT_FOR_REACTION:
        {
            unsigned long time_diff = millis() - time_stamp;
            for(int i=0; i < 4; ++i){
              if(distance_sensor[static_cast<LEDColour>(i)].is_activated()){
                if(static_cast<LEDColour>(i) == colour && player_times[i] > 0){
                  player_times[i] -= time_diff;
                  state = State::UPDATE_SCORES;
                }
                else{
                  player_times[i] -= waiting_time;
                }
              }
            }
            if(time_diff > waiting_time){
              state = State::UPDATE_SCORES;
            }
            break;
        }
        case State::UPDATE_SCORES:
        {
            int players_done = 0; 
            for(int i = 0; i < 4; ++i){
              if(player_times[i] <= 0){
                player_times[i] = 0;
                ++players_done;
              }
              if(players_done > 2){
                state = State::FINALIZE;
              }
              break;
            }
        }
        case State::FINALIZE:
            
            return false;
    }
    return false;
}
