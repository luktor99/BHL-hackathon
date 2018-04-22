#include "ADCDriver.h"
#include "Battery.h"
#include "DistanceSensor.h"
#include "LEDDriver.h"
#include "PlayersStats.h"
#include "Game.h"
#include "React.h"
#include "SmartCubeState.h"
#include "WiFiDriver.h"
#include <ArduinoJson.h>

// API.h /////////////////////////////////////////////////////////////////
namespace APIFunction {
  void register_master() {
    if (smart_cube_state != SmartCubeState::WAIT_FOR_MASTER) {
      Serial.println("APIFunction::register_master bad state");
      return
    }
    smart_cube_state = SmartCubeState::MASTER_CONNECTED;
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
  StaticJsonBuffer<200> jsonBuffer;
};

// API.cpp ///////////////////////////////////////////////////////////////
API::API() {
}

void API::configure() {
  server.on("/game", HTTP_GET, [&](AsyncWebServerRequest *request) {
    AsyncWebParameter* players_count = request->getParam(0);
    AsyncWebParameter* game = request->getParam(1);

    // Do sth with players_count->value().toInt() and game->value()
    
    jsonBuffer.clear();
    JsonObject& json = jsonBuffer.createObject();
    
    json["battery"] = 2;
    
    String jsonString;
    json.printTo(jsonString);
    request->send(200, "application/json", jsonString);
  });
  
  server.on("/pictionary", HTTP_GET, [&](AsyncWebServerRequest *request) {
    jsonBuffer.clear();
    JsonObject& json = jsonBuffer.createObject();
    
    json["battery"] = battery_level;
    json["now_showing"] = "red";
    json["now_answering"] = "none";
    json["red"] = PlayersStats::getPlayerValue(0);
    json["blue"] = PlayersStats::getPlayerValue(1);
    json["green"] = PlayersStats::getPlayerValue(2);
    json["yellow"] = PlayersStats::getPlayerValue(3);
    
    String jsonString;
    json.printTo(jsonString);
    request->send(200, "application/json", jsonString);
  });

  server.on("/react", HTTP_GET, [&](AsyncWebServerRequest *request) {
    jsonBuffer.clear();
    JsonObject& json = jsonBuffer.createObject();
    
    json["battery"] = battery_level;
    json["red"] = PlayersStats::getPlayerValue(0);
    json["blue"] = PlayersStats::getPlayerValue(1);
    json["green"] = PlayersStats::getPlayerValue(2);
    json["yellow"] = PlayersStats::getPlayerValue(3);
    
    String jsonString;
    json.printTo(jsonString);
    request->send(200, "application/json", jsonString);
  });

  server.on("/register", HTTP_GET, [&](AsyncWebServerRequest *request) {
    register_master();
    
    jsonBuffer.clear();
    JsonObject& json = jsonBuffer.createObject();
    
    json["battery"] = battery_level;
    
    String jsonString;
    json.printTo(jsonString);
    request->send(200, "application/json", jsonString);
  });
}

void API::handle_request(WiFiServer &server) {
  WiFiClient client = server.available();
  if (!client)
    return;
  
  while(!client.available()){
    delay(1);
  }
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
