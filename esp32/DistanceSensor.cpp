#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int pin, int activation_threashold)
  : adc_driver(pin),
  activation_threashold(activation_threashold),
  last_voltage(adc_driver.get_voltage())
{}

bool DistanceSensor::is_activated() { 
  int voltage = adc_driver.get_voltage();
  bool state = (voltage - last_voltage > 200) &&  (voltage > activation_threashold);  
  last_voltage = voltage;
  return state;
}

