#include "PlayersStats.h"

int PlayersStats::ranking[NUM_LEDS];

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

static void PlayersStats::clearStats()
{
  
}

