#ifndef _LED_H
#define _LED_H

#ifdef LED_MODULE

#include "config.h"

// For boolean type
#include <Arduino.h>

/*
 * Init LED stuff
 */
void led_init();

/*
 * Led heat signal
 */
void led_show_heat(boolean show);

#endif //LED_MODULE

#endif //_LED_H
