#ifndef _CONFIG_MO_H
#define _CONFIG_MO_H

// Iron pins
#define PIN_PWM_OUT 3
#define PIN_PROBE_IN A7

// Controls
#define ROTATING_UP_DOWN
#define ROTATING_UP_DOWN_DIVIDER 4
#define BUTTON_UP_PIN 13
#define BUTTON_UP_PULL 1
#define BUTTON_UP_INVERTED 1

#define BUTTON_DOWN_PIN 12
#define BUTTON_DOWN_PULL 1
#define BUTTON_DOWN_INVERTED 1

#define BUTTON_STANDBY
#define BUTTON_STANDBY_PIN A5
#define BUTTON_STANDBY_PULL 1
#define BUTTON_STANDBY_INVERTED 1

// SEG7 Module
#define SEG7_MODULE
#define SEG7_A_PIN 6
#define SEG7_B_PIN 7
#define SEG7_C_PIN 8
#define SEG7_D_PIN 5
#define SEG7_E_PIN A3
#define SEG7_F_PIN 2
#define SEG7_G_PIN 4
#define SEG7_DP_PIN A2
#define SEG7_SEL0_PIN 9
#define SEG7_SEL1_PIN 10
#define SEG7_SEL2_PIN 11
#define SEG7_PWM_DOT

// LED Module
#define LED_MODULE
#define LED_HEAT A4
#define LED_HEAT_INVERTED 0

// Serial Module
#define SERIAL_MODULE
#define SERIAL_BAUD 115200

// Override UI loop -> LED
#undef DELAY_UI_LOOP
#define DELAY_UI_LOOP 5

#define HEAT_PROTECTION
#define MEMORY_SETTINGS

#endif //_CONFIG_DC3MKB_H
