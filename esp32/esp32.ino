// DistanceSensor.h ///////////////////////////////////////////////////////
#define DISTANCE_PIN_1 36
#define DISTANCE_PIN_2 39
#define DISTANCE_PIN_3 34
#define DISTANCE_PIN_4 35

class DistanceSensor {
public:
  DistanceSensor(int pin, int activation_threashold);
  
  int get_voltage() const;
  bool is_activated() const;
  
private:
  const int pin;
  const int activation_threashold;
};

// DistanceSensor.cpp ////////////////////////////////////////////////////
DistanceSensor::DistanceSensor(int pin, int activation_threashold)
  : pin(pin), activation_threashold(activation_threashold)
{}

int DistanceSensor::get_voltage() const {
  return analogRead(pin);
}

bool DistanceSensor::is_activated() const {
  return get_voltage() > activation_threashold;
}

// LEDDriver.h ///////////////////////////////////////////////////////////
// libraries => git@github.com:samguyer/FastLED.git
#include <FastLED.h>

#define LED_DATA_PIN 23 
#define NUM_LEDS 10

namespace LEDColour {
  int RED = 0;
  int YELLOW = 42;
  int GREEN = 85;
  int BLUE = 171;
}

class LEDDriver {
public:
  LEDDriver();

  void next_wave_step(int hue);
  void battery_level(int level);
  
private:
  CRGBArray<NUM_LEDS> leds;

  void set_first(int count, int hue);
};

// LEDDriver.cpp /////////////////////////////////////////////////////////
LEDDriver::LEDDriver() {
  FastLED.addLeds<WS2812, LED_DATA_PIN>(leds, NUM_LEDS);
}

void LEDDriver::next_wave_step(int hue) {
  int sector_size = 255 / 4;
  
  for(int i = 0; i < NUM_LEDS; i++) {   
    if (i < 1)
      leds[i] = CHSV(i * sector_size + hue,255,255);
    else
      leds[i] = CHSV(0, 0, 0);
  } 
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

// WiFiDriver.h ///////////////////////////////////////////////////////////
#include <WiFi.h>
const char *ssid = "Melka";
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
  int control(String cmd) {
    Serial.print("API cmd = ");
    Serial.println(cmd);
    return 1;
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
  rest.function((char*)"control", APIFunction::control);

  rest.set_id("123456");
  rest.set_name((char*)"Melka");
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
DistanceSensor distance_sensor_1(DISTANCE_PIN_1, 1000);
LEDDriver led_driver;
API api;

void setup() {
  Serial.begin(115200);  
  
  api.configure();

  WiFi.softAP(ssid, password);
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());
  server.begin();
}

enum class MelkaState {
  INITIALIZE,
  WAIT_FOR_MASTER,
  WAIT_FOR_PLAYERS,
  GAME,
  AFTER_GAME
};

static uint8_t hue = 0;
MelkaState melka_state = MelkaState::INITIALIZE;
void loop() {
  api.handle_request(server);

  static unsigned long last_time = millis();
  if (millis() - last_time > 500) {
    last_time = millis();

    Serial.println("Slow loop iteration:");
    switch(melka_state) {
    case MelkaState::INITIALIZE:
      Serial.println("INITIALIZE");
      melka_state = MelkaState::WAIT_FOR_MASTER;  
      break;
    case MelkaState::WAIT_FOR_MASTER:
      Serial.println("WAIT_FOR_MASTER");
      led_driver.next_wave_step(hue);
      hue += 15;
//        led_driver.battery_level(1);
      // waitForServerRequest?
      break;
    case MelkaState::WAIT_FOR_PLAYERS:
      break;
    case MelkaState::GAME:
      break;
    case MelkaState::AFTER_GAME:
      break;
    }
    
    int value = distance_sensor_1.get_voltage();
    bool isActive = distance_sensor_1.is_activated();
    Serial.print("distance_sensor_1: value = ");
    Serial.print(value);
    Serial.print(" is_activated = ");
    Serial.println(isActive);
  }
}
