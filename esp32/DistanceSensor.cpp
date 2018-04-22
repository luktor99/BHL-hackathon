#include "DistanceSensor.h"

DistanceSensor::DistanceSensor(int pin, int activation_threashold)
  : adc_driver(pin),
  activation_threashold(activation_threashold)
{}

bool DistanceSensor::is_activated() const {
  return adc_driver.get_voltage() > activation_threashold;
}

