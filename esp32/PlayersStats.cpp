#include "PlayersStats.h"

int PlayersStats::ranking[NUM_LEDS];
String PlayersStats::now_showing = "none";
String PlayersStats::now_answering = "none";
unsigned int PlayersStats::time_stamp = millis();

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

namespace {
  String IntToColourASCII(int colour) {
    if (colour == 0)
      return "red";
    else if (colour == 1)
      return "yellow";
    else if (colour == 2)
      return "green";
    else if (colour == 3)
      return "blue";
    else
      return "none";
  }
}

void PlayersStats::setNowShowing(int colour) {
  now_showing = IntToColourASCII(colour);
}

void PlayersStats::setNowAnswering(int colour) {
  now_answering = IntToColourASCII(colour);
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

