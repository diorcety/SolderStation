#include "config.h"
#include "solder_station.h"
#include "iron.h"
#include "memory.h"
#include "utils.h"
#include "lcd.h"
#include "lang.h"

static int iron_temperature = 0;
static byte iron_pwm = 0;
static boolean standby_mode = false;

#define CHECKSUM_VALUE 0xDEADBEAF

struct _memory_settings {
  int target_temperature;
  int standby_temperature;
#ifdef LCD_MODULE
  lcd_mode lcd_backlight_mode;
  byte lcd_contrast;
  byte language;
  temperature_unit tu;
#endif //LCD_MODULE
  unsigned long checksum;
} settings = {
  300,
  150,
#ifdef LCD_MODULE
  LCD_ON,
  30,
  0,
  TEMP_CELSIUS,
#endif //LCD_MODULE
  CHECKSUM_VALUE
};

int get_target_temperature() {
  return settings.target_temperature;
}

void set_target_temperature(int tTmp) {
  // Verify target temperature range
  int max_iron_temp = iron_get_max_temperature();
  settings.target_temperature = tTmp > max_iron_temp? max_iron_temp : (tTmp < 0? 0 : tTmp);
}

int get_standby_temperature() {
  return settings.standby_temperature;
}

void set_standby_temperature(int tTmp) {
  // Verify target temperature range
  int max_iron_temp = iron_get_max_temperature();
  settings.standby_temperature = tTmp > max_iron_temp? max_iron_temp : (tTmp < 0? 0 : tTmp);
}

boolean get_standby_mode() {
  return standby_mode;
}

void set_standby_mode(boolean standby) {
  standby_mode = standby;
}

int get_iron_temperature() {
  return iron_temperature;
}

void set_iron_temperature(int tTmp) {
  iron_temperature = tTmp;
}

int get_iron_pwm() {
  return iron_pwm;
}

void set_iron_pwm(int pwm) {
  // Verify pwm range
  iron_pwm = pwm > 255 ? 255 : (pwm < 0 ? 0 : pwm);
}


#ifdef LCD_MODULE

lcd_mode get_lcd_backlight_mode() {
  return settings.lcd_backlight_mode;
}

void set_lcd_backlight_mode(lcd_mode backlight) {
  settings.lcd_backlight_mode = backlight;
  lcd_set_backlight(settings.lcd_backlight_mode > LCD_OFF);
}

byte get_lcd_contrast() {
  return settings.lcd_contrast;
}

void set_lcd_contrast(byte contrast) {
  settings.lcd_contrast = contrast > 100 ? 100 : (contrast < 0 ? 0 : contrast);
  lcd_set_contrast(settings.lcd_contrast);
}

byte get_language() {
  return settings.language;
}

void set_language(byte lang) {
  settings.language = lang;
  lang_set_current((TranslatableLang)settings.language);
}

temperature_unit get_temperature_unit() {
  return settings.tu;
}

void set_temperature_unit(temperature_unit tu) {
  settings.tu = tu;
}

#endif //LCD_MODULE

/*
 * Load settings from the memory
 */
void load_settings() {
  DEBUG_LOG_LN("Load settings");
  
  unsigned long checksum;
  memory_load_settings(sizeof(settings) - sizeof(unsigned long), &checksum, sizeof(unsigned long));
  
  if(checksum == CHECKSUM_VALUE) {
    DEBUG_LOG_LN("Load from memory");
    memory_load_settings(0, &settings, sizeof(settings) - sizeof(unsigned long));
  } else {
    DEBUG_LOG_LN("Memory is incorrect. Using default values");
  }
  
  DEBUG_LOG_LN(my_sprintf("Target temperature: %d", settings.target_temperature));
  DEBUG_LOG_LN(my_sprintf("Standby temperature: %d", settings.standby_temperature));
#ifdef LCD_MODULE
  DEBUG_LOG_LN(my_sprintf("LCD backlight: %d", settings.lcd_backlight_mode));
  DEBUG_LOG_LN(my_sprintf("LCD Contrast: %d", settings.lcd_contrast));
  DEBUG_LOG_LN(my_sprintf("Language: %d", settings.language));
  DEBUG_LOG_LN(my_sprintf("Temperature Unit: %d", settings.tu));
#endif //LCD_MODULE
}

/*
 * Save settings to the memory
 */
void save_settings() {
  DEBUG_LOG_LN("Save settings");
  memory_save_settings(0, &settings, sizeof(settings));
}

void update_settings() {
#ifdef LCD_MODULE
  set_lcd_backlight_mode(get_lcd_backlight_mode());
  set_lcd_contrast(get_lcd_contrast());
  set_language(get_language());
#endif //LCD_MODULE
}

