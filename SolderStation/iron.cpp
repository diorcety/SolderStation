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


#define ADC_TO_TEMP_OFFSET 24.0f

#define PWM_DIV 1024 //default: 64

//R2=68K:
static float iron_gain = 0.39f;

/*
 * Init iron stuff
 */
void iron_init() {
  DEBUG_LOG_LN(DEBUG_STR("Init Iron"));

  //set pins
  pinMode(PIN_PWM_OUT, OUTPUT);
  digitalWrite(PIN_PWM_OUT, LOW);
  pinMode(PIN_PROBE_IN, INPUT);

  // Set PWM
  setPwmFrequency(PIN_PWM_OUT, PWM_DIV);
  analogWrite(PIN_PWM_OUT, 0);
}

/*
 * Reads the temperature value from the ADC:
 */
int iron_get_temperature() {
  int adcValue = analogRead(PIN_PROBE_IN); // read the input on analog pin 0:
  return round(((float) adcValue)*iron_gain+ADC_TO_TEMP_OFFSET); //apply linear conversion to actual temperature
}

/*
 * Get iron max temperature
 */
int iron_get_max_temperature() {
  return MAX_IRON_TEMP_IN_DEGREES;
}

/*
 * Reads the gain
 */
float iron_get_gain() {
  return iron_gain;
}

/*
 * Set the gain
 */
void iron_set_gain(float gain) {
    iron_gain = gain;
}

/*
 * Set iron PWM
 */
void iron_set_pwm(int pwm) {
  analogWrite(PIN_PWM_OUT, pwm);
}
