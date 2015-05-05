#ifndef _LANG_H
#define _LANG_H

#ifdef LCD_MODULE

#define TT_PREFIX(x) TranslatableText_##x
enum TranslatableText {
  TT_PREFIX(LANG),
  TT_PREFIX(T_ON),
  TT_PREFIX(T_OFF),
  TT_PREFIX(MENU_MAIN_TITLE),
  TT_PREFIX(MENU_LCD),
  TT_PREFIX(MENU_IRON),
  TT_PREFIX(MENU_LOCALE),
  TT_PREFIX(MENU_LCD_TITLE),
  TT_PREFIX(MENU_LCD_CONTRAST),
  TT_PREFIX(MENU_LCD_BACKLIGHT),
  TT_PREFIX(MENU_IRON_TITLE),
  TT_PREFIX(MENU_IRON_TARGET_TEMPERATURE),
  TT_PREFIX(MENU_IRON_STANDBY_TEMPERATURE),
#ifdef HEAT_PROTECTION
  TT_PREFIX(MENU_IRON_PROTECTION_PWM),
  TT_PREFIX(MENU_IRON_PROTECTION_TIME),
#endif
  TT_PREFIX(MENU_LOCALE_TITLE),
  TT_PREFIX(MENU_LOCALE_LANG),
  TT_PREFIX(MENU_LOCALE_TEMPERATURE_UNIT),
  TT_PREFIX(T_FAULT),
  TT_PREFIX(MAX)
};

#define TT(x) TT_PREFIX(x)

const char * GET_TEXT(TranslatableText tt);

#define TL_PREFIX(x) TranslatableLang_##x
enum TranslatableLang {
  TL_PREFIX(EN),
  TL_PREFIX(FR),
  TL_PREFIX(MAX)
};

const char * lang_get_name(TranslatableLang tl);
TranslatableLang lang_get_current();
void lang_set_current(TranslatableLang tl);

#define TL(x) TL_PREFIX(x)

#endif //LCD_MODULE

#endif //_LANG_H
