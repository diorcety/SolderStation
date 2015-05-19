#ifndef _MEMORY_H
#define _MEMORY_H

// For byte type
#include <Arduino.h>

#ifdef MEMORY_SETTINGS

/*
 * Save the settings
 */
void memory_save_settings(int offset, const void *settings, unsigned int size);

/*
 * Load the settings
 */
void memory_load_settings(int offset, void *settings, unsigned int size);

#endif //MEMORY_SETTINGS

#endif //_MEMORY_H
