#ifndef _CONFIG_XXX_H
#define _CONFIG_XXX_H

// Redefine gain
#undef CNTRL_GAIN
#define CNTRL_GAIN 25

// Temperature meaning (in milliseconds)
#define TEMP_MEAN 100

// Temperature refresh (in milliseconds)
#define TEMP_IRON_REFRESH 500

// Temperature step number
#define TEMP_STEP 5

// Iron pins
#define PIN_PWM_OUT 3
#define PIN_PROBE_IN A0

// Controls
#define BUTTON_EXTENDED
#define ROTATING_UP_DOWN
#define ROTATING_UP_DOWN_DIVIDER 4
#define BUTTON_UP_PIN 7
#define BUTTON_UP_PULL 0
#define BUTTON_UP_INVERTED 0

#define BUTTON_DOWN_PIN 6
#define BUTTON_DOWN_PULL 0
#define BUTTON_DOWN_INVERTED 1

#define BUTTON_SELECT_PIN 5
#define BUTTON_SELECT_PULL 0
#define BUTTON_SELECT_INVERTED 0

#define BUTTON_BACK_PIN 4
#define BUTTON_BACK_PULL 0
#define BUTTON_BACK_INVERTED 0

#define BUTTON_STANDBY
#define BUTTON_STANDBY_PIN A2
#define BUTTON_STANDBY_PULL 1
#define BUTTON_STANDBY_INVERTED 1

// Menu module
#define MENU_MODULE

// LCD Module
#define LCD_MODULE
#define LCD_SHOW_HEAT
#define LCD_ST7735_MODULE
#define LCD_ST7735_CS 10
#define LCD_ST7735_DC 9
#define LCD_ST7735_RESET 8
#define LCD_ST7735_BL 2

// LED Module
#define LED_MODULE
#define LED_HEAT A3
#define LED_HEAT_INVERTED 0

// Serial Module
#define SERIAL_MODULE
#define SERIAL_BAUD 115200

#define HEAT_PROTECTION
// 33%
#define HEAT_PROTECTION_VALUE ((int)((33*256)/100))
// 15 seconds
#define HEAT_PROTECTION_TIME 15
#define HEAT_PROTECTION_DROP 40
#define MEMORY_SETTINGS

// Behaviours
#define BEHAVIOUR_EDIT BEHAVIOUR_EDIT_TARGET_N_STANBDY

#endif //_CONFIG_XXX_H
