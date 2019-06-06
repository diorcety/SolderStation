#include "config.h"
#include "solder_station.h"
#include "iron.h"
#include "memory.h"
#include "utils.h"
#include "lcd.h"
#include "lang.h"

#ifdef TEMP_MEAN
static float iron_temperature = 0.0f;
#else //TEMP_MEAN
static int iron_temperature = 0;
#endif //TEMP_MEAN
static bool fault_mode = false;
static byte iron_pwm = 0;
static boolean standby_mode = false;

#define CHECKSUM_VALUE 0xDEADBEAF
#define EEPROM_OFFSET 0x10

struct _memory_settings {
  int target_temperature;
  int standby_temperature;
  float iron_gain;
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
#ifdef HEAT_PROTECTION_DROP
  int protection_drop;
#endif //HEAT_PROTECTION_DROP
#endif //HEAT_PROTECTION
  unsigned long checksum;
} settings = {
  300,
  DEFAULT_STANDBY_TEMPERATURE,
  0.39f,
#ifdef LCD_MODULE
  LCD_ON,
#ifdef LCD_MODULE_CONTRAST
  30,  // default contrast
#endif //LCD_MODULE_CONTRAST
  0,
  TEMP_CELSIUS,
#endif //LCD_MODULE
#ifdef HEAT_PROTECTION
  HEAT_PROTECTION_VALUE,
  HEAT_PROTECTION_TIME,
#ifdef HEAT_PROTECTION_DROP
  HEAT_PROTECTION_DROP,
#endif //HEAT_PROTECTION_DROP
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
#ifdef TEMP_MEAN
#if TEMP_MEAN < DELAY_MAIN_LOOP*2
#error TEMP_MEAN should be greater than DELAY_MAIN_LOOP*2
#endif
#define MEAN_COUNT (((float)TEMP_MEAN)/((float)(DELAY_MAIN_LOOP*2))) // *2 because we have only one period on two is used for measurement
  float temp_iron_temperature = iron_temperature * (MEAN_COUNT - 1.0f);
  temp_iron_temperature += ((float)tTmp);
  iron_temperature = temp_iron_temperature / MEAN_COUNT;
#undef MEAN_COUNT
#else //TEMP_MEAN
  iron_temperature = tTmp;
#endif //TEMP_MEAN
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

#ifdef HEAT_PROTECTION_DROP

int get_protection_drop() {
  return settings.protection_drop;
}

void set_protection_drop(int drop) {
  settings.protection_drop = drop;
}

#endif //HEAT_PROTECTION_DROP

#endif //HEAT_PROTECTION

/*
 * Load settings from the memory
 */
void load_settings() {
  DEBUG_LOG_LN(DEBUG_STR("Load settings"));
  
#ifdef MEMORY_SETTINGS
  unsigned long checksum;
  memory_load_settings(EEPROM_OFFSET + sizeof(settings) - sizeof(unsigned long), &checksum, sizeof(unsigned long));
  
  if(checksum == CHECKSUM_VALUE) {
    DEBUG_LOG_LN(DEBUG_STR("Load from memory"));
    memory_load_settings(EEPROM_OFFSET, &settings, sizeof(settings) - sizeof(unsigned long));

    // Security about corrupted eeprom
    set_target_temperature(get_target_temperature());
    set_standby_temperature(get_standby_temperature());
    iron_set_gain(settings.iron_gain);
  } else {
    DEBUG_LOG_LN(DEBUG_STR("Memory is incorrect. Using default values"));
  }
#endif //MEMORY_SETTINGS

  DEBUG_LOG(DEBUG_STR("Target temperature: "));
  DEBUG_LOG_LN(settings.target_temperature);
  DEBUG_LOG(DEBUG_STR("Standby temperature: "));
  DEBUG_LOG_LN(settings.standby_temperature);
  DEBUG_LOG(DEBUG_STR("Iron gain: "));
  DEBUG_LOG_LN(settings.iron_gain);
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
  settings.iron_gain = iron_get_gain();
  
#ifdef MEMORY_SETTINGS
  memory_save_settings(EEPROM_OFFSET, &settings, sizeof(settings));
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

