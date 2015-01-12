#ifndef _MEMORY_H
#define _MEMORY_H

/*
 * Save the target temperature
 */
void memory_save_target_temperature(int target_temperature);

/*
 * Load the target temperature
 */
int memory_load_target_temperature();

#endif //_MEMORY_H
