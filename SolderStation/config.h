#ifndef _CONFIG_H
#define _CONFIG_H

// Enable debug serial
#define DEBUG

// Main delay
#define DELAY_MAIN_LOOP 10
#define DELAY_UI_LOOP 20
#define DELAY_SETTINGS_LOOP 1000
#define DELAY_SAVE_SETTINGS_LOOP 10000

// Gain
#define CNTRL_GAIN 10


/*
 * Iron
 */
// Iron pins
#define PIN_PWM_OUT 3
#define PIN_PROBE_IN A0

// Iron delay before measuring
#define DELAY_BEFORE_MEASURE_IN_MS 10

#define MAX_IRON_TEMP_IN_DEGREES 400

/*
 * Input
 */
// Buttons pins
#define BUTTON_UP_PIN 7
#define BUTTON_UP_PULL 1
#define BUTTON_UP_INVERTED 1

#define BUTTON_DOWN_PIN 6
#define BUTTON_DOWN_PULL 1
#define BUTTON_DOWN_INVERTED 1

#define BUTTON_SELECT_PIN 5
#define BUTTON_SELECT_PULL 1
#define BUTTON_SELECT_INVERTED 1

#define BUTTON_BACK_PIN 4
#define BUTTON_BACK_PULL 1
#define BUTTON_BACK_INVERTED 1

#ifdef DEBUG
#include <HardwareSerial.h>
#endif

#endif //_CONFIG_H

