#ifndef _UTILS_H
#define _UTILS_H

/*
 * Set the frequency of the PWM output (code from http://playground.arduino.cc/Code/PwmFrequency):
 */
void setPwmFrequency(int pin, int divisor);

const char * my_sprintf(const char *format, ...);

#if defined(SERIAL_MODULE) && defined(SERIAL_DEBUG)
#define DEBUG_LOG(x) Serial.print(x)
#define DEBUG_LOG_LN(x) Serial.println(x)
#else
#define DEBUG_LOG(x)
#define DEBUG_LOG_LN(x)
#endif

#endif //_UTILS_H
