#include "config.h"
#include "solder_station.h"
#include "display.h"
#include "controls.h"
#include "lcd.h"
#include "led.h"
#include "seg7.h"
#include "utils.h"
#include "lang.h"

class View {
public:
  virtual ~View() = 0;
  virtual void update() = 0;
  virtual void draw() = 0;
};


View::~View() {
}

static boolean do_redraw = true;
static void redraw() {
  do_redraw = true;
}

static View *view = NULL;

typedef enum {
  SCREEN_NONE = 0,
  SCREEN_MAIN,
#ifdef MENU_MODULE
  SCREEN_MENU_MAIN,
  SCREEN_MENU_IRON,
  SCREEN_MENU_LCD,
  SCREEN_MENU_LOCALE,
#endif //MENU_MODULE
  SCREEN_MAX
} Screen;

static Screen displayed_screen = SCREEN_NONE;
static Screen current_screen = SCREEN_NONE;
static void change_screen(Screen screen);

#ifdef MENU_MODULE

typedef struct _item_entry {
  TranslatableText text;
  const char* (*get_fct)(void);
  boolean (*set_fct)(int);
} item_entry;


/*
 * Generic menu display function
 */
 
template<typename T>
static T rooling(T value, T min_value, T max_value, int inc_value) {
  int diff = max_value - min_value;
  bool sub = inc_value < 0;
  if(sub) {
    inc_value = -inc_value;
  }
  inc_value = inc_value % diff;
  if(sub) {
    inc_value = -inc_value;
  }
  
  value -= min_value;
  inc_value = inc_value + value + diff;
  value = inc_value % diff + min_value;
  return value;
}
 
static boolean edit_menu(item_entry *item, byte count, byte selected, int inc_value) {
  if(item != NULL && selected < count) {
    if(item[selected].set_fct != NULL) {
      return item[selected].set_fct(inc_value);
    }
  }
  return false;
}

