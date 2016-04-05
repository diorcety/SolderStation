#ifndef _LCD_H
#define _LCD_H

#include "config.h"

#ifdef LCD_MODULE

// For boolean type
#include <Arduino.h>

#define DEGREE_SYM "\xF8"

/*
 * Init LCD stuff
 */
void lcd_init();

/*
 * Clear lcd
 */
void lcd_clear();

/*
 * Enable/Disable backlight
 */
void lcd_set_backlight(boolean enable);

#ifdef LCD_MODULE_CONTRAST
/*
 * Set contrast
 */
void lcd_set_contrast(byte contrast);
#endif //LCD_MODULE_CONTRAST

/*
 * Print heat pwm
 */
void lcd_print_heat(byte pwm);

/*
 * Print iron temperature
 */
void lcd_print_iron_temperature(int temperature);

/*
 * Print target temperature
 */
void lcd_print_target_temperature(int temperature);

/*
 * Print standby temperature
 */
void lcd_print_standby_temperature(int temperature);

/*
 * Print temperature unit
 */
void lcd_print_temperature_unit();

/*
 * Print title
 */
void lcd_print_title(const char *title);

/*
 * Print fault
 */
void lcd_print_fault();

typedef enum {
  ITEM_NONE,
  ITEM_SELECTED,
  ITEM_EDITION,
} item_state;
/*
 * Print item
 */
void lcd_print_item(byte line, const char *item, const char *value, item_state state);

byte lcd_item_count();

/*
 * Display on the lcd
 */
void lcd_display();

#endif //LCD_MODULE

#endif //_LCD_H

