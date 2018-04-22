#include "PlayersStats.h"

int PlayersStats::ranking[NUM_LEDS];
String PlayersStats::now_showing = "none";
String PlayersStats::now_answering = "none";
unsigned long PlayersStats::time_stamp = millis();

PlayersStats::PlayersStats()
{
  for(int i=0; i < NUM_LEDS; ++i)
  {
    ranking[i] = 0;
  }
}

void PlayersStats::setPlayerValue(int user, int value)
{
   ranking[user] = ranking[user]+value;
}
 
int PlayersStats::getPlayerValue(int user)
{
  return ranking[user];
}

void PlayersStats::clearStats()
{
  for(int i=0; i < NUM_LEDS; ++i)
  {
    ranking[i] = 0;
  }
}

void PlayersStats::setNowShowing(String colour) {
  now_showing = colour;
}

void PlayersStats::setNowAnswering(String colour) {
  now_answering = colour;
}

void PlayersStats::setTimeStamp(unsigned long stamp) {
  time_stamp;
}

String PlayersStats::getNowShowing() {
  return now_showing;
}

String PlayersStats::getNowAnswering() {
  return now_answering;
}

unsigned long PlayersStats::getTimeStamp() {
  return time_stamp;
}

