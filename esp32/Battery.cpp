 #include "Battery.h"

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

