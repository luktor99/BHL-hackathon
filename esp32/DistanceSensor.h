#ifndef ESP32_DISTANCE_SENSOR_H
#define ESP32_DISTANCE_SENSOR_H

#include "ADCDriver.h"

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

#endif

