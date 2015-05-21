#include "config.h"

// Hack for Arduino IDE
#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <buttons.h>
#define LIBCALL_PINCHANGEINT
#include <PinChangeInt.h>


#include <SimpleTimer.h>
#include "solder_station.h"
#include "iron.h"
#include "lcd.h"
#include "led.h"
#include "seg7.h"
#include "display.h"
#include "controls.h"
#include "memory.h"
#include "lang.h"
#include "utils.h"

/*
 * Main functions
 */
int compute_iron_pwm(int actual_temperature, int target_temperature) {
  // compute difference between target and actual temperature:
  int diff = target_temperature - actual_temperature;
  
  // apply P controller:  
  int pwm = diff*CNTRL_GAIN;
  
  return pwm;
}

void update_iron_temperature() {
  if(is_fault_mode()) {
    set_iron_pwm(0);
    iron_set_pwm(0);
  } else {
    int temperature;
    if(get_standby_mode()) {
      temperature = get_standby_temperature();
    } else {
      temperature = get_target_temperature();
    }
    set_iron_pwm(compute_iron_pwm(get_iron_temperature(), temperature));
    iron_set_pwm(get_iron_pwm());
  }
  
#ifdef DEBUG
  static unsigned long last_debug_log = 0;
  unsigned long current_check = millis();
  if(last_debug_log + 1000 <= current_check) {
    last_debug_log = current_check;
    if(is_fault_mode()) {
      DEBUG_LOG_LN("FAULT");
    } else {
      DEBUG_LOG("Iron Temp.=");
      DEBUG_LOG_LN(get_iron_temperature());
      int temperature;
      if(get_standby_mode()) {
        DEBUG_LOG("Standby Temp.=");
        temperature = get_standby_temperature();
      } else {
        DEBUG_LOG("Target Temp.=");
        temperature = get_target_temperature();
      }
      DEBUG_LOG_LN(temperature);
      DEBUG_LOG("Iron PWM=");
      DEBUG_LOG_LN(get_iron_pwm());
    }
  }
#endif //DEBUG
}

SimpleTimer uiTimer; // UI timer
SimpleTimer ironTimer; // Iron timer
#if 0 // Not really usefull for the moment
SimpleTimer settingsTimer; // Settings timer
#endif
SimpleTimer saveTimer; // Save timer

void update_iron() {
  static byte cycle = 0;
  if((++cycle) & 0x1) { // TODO better stuff
    iron_set_pwm(0); //switch off heater and wait for some time (to get low pass filter in steady state)
  } else {
    int iron_temperature = iron_get_temperature();
    set_iron_temperature(iron_temperature);
    update_iron_temperature();
  }
  
#ifdef HEAT_PROTECTION
#define CHECK_MEAN_PERIOD_MS 100
#define CHECK_MEAN_COUNT 20.0f
#define CHECK_PROTECTION_PERIOD_MS 1000
  static float pwm_mean = 0.0f;
  static int pwm_time = 0;
  static unsigned long last_mean_check = 0;
  static unsigned long last_protection_check = 0;
  unsigned long current_check = millis();
  if(last_mean_check + CHECK_MEAN_PERIOD_MS <= current_check) {
    last_mean_check = current_check;
    
    // Update pwm
    float pwm = pwm_mean * (CHECK_MEAN_COUNT - 1.0f);
    pwm += get_iron_pwm();
    pwm_mean = pwm / CHECK_MEAN_COUNT;
  }
  
  if(last_protection_check + CHECK_PROTECTION_PERIOD_MS <= current_check) {
    last_protection_check = current_check;
    
    DEBUG_LOG("PWM protection mean=");
    DEBUG_LOG_LN(pwm_mean);
    DEBUG_LOG("PWM protection time=");
    DEBUG_LOG_LN(pwm_time);
   
    // Check pwm
    if(pwm_mean >= (float)get_protection_pwm()) {
      pwm_time++;
    } else {
      pwm_time = 0;
    }
    
    if(pwm_time >= get_protection_time()) {
      set_fault_mode();
    }
  }
#undef CHECK_MEAN_PERIOD_MS
#undef CHECK_MEAN_COUNT
#undef CHECK_PROTECTION_PERIOD_MS
#endif //HEAT_PROTECTION
}

/*
 * Setup function
 */
void setup() {
#ifdef SERIAL_MODULE
  Serial.begin(115200);
#endif //SERIAL_MODULE
  DEBUG_LOG_LN("Booting...");

  // Init modules
  iron_init();
#ifdef LCD_MODULE
  lcd_init();
#endif //LCD_MODULE
#ifdef LED_MODULE
  led_init();
#endif //LED_MODULE
#ifdef SEG7_MODULE
  seg7_init();
#endif //SEG7_MODULE
  controls_init();
  display_init();
   

#ifdef MEMORY_SETTINGS
#ifndef ROTATING_UP_DOWN
  // Check if we load default settings or not
  if(!(digitalRead(BUTTON_UP_PIN)^BUTTON_UP_INVERTED) || !(digitalRead(BUTTON_DOWN_PIN)^BUTTON_DOWN_INVERTED)) {
#endif //ROTATING_UP_DOWN
    // Load settings
    load_settings();
#ifndef ROTATING_UP_DOWN
  } else {
    DEBUG_LOG_LN("Load default settings");
  }
#endif //ROTATING_UP_DOWN
#endif //MEMORY_SETTINGS
  
  // Init timers
  uiTimer.setInterval(DELAY_UI_LOOP, display_update);
  ironTimer.setInterval(DELAY_MAIN_LOOP, update_iron);
#if 0 // Not really usefull for the moment
  settingsTimer.setInterval(DELAY_SETTINGS_LOOP, update_settings);
#endif
  saveTimer.setInterval(DELAY_SAVE_SETTINGS_LOOP, save_settings);
    
  DEBUG_LOG_LN("Boot end!");
  DEBUG_LOG_LN("Solder station V0.1\n");

  // Update data
  update_iron();
  update_settings();
}

/*
 * Main loop
 */
void loop() {
  uiTimer.run(); 
  ironTimer.run();
#if 0 // Not really usefull for the moment
  settingsTimer.run();
#endif
  saveTimer.run();
}
