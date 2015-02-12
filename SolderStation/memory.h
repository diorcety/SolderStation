#ifndef _MEMORY_H
#define _MEMORY_H

// For byte type
#include <Arduino.h>

/*
 * Save the settings
 */
void memory_save_settings(int offset, const void *settings, unsigned int size);

/*
 * Load the settings
 */
void memory_load_settings(int offset, void *settings, unsigned int size);

#endif //_MEMORY_H
