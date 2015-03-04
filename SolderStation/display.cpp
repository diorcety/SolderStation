#include "config.h"
#include "solder_station.h"
#include "display.h"
#include "controls.h"
#include "lcd.h"
#include "led.h"
#include "seg7.h"
#include "utils.h"
#include "lang.h"

typedef union _display_state_struct {
  struct main_state {
    unsigned long last_edit_time;
  } main;
#ifdef MENU_MODULE
  struct menu_state {
    byte selected_item;
    boolean edit;
  } menu;
#endif //MENU_MODULE
} display_state_struct;

static display_state_struct display_state;

class View {
public:
  virtual ~View() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
  virtual void enter() = 0;
  virtual void exit() = 0;
};


View::~View() {
}

static boolean do_redraw = true;
static void redraw() {
  do_redraw = true;
}

static View *displayed_screen = NULL;
static View *current_screen = NULL;

typedef enum {
  SCREEN_MAIN = 0,
#ifdef MENU_MODULE
  SCREEN_MENU_MAIN,
  SCREEN_MENU_IRON,
  SCREEN_MENU_LCD,
  SCREEN_MENU_LOCALE,
#endif //MENU_MODULE
  SCREEN_MAX
} Screen;

View *screens[SCREEN_MAX];

static void change_screen(Screen screen) {
  current_screen = screens[screen];
  buttons[BUTTON_UP].acknowledge();
  buttons[BUTTON_DOWN].acknowledge();
#ifdef BUTTON_EXTENDED
  buttons[BUTTON_SELECT].acknowledge();
  buttons[BUTTON_BACK].acknowledge();
#endif //BUTTON_EXTENDED
}

#ifdef MENU_MODULE

typedef struct _item_entry {
  TranslatableText text;
  const char* (*get_fct)(void);
  boolean (*set_fct)(boolean);
} item_entry;


/*
 * Generic menu display function
 */
 
template<typename T>
static T rooling(T value, T min_value, T max_value, boolean plus) {
  if(plus) {
    value++;
    if(value >= max_value) {
      value = min_value;
    }
  } else {
    if(value <= min_value) {
      value = max_value;
    }
    value--;
  }
  return value;
}
 
static boolean edit_menu(item_entry *item, byte count, byte selected, boolean edit) {
  if(item != NULL && selected < count) {
    if(item[selected].set_fct != NULL) {
      return item[selected].set_fct(edit);
    }
  }
  return false;
}

static void display_menu(item_entry *item, byte count, byte selected, boolean edit) {
  for(byte i = 0; i < 4; ++i) {
    const char* entry = NULL;
    const char* value = NULL;
    if(item != NULL && i < count) {
      entry = GET_TEXT(item->text);
      if(item->get_fct != NULL) {
        value = item->get_fct();
      }
      ++item;
    }
    lcd_print_item(i, entry, value, i==selected?(edit?ITEM_EDITION:ITEM_SELECTED):ITEM_NONE);
  }
}

#endif //MENU_MODULE

/*
 * Main screen
 */
class MainScreen: public View {
public:
  virtual ~MainScreen() {
  }
  
  virtual void update() {
    byte up = BUTTON_ACTION(buttons[BUTTON_UP].check());
    byte down = BUTTON_ACTION(buttons[BUTTON_DOWN].check());
#ifdef MENU_MODULE
    byte select = BUTTON_ACTION(buttons[BUTTON_SELECT].check());
    if(select) {
      change_screen(SCREEN_MENU_MAIN);
      return;
    }
#endif //MENU_MODULE
#ifdef BEHAVIOUR_COMBO_STANDBY
    if(up && down) {
      set_standby_mode(!get_standby_mode());
      buttons[BUTTON_UP].acknowledge();
      buttons[BUTTON_DOWN].acknowledge();
      redraw();
      return;
    }
#endif //BEHAVIOUR_COMBO_STANDBY
    if(up) {
      if(!get_standby_mode()) {
        set_target_temperature(get_target_temperature() + 5);
        display_state.main.last_edit_time = millis() + DELAY_EDIT_TIME;
      } else {
#ifdef STANDBY_LIVE_EDIT
        set_standby_temperature(get_standby_temperature() + 5);
        display_state.main.last_edit_time = millis() + DELAY_EDIT_TIME;
#endif //STANDBY_LIVE_EDIT
      }
      redraw();
      return;
    }
    if(down) {
      if(!get_standby_mode()) {
        set_target_temperature(get_target_temperature() - 5);
        display_state.main.last_edit_time = millis() + DELAY_EDIT_TIME; 
      } else {
#ifdef BEHAVIOUR_STANDBY_LIVE_EDIT
        set_standby_temperature(get_standby_temperature() - 5);
        display_state.main.last_edit_time = millis() + DELAY_EDIT_TIME;
#endif //BEHAVIOUR_STANDBY_LIVE_EDIT
      }
      redraw();
      return;
    }
    redraw();
  }
  
