#include "config.h"
#include "iron.h"
#include "utils.h"
#include <Arduino.h>

#ifndef PIN_PWM_OUT
#error Missing configuration of PIN_PWM_OUT
#endif //PIN_PWM_OUT

#ifndef PIN_PROBE_IN
#error Missing configuration of PIN_PROBE_IN
#endif //PIN_PROBE_IN

//R2=68K:
#define ADC_TO_TEMP_GAIN 0.39
#define ADC_TO_TEMP_OFFSET 23.9

#define PWM_DIV 1024 //default: 64

/*
 * Init iron stuff
 */
void iron_init() {
  DEBUG_LOG_LN(DEBUG_STR("Init Iron"));
  //set pin directions:
  pinMode(PIN_PWM_OUT, OUTPUT);
  pinMode(PIN_PROBE_IN, INPUT);
  
  setPwmFrequency(PIN_PWM_OUT, PWM_DIV);
}

/*
 * Reads the temperature value from the ADC:
 */
int iron_get_temperature() {
  int adcValue = analogRead(PIN_PROBE_IN); // read the input on analog pin 0:
  return round(((float) adcValue)*ADC_TO_TEMP_GAIN+ADC_TO_TEMP_OFFSET); //apply linear conversion to actual temperature
}

/*
 * Get iron max temperature
 */
int iron_get_max_temperature() {
  return MAX_IRON_TEMP_IN_DEGREES;
}

/*
 * Set iron PWM
 */
void iron_set_pwm(int pwm) {
  analogWrite(PIN_PWM_OUT, pwm);
}
