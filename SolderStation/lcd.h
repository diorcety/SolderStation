#ifndef _LCD_H
#define _LCD_H

// For boolean type
#include <Arduino.h>

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

/*
 * Get backlight status
 */
boolean lcd_get_backlight();

/*
 * Print heat signal
 */
void lcd_print_heat(boolean show);

/*
 * Print iron temperature
 */
void lcd_print_iron_temperature(int temperature);

/*
 * Print target temperature
 */
void lcd_print_target_temperature(int temperature);

/*
 * Print title
 */
void lcd_print_title(String title);

#endif //_LCD_H

