#ifndef ESP32_PLAYERS_STATS_H
#define ESP32_PLAYERS_STATS_H

#include "LEDDriver.h"

class PlayersStats {
  
public:
   PlayersStats();
   ~PlayersStats();

  void setPlayerValue(int user, int value);
  int getPlayerValue(int user);
     
private:
    int ranking[NUM_LEDS];
};
#endif

