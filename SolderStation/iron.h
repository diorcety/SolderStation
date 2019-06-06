#ifndef _IRON_H
#define _IRON_H

/*
 * Init iron stuff
 */
void iron_init();

/*
 * Reads the temperature value from the ADC:
 */
int iron_get_temperature();

/*
 * Get iron max temperature
 */
int iron_get_max_temperature();

/*
 * Reads the gain
 */
float iron_get_gain();

/*
 * Set the gain
 */
void iron_set_gain(float gain);

/*
 * Set iron PWM
 */
void iron_set_pwm(int pwm);

#endif //_IRON_H
