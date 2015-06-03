#include "config.h"
#include "led.h"
#include "utils.h"

#ifdef LED_MODULE

#ifndef LED_HEAT
#error Missing configuration of LED_HEAT
#endif //LED_HEAT

#ifndef LED_HEAT_INVERTED
#error Missing configuration of LED_HEAT_INVERTED
#endif //LED_HEAT_INVERTED

/*
 * Init LED stuff
 */
void led_init() {
  DEBUG_LOG_LN(DEBUG_STR("Init LED"));
  // Switch off the LED
  digitalWrite(LED_HEAT, LED_HEAT_INVERTED^LOW); 
  pinMode(LED_HEAT, OUTPUT);
}

/*
 * Led heat signal
 */
void led_show_heat(boolean show) {
  digitalWrite(LED_HEAT, LED_HEAT_INVERTED^show); 
}

#endif //LED_MODULE
