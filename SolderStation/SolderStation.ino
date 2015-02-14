#include "config.h"

// Hack for Arduino IDE
#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <buttons.h>

#include <SimpleTimer.h>
#include "solder_station.h"
#include "iron.h"
#include "lcd.h"
#include "display.h"
#include "controls.h"
#include "memory.h"
#include "lang.h"

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
   int iron_temperature = get_iron_temperature();
#ifdef DEBUG
   Serial.print("Iron Temp.=");
   Serial.println(iron_temperature);
#endif //DEBUG
   int temperature = get_standby_mode()? get_standby_temperature():get_target_temperature();
   int iron_pwm = compute_iron_pwm(iron_temperature, temperature);
   set_iron_pwm(iron_pwm);
   iron_pwm = get_iron_pwm();
#ifdef DEBUG
   Serial.print("Iron PWM=");
   Serial.println(iron_pwm);
#endif //DEBUG
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
}

/*
 * Setup function
 */
void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println("Booting...");
#endif //DEBUG

  // Init modules
  iron_init();
  lcd_init();
  controls_init();
  display_init();
   
  // Load settings
  load_settings();
  
  // Init timers
  uiTimer.setInterval(DELAY_UI_LOOP, display_update);
  ironTimer.setInterval(DELAY_MAIN_LOOP, update_iron);
  settingsTimer.setInterval(DELAY_SETTINGS_LOOP, update_settings);
  saveTimer.setInterval(DELAY_SAVE_SETTINGS_LOOP, save_settings);
    
#ifdef DEBUG
  Serial.println("Solder station V0.1");
#endif //DEBUG

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
