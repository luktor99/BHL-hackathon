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

  static void setNowShowing(int colour);
  static void setNowAnswering(int colour);
  static void setTimeStamp(unsigned long stamp);

  static String getNowShowing();
  static String getNowAnswering();
  static unsigned long getTimeStamp();
  
  
private:
    static int ranking[NUM_LEDS];

    static String now_showing;
    static String now_answering;
    static unsigned long time_stamp;
};
#endif

