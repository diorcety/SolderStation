#ifndef _SOLDER_STATION_H
#define _SOLDER_STATION_H

#include "config.h"

// For byte type
#include <Arduino.h>

int get_target_temperature();

void set_target_temperature(int tTmp);

int get_standby_temperature();

void set_standby_temperature(int tTmp);

boolean get_standby_mode();

void set_standby_mode(boolean standby);

int get_iron_temperature();

void set_iron_temperature(int tTmp);

void set_fault_mode();

bool is_fault_mode();

int get_iron_pwm();

void set_iron_pwm(int pwm);

#ifdef LCD_MODULE

typedef enum _lcd_mode {
  LCD_OFF,
  LCD_ON,
  LCD_MAX
} lcd_mode;

lcd_mode get_lcd_backlight_mode();

void set_lcd_backlight_mode(lcd_mode status);

byte get_lcd_contrast();

void set_lcd_contrast(byte contrast);

byte get_language();

void set_language(byte lang);

typedef enum _temperature_unit {
  TEMP_CELSIUS,
  TEMP_FAHRENHEIT,
  TEMP_MAX
} temperature_unit;

temperature_unit get_temperature_unit();

void set_temperature_unit(temperature_unit ts);

#endif //LCD_MODULE

#ifdef HEAT_PROTECTION

byte get_protection_pwm();

void set_protection_pwm(byte pwm);

int get_protection_time();

void set_protection_time(int time);

#endif //HEAT_PROTECTION

/*
 * Load settings from the memory
 */
void load_settings();

/*
 * Save settings to the memory
 */
void save_settings();

/*
 * Update settings
 */
void update_settings();

#endif //_SOLDER_STATION_H
