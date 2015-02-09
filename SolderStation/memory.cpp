#include "memory.h"
#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_TARGET_TEMPERATURE 0
#define EEPROM_TARGET_TEMPERATURE_SIZE sizeof(int)
#define EEPROM_LCD_BACKLIGHT (EEPROM_TARGET_TEMPERATURE + EEPROM_TARGET_TEMPERATURE_SIZE)
#define EEPROM_LCD_BACKLIGHT_SIZE sizeof(byte)

/* from http://playground.arduino.cc/Code/EEPROMWriteAnything */
template <class T> int EEPROM_writeAnything(int ee, const T& value)
{
    const byte* p = (const byte*)(const void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          EEPROM.write(ee++, *p++);
    return i;
}

/* from http://playground.arduino.cc/Code/EEPROMWriteAnything */
template <class T> int EEPROM_readAnything(int ee, T& value)
{
    byte* p = (byte*)(void*)&value;
    unsigned int i;
    for (i = 0; i < sizeof(value); i++)
          *p++ = EEPROM.read(ee++);
    return i;
}

/*
 * Save the target temperature
 */
void memory_save_target_temperature(int target_temperature) {
  EEPROM_writeAnything(EEPROM_TARGET_TEMPERATURE, target_temperature);
}

/*
 * Load the target temperature
 */
int memory_load_target_temperature() {
  int target_temperature;
  EEPROM_readAnything(EEPROM_TARGET_TEMPERATURE, target_temperature);
  return target_temperature;
}

/*
 * Save the lcd backlight status
 */
void memory_save_lcd_backlight_mode(byte backlight) {
    EEPROM_writeAnything(EEPROM_LCD_BACKLIGHT, backlight);
}

/*
 * Load the lcd backlight status
 */
byte memory_load_lcd_backlight_mode() {
  byte lcd_backlight;
  EEPROM_readAnything(EEPROM_LCD_BACKLIGHT, lcd_backlight);
  return lcd_backlight;
}
