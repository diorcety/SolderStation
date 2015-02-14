#include "config.h"
#include "solder_station.h"
#include "iron.h"
#include "memory.h"
#include "utils.h"
#include "lcd.h"
#include "lang.h"

int iron_temperature = 0;
byte iron_pwm = 0;
boolean standby_mode = false;

struct _memory_settings {
  int target_temperature;
  lcd_mode lcd_backlight_mode;
  byte lcd_contrast;
  int standby_temperature;
  byte language;
  temperature_unit tu;
} settings = {
  0,
  LCD_ON,
  20,
  150,
  0,
  TEMP_CELSIUS,
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

/*
 * Load settings from the memory
 */
void load_settings() {
#ifdef DEBUG
  Serial.println("Load settings");
#endif //DEBUG
  memory_load_settings(0, &settings, sizeof(settings));
#ifdef DEBUG
  Serial.println(my_sprintf("Target temperature: %d", settings.target_temperature));
  Serial.println(my_sprintf("Standby temperature: %d", settings.standby_temperature));
  Serial.println(my_sprintf("LCD backlight: %d", settings.lcd_backlight_mode));
  Serial.println(my_sprintf("LCD Contrast: %d", settings.lcd_contrast));
  Serial.println(my_sprintf("Language: %d", settings.language));
  Serial.println(my_sprintf("Temperature Unit: %d", settings.tu));
#endif //DEBUG

  // Force to update
  set_lcd_backlight_mode(get_lcd_backlight_mode());
  set_lcd_contrast(get_lcd_contrast());
  set_language(get_language());
}

/*
 * Save settings to the memory
 */
void save_settings() {
#ifdef DEBUG
  Serial.println("Save settings");
#endif //DEBUG
  memory_save_settings(0, &settings, sizeof(settings));
}

void update_settings() {
}

