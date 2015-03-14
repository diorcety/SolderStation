#ifndef _CONFIG_H
#define _CONFIG_H

// Enable debug serial
#define DEBUG

// Main delay
#define DELAY_MAIN_LOOP 10
#define DELAY_UI_LOOP 20
#define DELAY_SETTINGS_LOOP 1000
#define DELAY_SAVE_SETTINGS_LOOP 10000
#define DELAY_EDIT_TIME 3000

// Gain
#define CNTRL_GAIN 10

// Iron delay before measuring
#define DELAY_BEFORE_MEASURE_IN_MS 10

#define MAX_IRON_TEMP_IN_DEGREES 400

#define TEMP_STEP 5

#include "config_xxx.h"
//#include "config_dc3mkb.h"
//#include "config_mo.h"

#if defined(SERIAL_MODULE) && defined(DEBUG)
#define SERIAL_DEBUG
#endif

#ifdef SERIAL_MODULE
#include <HardwareSerial.h>
#endif

#endif //_CONFIG_H

