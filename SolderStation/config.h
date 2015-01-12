#ifndef _CONFIG_H
#define _CONFIG_H

// Enable debug serial
#define DEBUG

// Main delay
#define DELAY_MAIN_LOOP_IN_MS 10

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
#define BUTTON_DOWN_PIN 6
#define BUTTON_SELECT_PIN 5
#define BUTTON_BACK_PIN 4

#endif //_CONFIG_H

