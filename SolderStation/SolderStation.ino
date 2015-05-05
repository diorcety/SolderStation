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
       DEBUG_LOG_LN("FAULT");
       set_iron_pwm(0);
       return;
   }
   int iron_temperature = get_iron_temperature();
   DEBUG_LOG("Iron Temp.=");
   DEBUG_LOG_LN(iron_temperature);
   int temperature;
   if(get_standby_mode()) {
     DEBUG_LOG("Standby Temp.=");
     temperature = get_standby_temperature();
   } else {
     DEBUG_LOG("Target Temp.=");
     temperature = get_target_temperature();
   }
   DEBUG_LOG_LN(temperature);
   int iron_pwm = compute_iron_pwm(iron_temperature, temperature);
   set_iron_pwm(iron_pwm);
   iron_pwm = get_iron_pwm();
   DEBUG_LOG("Iron PWM=");
   DEBUG_LOG_LN(iron_pwm);
   iron_set_pwm(iron_pwm);
}

SimpleTimer uiTimer; // UI timer
SimpleTimer ironTimer; // Iron timer
SimpleTimer settingsTimer; // Settings timer
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
  static unsigned int power_milli = 0;
  if(get_iron_pwm() >= get_protection_pwm()) {
    power_milli += DELAY_MAIN_LOOP;
  } else {
    power_milli = 0;
  }
  if(power_milli >= (get_protection_time() * 1000)) {
    set_fault_mode();
  }
#endif
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
   
  // Check if we load default settings or not
  if(!(digitalRead(BUTTON_UP_PIN)^BUTTON_UP_INVERTED) || !(digitalRead(BUTTON_DOWN_PIN)^BUTTON_DOWN_INVERTED)) {
    // Load settings
    load_settings();
  } else {
    DEBUG_LOG_LN("Load default settings");
  }
  
  // Init timers
  uiTimer.setInterval(DELAY_UI_LOOP, display_update);
  ironTimer.setInterval(DELAY_MAIN_LOOP, update_iron);
#if 0 // Not really usefull for the moment
  settingsTimer.setInterval(DELAY_SETTINGS_LOOP, update_settings);
#endif
  saveTimer.setInterval(DELAY_SAVE_SETTINGS_LOOP, save_settings);
    
  DEBUG_LOG_LN("Solder station V0.1");

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
  settingsTimer.run();
  saveTimer.run();
}
