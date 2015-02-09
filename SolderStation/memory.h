#ifndef _MEMORY_H
#define _MEMORY_H

// For byte type
#include <Arduino.h>

/*
 * Save the target temperature
 */
void memory_save_target_temperature(int target_temperature);

/*
 * Load the target temperature
 */
int memory_load_target_temperature();

/*
 * Save the lcd backlight status
 */
void memory_save_lcd_backlight_mode(byte backlight);

/*
 * Load the lcd backlight status
 */
byte memory_load_lcd_backlight_mode();

#endif //_MEMORY_H
