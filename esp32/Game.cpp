#include "Game.h"

#include <chrono>
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

LEDColour Game::getRandomColour()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0,4);
    
    int colour = distribution(generator);  
    switch(colour){
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

int Game::LEDColourToInt(LEDColour colour){
  switch(colour){
      case LEDColour::RED:
        return 0;
      case LEDColour::YELLOW:
        return 1;
      case LEDColour::GREEN:
        return 2;
      case LEDColour::BLUE:
        return 3;
    }
}


