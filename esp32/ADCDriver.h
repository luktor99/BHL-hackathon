#ifndef ESP32_ADC_DRIVER_H
#define ESP32_ADC_DRIVER_H

#define BATTERY_PIN 32

class ADCDriver {
public:
  ADCDriver(int pin);
  
  int get_voltage() const;
  
private:
  const int pin;
};

#endif
