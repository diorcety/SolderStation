#include "config.h"
#include "solder_station.h"
#include "iron.h"
#include "memory.h"
#include "utils.h"
#include "lcd.h"

int iron_temperature = 0;
byte iron_pwm = 0;

struct _memory_settings {
  int target_temperature;
  lcd_mode lcd_backlight_mode;
  byte lcd_contrast;
} settings = {
  0,
  LCD_ON,
  20
};

int get_target_temperature() {
  return settings.target_temperature;
}

void set_target_temperature(int tTmp) {
  // Verify target temperature range
  int max_iron_temp = iron_get_max_temperature();
  settings.target_temperature = tTmp > max_iron_temp? max_iron_temp : (tTmp < 0? 0 : tTmp);
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

/*
 * Load settings from the memory
 */
void load_settings() {
#ifdef DEBUG
  Serial.println(MY_STR("Load settings"));
#endif //DEBUG
  memory_load_settings(0, &settings, sizeof(settings));
#ifdef DEBUG
  Serial.println(my_sprintf(MY_STR("Target temperature: %d"), settings.target_temperature));
  Serial.println(my_sprintf(MY_STR("LCD backlight: %d"), settings.lcd_backlight_mode));
  Serial.println(my_sprintf(MY_STR("LCD Contrast: %d"), settings.lcd_contrast));
#endif //DEBUG

  // Force to update
  set_lcd_backlight_mode(get_lcd_backlight_mode());
  set_lcd_contrast(get_lcd_contrast());
}

/*
 * Save settings to the memory
 */
void save_settings() {
#ifdef DEBUG
  Serial.println(MY_STR("Save settings"));
#endif //DEBUG
  memory_save_settings(0, &settings, sizeof(settings));
}

void update_settings() {
}

