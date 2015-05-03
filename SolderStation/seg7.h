#ifndef _SEG7_H
#define _SEG7_H

#ifdef SEG7_MODULE

// For byte type
#include <Arduino.h>

/*
 * Init SEG7 stuff
 */
void seg7_init();

/*
 * Print temperature on 7-seg
 */
void seg7_print(int temp);

/*
 * Print heat pwm
 */
void seg7_print_heat(byte pwm);

#endif //SEG7_MODULE

#endif //_SEG7_H
