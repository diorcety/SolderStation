#include "memory.h"
#include <Arduino.h>
#include <EEPROM.h>

#define EEPROM_TARGET_TEMPERATURE 0
#define EEPROM_TARGET_TEMPERATURE_SIZE sizeof(int)

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
