 #include "ADCDriver.h"

#include <Arduino.h>

 ADCDriver::ADCDriver(int pin)
  : pin(pin)
{}

int ADCDriver::get_voltage() const {
  return analogRead(pin);
}

