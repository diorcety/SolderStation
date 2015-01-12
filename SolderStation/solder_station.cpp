#include "solder_station.h"
#include "iron.h"

int iron_temperature = 0;
byte iron_pwm = 0;
int target_temperature = 0;

int get_target_temperature() {
  return target_temperature;
}

void set_target_temperature(int tTmp) {
  // Verify target temperature range
  int max_iron_temp = iron_get_max_temperature();
  target_temperature = tTmp > max_iron_temp? max_iron_temp : (tTmp < 0? 0 : tTmp);
}

void set_iron_temperature(int tTmp) {
  iron_temperature = tTmp;
}


int get_iron_temperature() {
  return iron_temperature;
}

int get_iron_pwm() {
  return iron_pwm;
}

void set_iron_pwm(int pwm) {
  // Verify pwm range
  iron_pwm = pwm > 255 ? 255 : (pwm < 0 ? 0 : pwm);
}

