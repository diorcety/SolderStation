#include "lang.h"
#include "lcd.h"
#include <Arduino.h>
#include <avr/pgmspace.h>

/*PROGMEM*/ static const char * en_translation[] = {
  "En",
  "On",
  "Off",
  "Main menu",
  "LCD",
  "Iron",
  "Locale",
  "LCD Menu",
  "Contrast",
  "Backlight",
  "Iron Menu",
  "Standby T"DEGREE_SYM,
  "Locale Menu",
  "Language",
  "T"DEGREE_SYM" unit",
};

/*PROGMEM*/ static const char * fr_translation[] = {
  "Fr",
  "On",
  "Off",
  "Menu principal",
  "LCD",
  "Fer",
  "Localisation",
  "Menu LCD",
  "Contrast",
  "Eclairage",
  "Menu Fer",
  "T"DEGREE_SYM" repos",
  "Menu local.",
  "Langage",
  "Unite T"DEGREE_SYM"",
};

static const char ** translations[TL(MAX)] = {
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
  /*
  static char buffer[128];
  strcpy_P(buffer, (char*)pgm_read_word(&(translations[0][tt])));
  return buffer;
  */
  return translations[currentLang][tt];
}
