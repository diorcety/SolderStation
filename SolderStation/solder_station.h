#ifndef _SOLDER_STATION_H
#define _SOLDER_STATION_H

// For byte type
#include <Arduino.h>

int get_target_temperature();

void set_target_temperature(int tTmp);

void set_iron_temperature(int tTmp);

int get_iron_temperature();

int get_iron_pwm();

void set_iron_pwm(int pwm);

#endif //_SOLDER_STATION_H