  virtual void draw() {
    if(!get_standby_mode()) {
#ifdef LCD_MODULE
      lcd_print_target_temperature(get_target_temperature());
#endif //LCD_MODULE
#ifdef SEG7_MODULE
      if(display_state.main.last_edit_time < millis()) {
        seg7_print(get_iron_temperature());
      } else {
        seg7_print(get_target_temperature());
      }
#endif //SEG7_MODULE
    } else {
#ifdef LCD_MODULE
      lcd_print_standby_temperature(get_standby_temperature());
#endif //LCD_MODULE
#ifdef SEG7_MODULE
      if(display_state.main.last_edit_time < millis()) {
        seg7_print(get_iron_temperature());
      } else {
        seg7_print(get_standby_temperature());
      }
#endif //SEG7_MODULE
    }
#ifdef LCD_MODULE
    lcd_print_iron_temperature(get_iron_temperature());
#ifdef LCD_SHOW_HEAT
    lcd_print_heat(get_iron_pwm() > 0);
#endif //LCD_SHOW_HEAT
#endif //LCD_MODULE
  }
  
  virtual void enter() {
  }
  
  virtual void exit() {
  }
};

#ifdef MENU_MODULE
/*
 * Main menu screen
 */
class MainMenuScreen: public View {
private:
  typedef enum {
    IRON = 0,
    LCD,
    LOCALE,
    MAX
  } Item;
  static item_entry menu_items[MAX];
  
public:
  virtual ~MainMenuScreen() {
  }
  
  virtual void update() {
    byte select = BUTTON_ACTION(buttons[BUTTON_SELECT].check());
    byte back = BUTTON_ACTION(buttons[BUTTON_BACK].check());
    byte up = BUTTON_ACTION(buttons[BUTTON_UP].check());
    byte down = BUTTON_ACTION(buttons[BUTTON_DOWN].check());
    if(back) {
      change_screen(SCREEN_MAIN);
      return;
    }
    if(select) {
      switch(display_state.menu.selected_item) {
        case LCD:
          change_screen(SCREEN_MENU_LCD);
          break;
        case IRON:
          change_screen(SCREEN_MENU_IRON);
          break;
        case LOCALE:
          change_screen(SCREEN_MENU_LOCALE);
          break;
        default:
        break;
      }
      return;
    }
    if(up) {
      display_state.menu.selected_item = rooling(display_state.menu.selected_item, (byte)0, (byte)(MAX), true);
      redraw();
      return;
    }
    if(down) {
      display_state.menu.selected_item = rooling(display_state.menu.selected_item, (byte)0, (byte)(MAX), false);
      redraw();
      return;
    }
  }
  
  virtual void draw() {
    lcd_print_title(GET_TEXT(TT(MENU_MAIN_TITLE)));
    display_menu(menu_items, MAX, display_state.menu.selected_item, display_state.menu.edit);
  }
  
  virtual void enter() {
    display_state.menu.selected_item = 0;
    display_state.menu.edit = false;
  }
  
  virtual void exit() {
  }
};

item_entry MainMenuScreen::menu_items[MainMenuScreen::MAX] = {
  {TT(MENU_IRON), NULL, NULL},
  {TT(MENU_LCD), NULL, NULL},
  {TT(MENU_LOCALE), NULL, NULL},
};

/*
 * Abstract edit menu screen
 */
