#ifndef ESP32_PLAYERS_STATS_H
#define ESP32_PLAYERS_STATS_H

#include "LEDDriver.h"

class PlayersStats {
  
public:
   PlayersStats();
   ~PlayersStats();

  static void setPlayerValue(int user, int value);
  static int getPlayerValue(int user);

  static void clearStats();
     
private:
    static int ranking[NUM_LEDS];
};
#endif

