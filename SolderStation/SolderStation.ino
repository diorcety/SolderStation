#include <SoftwareSerial.h>

// Hack for Arduino IDE
#include <EEPROM.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include <buttons.h>

#include <SimpleTimer.h>
#include "solder_station.h"
#include "config.h"
#include "iron.h"
#include "screen.h"
#include "lcd.h"
#include "display.h"
#include "controls.h"
#include "memory.h"

/*
 * Load settings from the memory
 */
void load_settings() {
  set_target_temperature(memory_load_target_temperature());
  set_lcd_backlight_mode((lcd_mode)memory_load_lcd_backlight_mode());
}

/*
 * Save settings to the memory
 */
void save_settings() {
  memory_save_target_temperature(get_target_temperature());
  memory_save_lcd_backlight_mode((byte)get_lcd_backlight_mode());
}

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
   int iron_pwm = compute_iron_pwm(iron_temperature, get_target_temperature());
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

void update_ui() {
   // Inputs
   constrols_update();
   
   // Outputs
   display_update();
}

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

void update_settings() {
  lcd_mode lm = get_lcd_backlight_mode();
  lcd_set_backlight(lm > LCD_OFF);
}

/*
 * Setup function
 */
void setup() {
#ifdef DEBUG
  Serial.begin(115200);
  Serial.println("Booting...");
#endif //DEBUG

  // Init timers
  uiTimer.setInterval(DELAY_UI_LOOP, update_ui);
  ironTimer.setInterval(DELAY_MAIN_LOOP, update_iron);
  settingsTimer.setInterval(DELAY_SETTINGS_LOOP, update_settings);
  saveTimer.setInterval(DELAY_SAVE_SETTINGS, save_settings);

  // Init modules
  iron_init();
  lcd_init();
  controls_init();
  display_init();
   
  // Load settings
  load_settings();
    
#ifdef DEBUG
  Serial.println("Solder station V0.1");
#endif //DEBUG
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