class AbstractEditMenuScreen: public View {
private:
  TranslatableText tt;
  Screen parent_screen;
  item_entry *menu_items;
  byte items_count;
  
public:
  AbstractEditMenuScreen(TranslatableText tt, Screen parent_screen, item_entry *menu_items, byte items_count): tt(tt), parent_screen(parent_screen), menu_items(menu_items), items_count(items_count) {
  }
  virtual ~AbstractEditMenuScreen() {
  }
  
  virtual void update() {
    byte select = BUTTON_ACTION(buttons[BUTTON_SELECT].check());
    byte back = BUTTON_ACTION(buttons[BUTTON_BACK].check());
    byte up = BUTTON_ACTION(buttons[BUTTON_UP].check());
    byte down = BUTTON_ACTION(buttons[BUTTON_DOWN].check());
    if(back) {
      if(display_state.menu.edit) {
        display_state.menu.edit = false;
        redraw();
      } else {
        change_screen(parent_screen);
      }
      return;
    }
    if(select) {
      display_state.menu.edit = true;
      redraw();
      return;
    }
    if(up) {
      if(!display_state.menu.edit) {
        display_state.menu.selected_item = rooling(display_state.menu.selected_item, (byte)0, (byte)(items_count), true);
        redraw();
      } else {
        if(edit_menu(menu_items, items_count, display_state.menu.selected_item, true)) {
          redraw();
        }
      }
      return;
    }
    if(down) {
      if(!display_state.menu.edit) {
        display_state.menu.selected_item = rooling(display_state.menu.selected_item, (byte)0, (byte)(items_count), false);
        redraw();
      } else {
        if(edit_menu(menu_items, items_count, display_state.menu.selected_item, false)) {
          redraw();
        }
      }
    }
  }
  
  virtual void draw() {
    lcd_print_title(GET_TEXT(tt));
    display_menu(menu_items, items_count, display_state.menu.selected_item, display_state.menu.edit);
  }
  
  virtual void enter() {
    display_state.menu.selected_item = 0;
    display_state.menu.edit = false;
  }
  
  virtual void exit() {
  }
};

/*
 * LCD menu screen
 */
class LCDMenuScreen: public AbstractEditMenuScreen {
private:
  typedef enum {
    CONTRAST = 0,
    BLACKLIGHT,
    MAX
  } Item;
  static item_entry menu_items[MAX];
  
  static const char* get_contrast() {
    return my_sprintf("%d", get_lcd_contrast());
  }
  
  static boolean set_contrast(boolean plus) {
    set_lcd_contrast(get_lcd_contrast() + (plus? +2:-2));
    return true;
  }
  
  static const char* get_backlight_mode() {
    switch(get_lcd_backlight_mode()) {
      case LCD_ON:
        return GET_TEXT(TT(T_ON));
      case LCD_OFF:
      default:
        return GET_TEXT(TT(T_OFF));
    }
  }
  
  static boolean set_backlight_mode(boolean plus) {
    set_lcd_backlight_mode((lcd_mode)rooling((byte)get_lcd_backlight_mode(), (byte)0, (byte)LCD_MAX, plus));
    return true;
  }
  
public:
  LCDMenuScreen(): AbstractEditMenuScreen(TT(MENU_LCD_TITLE), SCREEN_MENU_MAIN, menu_items, MAX) {
  }
  virtual ~LCDMenuScreen() {
  }
};

item_entry LCDMenuScreen::menu_items[LCDMenuScreen::MAX] = {
  {TT(MENU_LCD_CONTRAST), get_contrast, set_contrast},
  {TT(MENU_LCD_BACKLIGHT), get_backlight_mode, set_backlight_mode}
};


/*
 * Iron menu screen
 */
class IronMenuScreen: public AbstractEditMenuScreen {
private:
  typedef enum {
    TARGET_TEMPERATURE = 0,
    STANDBY_TEMPERATURE,
    MAX
  } Item;
  static item_entry menu_items[MAX];
  
  static const char* get_target_temperature() {
    return my_sprintf("%d", ::get_target_temperature());
  }
  
