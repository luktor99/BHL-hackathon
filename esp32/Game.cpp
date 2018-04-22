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

PlayerColours Game::getRandomColour()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(0,3);
    
    return static_cast<PlayerColours>(distribution(generator));  
}


