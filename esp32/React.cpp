#include "React.h"
#include <random>
#include "PlayersStats.h"

unsigned long React::max_waiting_time = 8000;
const unsigned long waiting_time = 1000;

React::React(int players_cnt)
        : Game(players_cnt),
          time_stamp(0),
          state(State::GAME_START),
          colour(LEDColour::RED)
{}

bool React::continue_game() {
    int winner = 4;
    switch(state) {
        case State::GAME_START:
            led_driver.set_first(0, 0);
            delay(100);
            for(int i = 0; i < players_cnt; ++i){
               player_times[i] = max_waiting_time;
               led_driver.double_blink(500, IntToLEDColour(i));
            }
        case State::GENERATE_COLOUR:
            colour = getRandomColour();
            led_driver.set_first(0, 0);
            delay(100);
            led_driver.single_blink(250, colour);
            time_stamp = millis();
            state = State::WAIT_FOR_REACTION;
            break;
        case State::WAIT_FOR_REACTION:
        {
            unsigned long time_diff = millis() - time_stamp;
            if(time_diff > waiting_time){
              player_times[LEDColourToInt(colour)] -= waiting_time;
              state = State::UPDATE_SCORES;
            }
            for(int i=0; i < players_cnt; ++i){
              if(!distance_sensor[i].is_activated())
                continue;
                
              if( IntToLEDColour(i) == colour && player_times[i] > 0) {
                player_times[i] -= time_diff;
                state = State::UPDATE_SCORES;
              } else{
                player_times[i] -= waiting_time;
              }
              
            }
            
            break;
        }
        case State::UPDATE_SCORES: {
            int players_done = 0; 
            for(int i = 0; i < players_cnt; ++i){
              Serial.println(player_times[i]);
              if(player_times[i] <= 0){
                player_times[i] = 0;
                ++players_done;
              }
              else{
                winner = i;
              }
            }
            if(players_done == players_cnt-1){
              PlayersStats::setPlayerValue(winner,1);
              state = State::FINALIZE;
            }
            else if(players_done == players_cnt){
              state = State::FINALIZE;
            }
            else{
              state = State::GENERATE_COLOUR;
            }
            break;
        }
        case State::FINALIZE:
            led_driver.set_first(0, 0);
            delay(100);
            led_driver.double_blink(500, IntToLEDColour(winner));
            return false;
    }
    return true;
}
