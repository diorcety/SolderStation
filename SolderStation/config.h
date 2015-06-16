#ifndef _CONFIG_H
#define _CONFIG_H

/*
 * General configuration
 */

// Enable debug serial
#define DEBUG

// Main delay
#define DELAY_MAIN_LOOP 10
#define DELAY_UI_LOOP 100
#define DELAY_SETTINGS_LOOP 1000
#define DELAY_SAVE_SETTINGS_LOOP 10000
#define DELAY_EDIT_TIME 3000

// Gain
#define CNTRL_GAIN 10

// Iron delay before measuring
#define DELAY_BEFORE_MEASURE_IN_MS 10

// Maximum iron temperature capability
#define MAX_IRON_TEMP_IN_DEGREES 400

// Temperature meaning (in milliseconds)
#define TEMP_MEAN 500

// Temperature step number
#define TEMP_STEP 5

/*
 * Board configuration
 */

#define CONFIG_DC3MKB 1
#define CONFIG_ELECTROLAB 2
#define CONFIG_XXX 3

// Set the board name. Please change the name of the configuration following your board
//#define CONFIG_NAME CONFIG_XXX

// Use correct configuration
#if CONFIG_NAME==CONFIG_XXX
#include "config_xxx.h"
#elif CONFIG_NAME==CONFIG_DC3MKB
#include "config_dc3mkb.h"
#elif CONFIG_NAME==CONFIG_ELECTROLAB
#include "config_electrolab.h"
#else
#error Invalid or no configuration defined
#endif //CONFIG_NAME

/*
 * Debug configuration
 */

#if defined(SERIAL_MODULE) && defined(DEBUG)
#define SERIAL_DEBUG
#endif

#ifdef SERIAL_MODULE
#include <HardwareSerial.h>
#endif

#endif //_CONFIG_H

