#include "config.h"
#include "led.h"

#ifdef LED_MODULE

/*
 * Init LED stuff
 */
void led_init() {
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
