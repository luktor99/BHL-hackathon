#ifndef ESP32_SMART_CUBE_STATE_H
#define ESP32_SMART_CUBE_STATE_H

enum class SmartCubeState {
  INITIALIZE,
  WAIT_FOR_MASTER,
  MASTER_CONNECTED,
  GAME_INITIALIZATION,
  GAME,
  AFTER_GAME
};

extern SmartCubeState smart_cube_state;

#endif

