#ifndef _SOLDER_STATION_H
#define _SOLDER_STATION_H

// For byte type
#include <Arduino.h>

int get_target_temperature();

void set_target_temperature(int tTmp);

int get_iron_temperature();

void set_iron_temperature(int tTmp);

int get_iron_pwm();

void set_iron_pwm(int pwm);

typedef enum _lcd_mode {
  LCD_OFF,
  LCD_ON,
  LCD_MAX
} lcd_mode;

lcd_mode get_lcd_backlight_mode();

void set_lcd_backlight_mode(lcd_mode status);

byte get_lcd_contrast();

void set_lcd_contrast(byte contrast);

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
