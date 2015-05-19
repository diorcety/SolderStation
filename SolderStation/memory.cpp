#include "config.h"
#include "memory.h"
#include <Arduino.h>
#include <EEPROM.h>

#ifdef MEMORY_SETTINGS

/*
 * Save the settings
 */
void memory_save_settings(int offset, const void *settings, unsigned int size) {
    const byte* p = (const byte*)settings;
    unsigned int i;
    for (i = 0; i < size; i++)
          EEPROM.write(offset++, *p++);
}

/*
 * Load the settings
 */
void memory_load_settings(int offset, void *settings, unsigned int size) {
    byte* p = (byte*)settings;
    unsigned int i;
    for (i = 0; i < size; i++)
          *p++ = EEPROM.read(offset++);
}

#endif //MEMORY_SETTINGS
