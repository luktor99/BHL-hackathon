// ADCDriver.h ////////////////////////////////////////////////////////////
#define BATTERY_PIN 32

class ADCDriver {
public:
  ADCDriver(int pin);
  
  int get_voltage() const;
  
private:
  const int pin;
};

// ADCDriver.cpp //////////////////////////////////////////////////////////
ADCDriver::ADCDriver(int pin)
  : pin(pin)
{}

int ADCDriver::get_voltage() const {
  return analogRead(pin);
}

// Battery.h //////////////////////////////////////////////////////////////
class Battery {
public:
  Battery(int pin);

  int get_level() const;
  
private:
  ADCDriver adc_driver;
};

// Battery.cpp ////////////////////////////////////////////////////////////
Battery::Battery(int pin)
  : adc_driver(pin)
{}

int Battery::get_level() const {
  int voltage = adc_driver.get_voltage();
  if (voltage < 3.3)
    return 1;
  if (voltage < 3.58)
    return 2;
  if (voltage < 3.87)
    return 3;
  return 4;
}

// DistanceSensor.h ///////////////////////////////////////////////////////
#define DISTANCE_PIN_1 36
#define DISTANCE_PIN_2 39
#define DISTANCE_PIN_3 34
#define DISTANCE_PIN_4 35

class DistanceSensor {
public:
  DistanceSensor(int pin, int activation_threashold);
  
  bool is_activated() const;
  
private:
  ADCDriver adc_driver;
  const int activation_threashold;
};

// DistanceSensor.cpp ////////////////////////////////////////////////////'
DistanceSensor::DistanceSensor(int pin, int activation_threashold)
  : adc_driver(pin),
  activation_threashold(activation_threashold)
{}

bool DistanceSensor::is_activated() const {
  return adc_driver.get_voltage() > activation_threashold;
}

// LEDDriver.h ///////////////////////////////////////////////////////////
// libraries => git@github.com:samguyer/FastLED.git
#include <FastLED.h>

#define LED_DATA_PIN 23 
#define NUM_LEDS 4

namespace LEDColour {
  int RED = 0;
  int YELLOW = 42;
  int GREEN = 85;
  int BLUE = 171;
}

class LEDDriver {
public:
  LEDDriver();

  void single_blink(int ms, int hue);
  void double_blink(int ms, int hue);
  void next_rainbow_step(int hue);
  void battery_level(int level);
  
private:
  CRGBArray<NUM_LEDS> leds;

  void set_first(int count, int hue);
};

LEDDriver led_driver;

// LEDDriver.cpp /////////////////////////////////////////////////////////
LEDDriver::LEDDriver() {
  FastLED.addLeds<WS2812, LED_DATA_PIN>(leds, NUM_LEDS);
}

void LEDDriver::single_blink(int ms, int hue) {
  set_first(4, hue);
  delay(ms);
  set_first(0, 0);
  delay(ms);
}

void LEDDriver::double_blink(int ms, int hue) {
  single_blink(ms, hue);
  single_blink(ms, hue);
}

void LEDDriver::next_rainbow_step(int hue) {
  int sector_size = 255 / 4;
  
  for(int i = 0; i < NUM_LEDS; i++)
    leds[i] = CHSV(i * sector_size + hue,255,255);
  FastLED.show();
}

void LEDDriver::battery_level(int level) {
  int colour;
  switch(level) {
  case 1:
    set_first(1, LEDColour::RED);
    break;
  case 2:
    set_first(2, LEDColour::YELLOW);
    break;
  case 3:
    set_first(3, LEDColour::BLUE);
    break;
  case 4:
    set_first(4, LEDColour::GREEN);
    break;
  }
}

void LEDDriver::set_first(int count, int hue) {
  int cnt = 0;
  for (;cnt < count; ++cnt)
    leds[cnt] = CHSV(hue,255,255);
  for (;cnt < NUM_LEDS; ++cnt)
    leds[cnt] = CHSV(0,0,0);
  FastLED.show();
}

// PlayersStats.h /////////////////////////////////////////////////////////
class PlayersStats {
public:
  // TODO 
};

// Game.h /////////////////////////////////////////////////////////////////
class Game {
public:
  Game(int players_cnt);

  virtual bool continue_game() = 0;

protected:
  int players_cnt;
  unsigned long last_time;

  DistanceSensor distance_sensor[4];
};

Game *game_instance = nullptr;

// Game.cpp ///////////////////////////////////////////////////////////////
Game::Game(int players_cnt)
  : players_cnt(players_cnt),
  last_time(millis()),
  distance_sensor{DistanceSensor(DISTANCE_PIN_1, 1000),
                  DistanceSensor(DISTANCE_PIN_2, 1000),
                  DistanceSensor(DISTANCE_PIN_3, 1000),
                  DistanceSensor(DISTANCE_PIN_4, 1000)}
{}

// React.h ////////////////////////////////////////////////////////////////
class React : public Game{
public:
  enum class State {
    GENERATE_COLOUR,
    WAIT_FOR_REACTION,
    FINALIZE
  };

  React(int players_cnt);

  bool continue_game() override;
  
private:
  unsigned long time_stamp;
  State state;
  int colour;

  static unsigned long max_waiting_time;
};

// React.cpp //////////////////////////////////////////////////////////////
unsigned long React::max_waiting_time = 20000;

