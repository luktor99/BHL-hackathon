#include "Game.h"

#include <Arduino.h>


Game *game_instance = nullptr;

Game::Game(int players_cnt)
  : players_cnt(players_cnt),
  last_time(millis()),
  distance_sensor{DistanceSensor(DISTANCE_PIN_1, 1000),
                  DistanceSensor(DISTANCE_PIN_2, 1000),
                  DistanceSensor(DISTANCE_PIN_3, 1000),
                  DistanceSensor(DISTANCE_PIN_4, 1000)}
{}

LEDColour Game::getRandomColour() {
    static std::default_random_engine generator(analogRead(26));
    static std::uniform_int_distribution<int> distribution(0,4);
    
    switch(distribution(generator)){
      case 0:
        return LEDColour::RED;
      case 1:
        return LEDColour::YELLOW;
      case 2:
        return LEDColour::GREEN;
      case 3:
        return LEDColour::BLUE;
    }
}


