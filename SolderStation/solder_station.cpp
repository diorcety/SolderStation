#include "config.h"
#include "solder_station.h"
#include "iron.h"
#include "memory.h"
#include "utils.h"
#include "lcd.h"
#include "lang.h"

static int iron_temperature = 0;
static bool fault_mode = false;
static byte iron_pwm = 0;
static boolean standby_mode = false;

#define CHECKSUM_VALUE 0xDEADBEAF

struct _memory_settings {
  int target_temperature;
  int standby_temperature;
#ifdef LCD_MODULE
  lcd_mode lcd_backlight_mode;
#ifdef LCD_MODULE_CONTRAST
  byte lcd_contrast;
#endif //LCD_MODULE_CONTRAST
  byte language;
  temperature_unit tu;
#endif //LCD_MODULE
#ifdef HEAT_PROTECTION
  byte protection_pwm;
  byte protection_time;
#endif //HEAT_PROTECTION
  unsigned long checksum;
} settings = {
  300,
  150,
#ifdef LCD_MODULE
  LCD_ON,
#ifdef LCD_MODULE_CONTRAST
  30,  // default contrast
#endif //LCD_MODULE_CONTRAST
  0,
  TEMP_CELSIUS,
#endif //LCD_MODULE
#ifdef HEAT_PROTECTION
  85, // 33%
  15, // 15 seconds
#endif //HEAT_PROTECTION
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

void set_fault_mode() {
  fault_mode = true;
}

bool is_fault_mode() {
  return fault_mode;
}

#ifdef LCD_MODULE

lcd_mode get_lcd_backlight_mode() {
  return settings.lcd_backlight_mode;
}

void set_lcd_backlight_mode(lcd_mode backlight) {
  settings.lcd_backlight_mode = backlight;
  lcd_set_backlight(settings.lcd_backlight_mode > LCD_OFF);
}

#ifdef LCD_MODULE_CONTRAST
byte get_lcd_contrast() {
  return settings.lcd_contrast;
}

void set_lcd_contrast(byte contrast) {
  settings.lcd_contrast = contrast > 100 ? 100 : (contrast < 0 ? 0 : contrast);
  lcd_set_contrast(settings.lcd_contrast);
}
#endif //LCD_MODULE_CONTRAST

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

#ifdef HEAT_PROTECTION

byte get_protection_pwm() {
  return settings.protection_pwm;
}

void set_protection_pwm(byte pwm) {
  settings.protection_pwm = pwm;
}

int get_protection_time() {
  return settings.protection_time;
}

void set_protection_time(int time) {
  settings.protection_time = time;
}

#endif //HEAT_PROTECTION

/*
 * Load settings from the memory
 */
void load_settings() {
  DEBUG_LOG_LN(DEBUG_STR("Load settings"));
  
#ifdef MEMORY_SETTINGS
  unsigned long checksum;
  memory_load_settings(sizeof(settings) - sizeof(unsigned long), &checksum, sizeof(unsigned long));
  
  if(checksum == CHECKSUM_VALUE) {
    DEBUG_LOG_LN(DEBUG_STR("Load from memory"));
    memory_load_settings(0, &settings, sizeof(settings) - sizeof(unsigned long));
  } else {
    DEBUG_LOG_LN(DEBUG_STR("Memory is incorrect. Using default values"));
  }
#endif //MEMORY_SETTINGS

  DEBUG_LOG(DEBUG_STR("Target temperature: "));
  DEBUG_LOG_LN(settings.target_temperature);
  DEBUG_LOG(DEBUG_STR("Standby temperature: "));
  DEBUG_LOG_LN(settings.standby_temperature);
#ifdef LCD_MODULE
  DEBUG_LOG(DEBUG_STR("LCD backlight: "));
  DEBUG_LOG_LN(settings.lcd_backlight_mode);
#ifdef LCD_MODULE_CONTRAST
  DEBUG_LOG(DEBUG_STR("LCD Contrast: "));
  DEBUG_LOG_LN(settings.lcd_contrast);
#endif //LCD_MODULE_CONTRAST
  DEBUG_LOG(DEBUG_STR("Language: "));
  DEBUG_LOG_LN(settings.language);
  DEBUG_LOG(DEBUG_STR("Temperature Unit: "));
  DEBUG_LOG_LN(settings.tu);
#endif //LCD_MODULE
#ifdef HEAT_PROTECTION
  DEBUG_LOG(DEBUG_STR("Protection PWM: "));
  DEBUG_LOG_LN(settings.protection_pwm);
  DEBUG_LOG(DEBUG_STR("Protection Time: "));
  DEBUG_LOG_LN(settings.protection_time);
#endif //HEAT_PROTECTION
}

/*
 * Save settings to the memory
 */
void save_settings() {
  DEBUG_LOG_LN(DEBUG_STR("Save settings"));
#ifdef MEMORY_SETTINGS
  memory_save_settings(0, &settings, sizeof(settings));
#endif //MEMORY_SETTINGS
}

void update_settings() {
#ifdef LCD_MODULE
  set_lcd_backlight_mode(get_lcd_backlight_mode());
#ifdef LCD_MODULE_CONTRAST
  set_lcd_contrast(get_lcd_contrast());
#endif //LCD_MODULE_CONTRAST
  set_language(get_language());
#endif //LCD_MODULE
}