static void display_menu(item_entry *item, byte count, byte selected, boolean edit) {
  char buffer[128];
  for(byte i = 0; i < 4; ++i) {
    const char *entry = NULL;
    const char *value = NULL;
    if(item != NULL && i < count) {
      strcpy(buffer, GET_TEXT(item->text));
      entry = buffer;
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
private:
  unsigned long last_edit_time;
  
public:
  MainScreen() {
    last_edit_time = 0;
  }

  virtual ~MainScreen() {
  }
  
  virtual void update() {
    int up = controls[CONTROL_UP]->getValue();
    int down = controls[CONTROL_DOWN]->getValue();
#ifdef MENU_MODULE
    int select = controls[CONTROL_SELECT]->getValue();
    if(select) {
      change_screen(SCREEN_MENU_MAIN);
      return;
    }
#endif //MENU_MODULE
#ifdef BEHAVIOUR_COMBO_STANDBY
    if(up && down) {
      set_standby_mode(!get_standby_mode());
      controls[CONTROL_UP]->acknowledge();
      controls[CONTROL_DOWN]->acknowledge();
      redraw();
      return;
    }
#endif //BEHAVIOUR_COMBO_STANDBY
              
    if(up) {
      if(!get_standby_mode()) {
        set_target_temperature(get_target_temperature() + TEMP_STEP * up);
        last_edit_time = millis() + DELAY_EDIT_TIME;
      } else {
#ifdef STANDBY_LIVE_EDIT
        set_standby_temperature(get_standby_temperature() + TEMP_STEP * up);
        last_edit_time = millis() + DELAY_EDIT_TIME;
#endif //STANDBY_LIVE_EDIT
      }
      redraw();
      return;
    }
    if(down) {
      if(!get_standby_mode()) {
        set_target_temperature(get_target_temperature() - TEMP_STEP * down);
        last_edit_time = millis() + DELAY_EDIT_TIME; 
      } else {
#ifdef BEHAVIOUR_STANDBY_LIVE_EDIT
        set_standby_temperature(get_standby_temperature() - TEMP_STEP * down);
        last_edit_time = millis() + DELAY_EDIT_TIME;
#endif //BEHAVIOUR_STANDBY_LIVE_EDIT
      }
      redraw();
      return;
    }
    redraw();
  }
  
  virtual void draw() {
    if(is_fault_mode()) {
#ifdef SEG7_MODULE
      seg7_print_fault();
#endif //SEG7_MODULE
#ifdef LCD_MODULE
      lcd_print_fault();
#endif //LCD_MODULE
      return;
    }
    if(!get_standby_mode()) {
#ifdef LCD_MODULE
      lcd_print_target_temperature(get_target_temperature());
#endif //LCD_MODULE
#ifdef SEG7_MODULE
      if(last_edit_time < millis()) {
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
      if(last_edit_time < millis()) {
        seg7_print(get_iron_temperature());
      } else {
        seg7_print(get_standby_temperature());
      }
#endif //SEG7_MODULE
    }
#ifdef SEG7_MODULE
#ifdef SEG7_PWM_DOT
    seg7_print_heat(get_iron_pwm());
#endif //SEG7_PWM_DOT
#endif //SEG7_MODULE
#ifdef LCD_MODULE
    lcd_print_iron_temperature(get_iron_temperature());
#ifdef LCD_SHOW_HEAT
    lcd_print_heat(get_iron_pwm());
#endif //LCD_SHOW_HEAT
    lcd_print_temperature_unit();
#endif //LCD_MODULE
  }
};

#ifdef MENU_MODULE
/*
 * Main menu screen
 */
class MainMenuScreen: public View {
private:
  byte selected_item;
  boolean edit;
  typedef enum {
    IRON = 0,
    LCD,
    LOCALE,
    MAX
  } Item;
  static item_entry menu_items[MAX];
  
public:
  MainMenuScreen() {
    selected_item = 0;
    edit = false;
  }

  virtual ~MainMenuScreen() {
  }
  
  virtual void update() {
    int select = controls[CONTROL_SELECT]->getValue();
    int back = controls[CONTROL_BACK]->getValue();
    int up = controls[CONTROL_UP]->getValue();
    int down = controls[CONTROL_DOWN]->getValue();
    if(back) {
      change_screen(SCREEN_MAIN);
      return;
    }
    if(select) {
      switch(selected_item) {
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
      selected_item = rooling(selected_item, (byte)0, (byte)(MAX), up);
      redraw();
      return;
    }
    if(down) {
      selected_item = rooling(selected_item, (byte)0, (byte)(MAX), -down);
      redraw();
      return;
    }
  }
  
  virtual void draw() {
    lcd_print_title(GET_TEXT(TT(MENU_MAIN_TITLE)));
    display_menu(menu_items, MAX, selected_item, edit);
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
  byte selected_item;
  boolean edit;
  TranslatableText tt;
  Screen parent_screen;
  item_entry *menu_items;
  byte items_count;
  
public:
  AbstractEditMenuScreen(TranslatableText tt, Screen parent_screen, item_entry *menu_items, byte items_count): tt(tt), parent_screen(parent_screen), menu_items(menu_items), items_count(items_count) {
    selected_item = 0;
    edit = false;
  }
  
  virtual ~AbstractEditMenuScreen() {
  }
  
  virtual void update() {
    int select = controls[CONTROL_SELECT]->getValue();
    int back = controls[CONTROL_BACK]->getValue();
    int up = controls[CONTROL_UP]->getValue();
    int down = controls[CONTROL_DOWN]->getValue();
    if(back) {
      if(edit) {
        edit = false;
        redraw();
      } else {
        change_screen(parent_screen);
      }
      return;
    }
    if(select) {
      edit = true;
      redraw();
      return;
    }
    if(up) {
      if(!edit) {
        selected_item = rooling(selected_item, (byte)0, (byte)(items_count), up);
        redraw();
      } else {
        if(edit_menu(menu_items, items_count, selected_item, up)) {
          redraw();
        }
      }
      return;
    }
    if(down) {
      if(!edit) {
        selected_item = rooling(selected_item, (byte)0, (byte)(items_count), -down);
        redraw();
      } else {
        if(edit_menu(menu_items, items_count, selected_item, -down)) {
          redraw();
        }
      }
    }
  }
  
  virtual void draw() {
    lcd_print_title(GET_TEXT(tt));
    display_menu(menu_items, items_count, selected_item, edit);
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
  
  static boolean set_contrast(int inc) {
    set_lcd_contrast(get_lcd_contrast() + 2*inc);
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
  
  static boolean set_backlight_mode(int inc) {
    set_lcd_backlight_mode((lcd_mode)rooling((byte)get_lcd_backlight_mode(), (byte)0, (byte)LCD_MAX, inc));
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
#ifdef HEAT_PROTECTION
    PROTECTION_PWM,
    PROTECTION_TIME,
#endif //HEAT_PROTECTION
    MAX
  } Item;
  static item_entry menu_items[MAX];
  
  static const char* get_target_temperature() {
    return my_sprintf("%d", ::get_target_temperature());
  }
  
  static boolean set_target_temperature(int inc) {
    ::set_target_temperature(::get_target_temperature() + TEMP_STEP*inc);
    return true;
  }
  
  static const char* get_standby_temperature() {
    return my_sprintf("%d", ::get_standby_temperature());
  }
  
  static boolean set_standby_temperature(int inc) {
    ::set_standby_temperature(::get_standby_temperature() + TEMP_STEP*inc);
    return true;
  }
  
  static const char* get_protection_pwm() {
    return my_sprintf("%d", (byte)((float)::get_protection_pwm() / 255.0f * 100.0f));
  }
  
  static boolean set_protection_pwm(int inc) {
    byte percent = (byte)((float)::get_protection_pwm() / 255.0f * 100.0f);
    percent += inc;
    ::set_protection_pwm((byte)((float)percent / 100.0f * 255.0f));
    return true;
  }
  
  static const char* get_protection_time() {
    return my_sprintf("%d", ::get_protection_time());
  }
  
  static boolean set_protection_time(int inc) {
    ::set_protection_time(::get_protection_time() + (1 * inc));
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
#ifdef HEAT_PROTECTION
  {TT(MENU_IRON_PROTECTION_PWM), get_protection_pwm, set_protection_pwm},
  {TT(MENU_IRON_PROTECTION_TIME), get_protection_time, set_protection_time},
#endif //HEAT_PROTECTION
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
  
  static boolean set_lang(int inc) {
    set_language(rooling(get_language(), (byte)0, (byte)(TL(MAX)), inc));
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
  
  static boolean set_temperature_unit(int inc) {
    ::set_temperature_unit((temperature_unit)rooling((byte)::get_temperature_unit(), (byte)0, (byte)TEMP_MAX, inc));
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

static void change_screen(Screen screen) {
  current_screen = screen;
  for(int i = 0; i < CONTROL_MAX; ++i) {
    controls[i]->acknowledge();
  }
}

// Placement new
inline void *operator new(size_t, void *buf) { return buf; }

static void change_view() {
  static union {
#ifdef MENU_MODULE
    byte mainMsData[sizeof(MainMenuScreen)];
    byte lcdMsData[sizeof(LCDMenuScreen)];
    byte IronMsData[sizeof(IronMenuScreen)];
    byte LocaleMsData[sizeof(LocaleMenuScreen)];
#endif //MENU_MODULE
    byte msData[sizeof(MainScreen)];
  } view_memory;
  
  if(view != NULL) {
    view->~View();
  }
  view = NULL;
  switch(current_screen) {
#ifdef MENU_MODULE
    case SCREEN_MENU_MAIN:
      view = new(&view_memory) MainMenuScreen();
    break;
    case SCREEN_MENU_LCD:
      view = new(&view_memory) LCDMenuScreen();
    break;
    case SCREEN_MENU_IRON:
      view = new(&view_memory) IronMenuScreen();
    break;
    case SCREEN_MENU_LOCALE:
      view = new(&view_memory) LocaleMenuScreen();
    break;
#endif //MENU_MODULE
    case SCREEN_MAIN:
      view = new(&view_memory) MainScreen();
    break;
  }
}

/*
 * Init display stuff
 */
void display_init() {
  DEBUG_LOG_LN("Init Display");
  change_screen(SCREEN_MAIN);
}

/*
 * Update display
 */
void display_update() {
  // Change screen?
  if(current_screen != displayed_screen) {
#ifdef LCD_MODULE
    lcd_clear();
#endif //LCD_MODULE
    do_redraw = true;
    
    change_view();
    
    displayed_screen = current_screen;
  }
  
  if(view != NULL) {
    // Update screen
    view->update();
    if(do_redraw) {
      //DEBUG_LOG_LN("Draw!");
      view->draw();
#ifdef LCD_MODULE
      lcd_display();
#endif //LCD_MODULE
      do_redraw = false;
    }
  }
  
  // Global HMI stuff
#ifdef LED_MODULE
  led_show_heat(get_iron_pwm() > 0);
#endif //LED_MODULE
#ifdef BUTTON_STANDBY
  set_standby_mode(controls[CONTROL_STANDBY]->getValue() > 0);
#endif //BUTTON_STANDBY
}
