#include "config.h"

#include "lang.h"
#include "lcd.h"
#include <Arduino.h>
#include <avr/pgmspace.h>

#ifdef LCD_MODULE

static const char EN_LANG[] PROGMEM = "En";
static const char EN_T_ON[] PROGMEM = "On";
static const char EN_T_OFF[] PROGMEM = "Off";
static const char EN_MENU_MAIN_TITLE[] PROGMEM = "Main menu";
static const char EN_MENU_LCD[] PROGMEM = "LCD";
static const char EN_MENU_IRON[] PROGMEM = "Iron";
static const char EN_MENU_LOCALE[] PROGMEM = "Localization";
static const char EN_MENU_LCD_TITLE[] PROGMEM = "LCD Menu";
#ifdef LCD_MODULE_CONTRAST
static const char EN_MENU_LCD_CONTRAST[] PROGMEM = "Contrast";
#endif //LCD_MODULE_CONTRAST
static const char EN_MENU_LCD_BACKLIGHT[] PROGMEM = "Backlight";
static const char EN_MENU_IRON_TITLE[] PROGMEM = "Iron";
static const char EN_MENU_IRON_TARGET_TEMPERATURE[] PROGMEM = "Target T"DEGREE_SYM;
static const char EN_MENU_IRON_STANDBY_TEMPERATURE[] PROGMEM = "Standby T"DEGREE_SYM;
#ifdef HEAT_PROTECTION
static const char EN_MENU_IRON_PROTECTION_PWM[] PROGMEM = "Prot. limit";
static const char EN_MENU_IRON_PROTECTION_TIME[] PROGMEM = "Prot. time";
#endif
static const char EN_MENU_LOCALE_TITLE[] PROGMEM = "Localization";
static const char EN_MENU_LOCALE_LANG[] PROGMEM = "Language";
static const char EN_MENU_LOCALE_TEMPERATURE_UNIT[] PROGMEM = "T"DEGREE_SYM" unit";
static const char EN_T_FAULT[] PROGMEM = "Fault";
static const char * const en_translation[] PROGMEM = {
  EN_LANG,
  EN_T_ON,
  EN_T_OFF,
  EN_MENU_MAIN_TITLE,
  EN_MENU_LCD,
  EN_MENU_IRON,
  EN_MENU_LOCALE,
  EN_MENU_LCD_TITLE,
#ifdef LCD_MODULE_CONTRAST
  EN_MENU_LCD_CONTRAST,
#endif //LCD_MODULE_CONTRAST
  EN_MENU_LCD_BACKLIGHT,
  EN_MENU_IRON_TITLE,
  EN_MENU_IRON_TARGET_TEMPERATURE,
  EN_MENU_IRON_STANDBY_TEMPERATURE,
#ifdef HEAT_PROTECTION
  EN_MENU_IRON_PROTECTION_PWM,
  EN_MENU_IRON_PROTECTION_TIME,
#endif
  EN_MENU_LOCALE_TITLE,
  EN_MENU_LOCALE_LANG,
  EN_MENU_LOCALE_TEMPERATURE_UNIT,
  EN_T_FAULT,
};

static const char FR_LANG[] PROGMEM = "Fr";
static const char FR_T_ON[] PROGMEM = "On";
static const char FR_T_OFF[] PROGMEM = "Off";
static const char FR_MENU_MAIN_TITLE[] PROGMEM = "Menu principal";
static const char FR_MENU_LCD[] PROGMEM = "LCD";
static const char FR_MENU_IRON[] PROGMEM = "Fer";
static const char FR_MENU_LOCALE[] PROGMEM = "Localisation";
static const char FR_MENU_LCD_TITLE[] PROGMEM = "LCD";
#ifdef LCD_MODULE_CONTRAST
static const char FR_MENU_LCD_CONTRAST[] PROGMEM = "Contrast";
#endif //LCD_MODULE_CONTRAST
static const char FR_MENU_LCD_BACKLIGHT[] PROGMEM = "Eclairage";
static const char FR_MENU_IRON_TITLE[] PROGMEM = "Fer";
static const char FR_MENU_IRON_TARGET_TEMPERATURE[] PROGMEM = "T"DEGREE_SYM" consig.";
static const char FR_MENU_IRON_STANDBY_TEMPERATURE[] PROGMEM = "T"DEGREE_SYM" repos";
#ifdef HEAT_PROTECTION
static const char FR_MENU_IRON_PROTECTION_PWM[] PROGMEM = "Prot. limite";
static const char FR_MENU_IRON_PROTECTION_TIME[] PROGMEM = "Prot. temps";
#endif
static const char FR_MENU_LOCALE_TITLE[] PROGMEM = "Localisation";
static const char FR_MENU_LOCALE_LANG[] PROGMEM = "Langage";
static const char FR_MENU_LOCALE_TEMPERATURE_UNIT[] PROGMEM = "Unite T"DEGREE_SYM;
static const char FR_T_FAULT[] PROGMEM = "Défaut";
static const char * const fr_translation[] PROGMEM = {
  FR_LANG,
  FR_T_ON,
  FR_T_OFF,
  FR_MENU_MAIN_TITLE,
  FR_MENU_LCD,
  FR_MENU_IRON,
  FR_MENU_LOCALE,
  FR_MENU_LCD_TITLE,
#ifdef LCD_MODULE_CONTRAST
  FR_MENU_LCD_CONTRAST,
#endif //LCD_MODULE_CONTRAST
  FR_MENU_LCD_BACKLIGHT,
  FR_MENU_IRON_TITLE,
  FR_MENU_IRON_TARGET_TEMPERATURE,
  FR_MENU_IRON_STANDBY_TEMPERATURE,
#ifdef HEAT_PROTECTION
  FR_MENU_IRON_PROTECTION_PWM,
  FR_MENU_IRON_PROTECTION_TIME,
#endif
  FR_MENU_LOCALE_TITLE,
  FR_MENU_LOCALE_LANG,
  FR_MENU_LOCALE_TEMPERATURE_UNIT,
  FR_T_FAULT,
};

static const char * const* const translations[TL(MAX)] = {
  en_translation,
  fr_translation,
};

static TranslatableLang currentLang = TL(EN);

const char * lang_get_name(TranslatableLang tl) {
  return translations[tl][TT(LANG)];
}

TranslatableLang lang_get_current() {
  return currentLang;
}

void lang_set_current(TranslatableLang tl) {
  currentLang = tl;
}

const char * GET_TEXT(TranslatableText tt) {
  static char buffer[128];
  strcpy_P(buffer, (char*)pgm_read_word(&(translations[0][tt])));
  return buffer;
  //return translations[currentLang][tt];
}

#endif //LCD_MODULE