React::React(int players_cnt)
  : Game(players_cnt),
  time_stamp(0),
  state(State::GENERATE_COLOUR),
  colour(0)
{}

bool React::continue_game() {
  switch(state) {
  case State::GENERATE_COLOUR:
     // get random colour
    colour = 0;
    led_driver.single_blink(50, LEDColour::BLUE);
    time_stamp = millis();
    state = State::WAIT_FOR_REACTION;
    break;
  case State::WAIT_FOR_REACTION: {
    unsigned long time_diff = millis() - time_stamp;
    if (distance_sensor[colour].is_activated() || time_diff > max_waiting_time) {
      // update player points table
      // check game over condition
      state = State::FINALIZE;
    }
    break;
  }
  case State::FINALIZE:
    // check if next game
    // go to base state
    break;
  }
}

// SmartCubeState.h ///////////////////////////////////////////////////////////
enum class SmartCubeState {
  INITIALIZE,
  WAIT_FOR_MASTER,
  MASTER_CONNECTED,
  GAME_INITIALIZATION,
  GAME,
  AFTER_GAME
};
SmartCubeState smart_cube_state = SmartCubeState::INITIALIZE;

// WiFiDriver.h ///////////////////////////////////////////////////////////
#include <WiFi.h>
const char *ssid = "SmartCube";
const char *password = "87654321";

WiFiServer server(80);

// API.h /////////////////////////////////////////////////////////////////
// libraries => https://github.com/marcoschwartz/aREST
#include <aREST.h>

namespace APIVariable {
  bool state = true;
  int temperature = 25;
  String nick = "hot20";
}

namespace APIFunction {
  int register_master(String) {
    if (smart_cube_state != SmartCubeState::WAIT_FOR_MASTER) {
      Serial.println("APIFunction::register_master bad state");
      return 1;
    }
    
    smart_cube_state = SmartCubeState::MASTER_CONNECTED;
    return 0;
  }

  int game(String cmd) {
    if (smart_cube_state != SmartCubeState::GAME_INITIALIZATION) {
      Serial.println("APIFunction::game bad state");
      return 1;
    }

    int players_cnt = cmd[0] - '0';
    Serial.print("players = ");
    Serial.print(players_cnt);
    Serial.print(" game = ");
    String game_name = cmd.substring(1, cmd.length());
    Serial.println(game_name);

    if (game_instance) {
      delete game_instance;
      game_instance = nullptr;
    }
      
    if (game_name == "React") {
      game_instance = new React(players_cnt);
    }
    
    smart_cube_state = SmartCubeState::GAME;
    return 0;    
  }
}

class API {
public:
  API();

  void configure();
  void handle_request(WiFiServer &server);
  
private:
  aREST rest;
};

// API.cpp ///////////////////////////////////////////////////////////////
API::API()
  : rest(aREST())
{}

void API::configure() {
  rest.variable("state", &APIVariable::state);
  rest.variable("temperature", &APIVariable::temperature);
  rest.variable("nick", &APIVariable::nick);
  
  rest.function((char*)"register", APIFunction::register_master);
  rest.function((char*)"game", APIFunction::game);

  rest.set_id("123456");
  rest.set_name((char*)"SmartCube");
}

void API::handle_request(WiFiServer &server) {
  WiFiClient client = server.available();
  if (!client)
    return;
  
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}

// code //////////////////////////////////////////////////////////////////
API api;

void setup() {
  Serial.begin(115200);  
  
  api.configure();

  WiFi.softAP(ssid, password);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
}

static uint8_t hue = 0;
void loop() {
  api.handle_request(server);

  static unsigned long last_time = millis();
  static unsigned long loop_time = 500;
  if (millis() - last_time > loop_time) {
    last_time = millis();

    Serial.println("Slow loop iteration:");
    switch(smart_cube_state) {
    case SmartCubeState::INITIALIZE:
      Serial.println("INITIALIZE");
      loop_time = 500;
      smart_cube_state = SmartCubeState::WAIT_FOR_MASTER;  
      break;
    case SmartCubeState::WAIT_FOR_MASTER: {
      Serial.println("WAIT_FOR_MASTER");
      Battery battery(BATTERY_PIN);
      int level = battery.get_level();
      led_driver.battery_level(level);
      break;
    }
    case SmartCubeState::MASTER_CONNECTED: {
      Serial.println("MASTER_CONNECTED");
      led_driver.single_blink(1000, LEDColour::GREEN);
      led_driver.double_blink(200, LEDColour::GREEN);
      Battery battery(BATTERY_PIN);
      int level = battery.get_level();
      led_driver.battery_level(level);
      smart_cube_state = SmartCubeState::GAME_INITIALIZATION;
      break;
    }
    case SmartCubeState::GAME_INITIALIZATION:
      Serial.println("GAME_INITIALIZATION");
      led_driver.next_rainbow_step(hue);
      hue += 10;
      break;
    case SmartCubeState::GAME: {
      loop_time = 1;
      bool stay_in_game = game_instance->continue_game();
      if (!stay_in_game)
        smart_cube_state = SmartCubeState::AFTER_GAME;
      break;
    }
    case SmartCubeState::AFTER_GAME:
      loop_time = 500;
      break;
    }
  }
}
