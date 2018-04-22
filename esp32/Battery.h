#ifndef ESP32_BATTERY
#define ESP32_BATTERY

#include "ADCDriver.h"

class Battery {
public:
  Battery(int pin);

  int get_level() const;
  
private:
  ADCDriver adc_driver;
};

extern int battery_level;

#endif

