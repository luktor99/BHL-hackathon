#include "Pictionary.h"
#include "LEDDriver.h"

#include <Arduino.h>
#include "PlayersStats.h"

const unsigned int answer_timeout = 5000;

Pictionary::Pictionary(int players_cnt)
  : Game(players_cnt),
  state(State::GENERATE_COLOUR)
{}

bool Pictionary::continue_game() {
  static int winner = 4;
  static int person_showing = 4;
  static int previous_time = 0;
  switch(state) {
    
  case State::GENERATE_COLOUR:
  {
    Serial.println("Pictionary: GENERATE_COLOUR state");
    answered = INVALID;
    for(int i = 0; i < players_cnt; ++i){
      if(distance_sensor[i].is_activated()){
        Serial.println("Pictionary: Setting person showing");
        led_driver.set_first(4,IntToLEDColour(i));
        person_showing = i;
        state = State::WAIT_FOR_REACTION;
        break;
      } 
    }
    state = State::GENERATE_COLOUR;
    break;
  }
  
  case State::WAIT_FOR_REACTION:
  Serial.println("Pictionary: WAIT_FOR_REACTION state");
    for(int i = 0; i < players_cnt; ++i){
      if(distance_sensor[i].is_activated()){
        Serial.println("Pictionary: Person answering chosen");
        led_driver.set_first(4,IntToLEDColour(i));
        winner = i;
        previous_time = millis();
        state = State::WAIT_FOR_ANSWER;
        break;
      }
    }
    state = State::WAIT_FOR_REACTION;
    break;
    
  case State::WAIT_FOR_ANSWER:
    if(millis()-previous_time > answer_timeout || answered == INVALID){
      Serial.println("Pictionary: Timeout, no answer or wrong answer");
      answered = UNDEFINED;
      led_driver.double_blink(300, LEDColour::RED);
      state = State::WAIT_FOR_REACTION;
    }
    else if(answered == VALID){
      Serial.println("Pictionary: Correct answer!!");
      answered == UNDEFINED;
      led_driver.double_blink(300, LEDColour::GREEN);
      state = State::FINALIZE;
    }
    break;
    
  case State::FINALIZE:
    if(winner < 4){
      Serial.println("Pictionary: Quitting");
      PlayersStats::setNowShowing(person_showing) ;
      PlayersStats::setNowAnswering(winner);
      PlayersStats::setTimeStamp(millis());
      PlayersStats::setPlayerValue(winner, 1);
    }
    return false;
  }
  return true;
}