  static boolean set_target_temperature(boolean plus) {
    ::set_target_temperature(::get_target_temperature() + (plus? +5: -5));
    return true;
  }
  
  static const char* get_standby_temperature() {
    return my_sprintf("%d", ::get_standby_temperature());
  }
  
  static boolean set_standby_temperature(boolean plus) {
    ::set_standby_temperature(::get_standby_temperature() + (plus? +5: -5));
    return true;
  }
public:
  IronMenuScreen(): AbstractEditMenuScreen(TT(MENU_IRON_TITLE), SCREEN_MENU_MAIN, menu_items, MAX) {
  }
  virtual ~IronMenuScreen() {
  }
};

item_entry IronMenuScreen::menu_items[IronMenuScreen::MAX] = {
  {TT(MENU_IRON_TARGET_TEMPERATURE), get_target_temperature, set_target_temperature},
  {TT(MENU_IRON_STANDBY_TEMPERATURE), get_standby_temperature, set_standby_temperature},
};


/*
 * Locale menu screen
 */
class LocaleMenuScreen: public AbstractEditMenuScreen {
private:
  typedef enum {
    LANG = 0,
    TEMPERATURE,
    MAX
  } Item;
  static item_entry menu_items[MAX];
  
  static const char* get_lang() {
    return lang_get_name((TranslatableLang)get_language());
  }
  
  static boolean set_lang(boolean plus) {
    set_language(rooling(get_language(), (byte)0, (byte)(TL(MAX)), plus));
    lcd_clear();
    return true;
  }
  
  static const char* get_temperature_unit() {
    switch(::get_temperature_unit()) {
      case TEMP_FAHRENHEIT:
        return DEGREE_SYM"F";
      case TEMP_CELSIUS:
      default:
        return DEGREE_SYM"C";
    }
  }
  
  static boolean set_temperature_unit(boolean plus) {
    ::set_temperature_unit((temperature_unit)rooling((byte)::get_temperature_unit(), (byte)0, (byte)TEMP_MAX, plus));
    return true;
  }
public:
  LocaleMenuScreen(): AbstractEditMenuScreen(TT(MENU_LOCALE_TITLE), SCREEN_MENU_MAIN, menu_items, MAX) {
  }
  virtual ~LocaleMenuScreen() {
  }
};

item_entry LocaleMenuScreen::menu_items[LocaleMenuScreen::MAX] = {
  {TT(MENU_LOCALE_LANG), get_lang, set_lang},
  {TT(MENU_LOCALE_TEMPERATURE_UNIT), get_temperature_unit, set_temperature_unit},
};

#endif //MENU_MODULE

/*
 * Init display stuff
 */
void display_init() {
  DEBUG_LOG_LN("Init Display");
  static MainScreen ms;
  screens[SCREEN_MAIN] = &ms;
#ifdef MENU_MODULE
  static MainMenuScreen mms;
  screens[SCREEN_MENU_MAIN] = &mms;
  static LCDMenuScreen lms;
  screens[SCREEN_MENU_LCD] = &lms;
  static IronMenuScreen ims;
  screens[SCREEN_MENU_IRON] = &ims;
  static LocaleMenuScreen localems;
  screens[SCREEN_MENU_LOCALE] = &localems;
#endif //MENU_MODULE
  current_screen = &ms;
}

/*
 * Update display
 */
void display_update() {
  // Change screen?
  if(current_screen != displayed_screen) {
    if(displayed_screen != NULL) {
      displayed_screen->exit();
    }
#ifdef LCD_MODULE
    lcd_clear();
#endif //LCD_MODULE
    memset(&display_state, '\0', sizeof(display_state));
    do_redraw = true;
    
    displayed_screen = current_screen;
    displayed_screen->enter();
  }
  
  // Update screen
  displayed_screen->update();
  if(do_redraw) {
    DEBUG_LOG_LN("Draw!");
    displayed_screen->draw();
#ifdef LCD_MODULE
    lcd_display();
#endif //LCD_MODULE
    do_redraw = false;
  }
  // Global HMI stuff
#ifdef LED_MODULE
  led_show_heat(get_iron_pwm() > 0);
#endif //LED_MODULE
}
