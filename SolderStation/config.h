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

// Maximum iron temperature capability
#define MAX_IRON_TEMP_IN_DEGREES 400

// Default value
#define DEFAULT_STANDBY_TEMPERATURE 150

/*
 * Behaviours
 */
#define BEHAVIOUR_EDIT_TARGET 1 // Allow to edit target temperature in non-standby mode (default)
#define BEHAVIOUR_EDIT_TARGET_ALWAYS 2 // Allow to edit target temeperature in any mode
#define BEHAVIOUR_EDIT_TARGET_N_STANDBY 3 // Allow the temperature of the current mode

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

