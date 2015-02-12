#ifndef _UTILS_H
#define _UTILS_H

/*
 * Set the frequency of the PWM output (code from http://playground.arduino.cc/Code/PwmFrequency):
 */
void setPwmFrequency(int pin, int divisor);

const char * my_sprintf(const char *format, ...);

#endif //_UTILS_H
