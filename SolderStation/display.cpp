#include "config.h"
#include "solder_station.h"
#include "display.h"
#include "controls.h"
#include "lcd.h"
#include "utils.h"
#include "lang.h"

typedef union _display_state_struct {
  struct main_state {
  } main;
  struct menu_state {
    byte selected_item;
    boolean edit;
  } menu;
} display_state_struct;

typedef struct _item_entry {
  TranslatableText text;
  const char* (*get_fct)(void);
  boolean (*set_fct)(boolean);
} item_entry;

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
  SCREEN_MENU_MAIN,
  SCREEN_MENU_IRON,
  SCREEN_MENU_LCD,
  SCREEN_MENU_LOCALE,
  SCREEN_MAX
} Screen;

View *screens[SCREEN_MAX];

template<typename T>
T rooling(T value, T min_value, T max_value, boolean plus) {
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

static void change_screen(Screen screen) {
  current_screen = screens[screen];
}


/*
 * Generic menu display function
 */
 
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

/*
 * Main screen
 */
class MainScreen: public View {
public:
  virtual ~MainScreen() {
  }
  
  virtual void update() {
    byte select = BUTTON_ACTION(buttons[BUTTON_SELECT].check());
    byte up = BUTTON_ACTION(buttons[BUTTON_UP].check());
    byte down = BUTTON_ACTION(buttons[BUTTON_DOWN].check());
    if(select) {
      change_screen(SCREEN_MENU_MAIN);
      return;
    }
    if(up && down) {
      set_standby_mode(!get_standby_mode());
      buttons[BUTTON_UP].acknowledge();
      buttons[BUTTON_DOWN].acknowledge();
      redraw();
      return;
    }
    if(up) {
      set_target_temperature(get_target_temperature() + 5);
      redraw();
      return;
    }
    if(down) {
      set_target_temperature(get_target_temperature() - 5);
      redraw();
      return;
    }
    redraw();
  }
  
  virtual void draw() {
    if(!get_standby_mode()) {
      lcd_print_target_temperature(get_target_temperature());
    } else {
      lcd_print_standby_temperature(get_standby_temperature());
    }
    lcd_print_iron_temperature(get_iron_temperature());
    lcd_print_heat(get_iron_pwm() > 0);
  }
  
  virtual void enter() {
  }
  
  virtual void exit() {
  }
};

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
  {TT(MENU_IRON), NULL},
  {TT(MENU_LCD), NULL},
  {TT(MENU_LOCALE), NULL},
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
    STANDBY_TEMPERATURE = 0,
    MAX
  } Item;
  static item_entry menu_items[MAX];
  
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

/*
 * Init display stuff
 */
void display_init() {
  static MainScreen ms;
  static MainMenuScreen mms;
  static LCDMenuScreen lms;
  static IronMenuScreen ims;
  static LocaleMenuScreen localems;
  screens[SCREEN_MAIN] = &ms;
  screens[SCREEN_MENU_MAIN] = &mms;
  screens[SCREEN_MENU_IRON] = &ims;
  screens[SCREEN_MENU_LCD] = &lms;
  screens[SCREEN_MENU_LOCALE] = &localems;
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
    
    lcd_clear();
    memset(&display_state, '\0', sizeof(display_state));
    do_redraw = true;
    
    displayed_screen = current_screen;
    displayed_screen->enter();
  }
  
  // Update screen
  displayed_screen->update();
  if(do_redraw) {
    #ifdef DEBUG
    Serial.println("Draw!");
    #endif //DEBUG
    displayed_screen->draw();
    lcd_display();
    do_redraw = false;
  }
}
