#include "config.h"
#include "solder_station.h"
#include "display.h"
#include "controls.h"
#include "lcd.h"
#include "utils.h"

typedef union _display_state_struct {
  struct main_state {
  } main;
  struct menu_state {
    byte selected_item;
    boolean edit;
  } menu;
} display_state_struct;

typedef struct _item_entry {
  const char *text;
  const char *(*get_fct)(void);
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
  SCREEN_MENU_LCD,
  SCREEN_MAX
} Screen;

View *screens[SCREEN_MAX];

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
    const char *entry = MY_STR("");
    const char *value = NULL;
    if(item != NULL && i < count) {
      entry = item->text;
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
    switch(buttons[BUTTON_SELECT].check()) {
      case ON:
        change_screen(SCREEN_MENU_MAIN);
      break;
    }
  
    switch(buttons[BUTTON_UP].check()) {
      case ON:
      case HOLD:
#ifdef DEBUG
        Serial.println(MY_STR("Increase target temp."));
#endif //DEBUG
        set_target_temperature(get_target_temperature() + 5);
      break;
    }
    switch(buttons[BUTTON_DOWN].check()) {
      case ON:
      case HOLD:
#ifdef DEBUG
        Serial.println(MY_STR("Decrease target temp."));
#endif //DEBUG
        set_target_temperature(get_target_temperature() - 5);
      break;
    }
    redraw();
  }
  
  virtual void draw() {
    lcd_print_target_temperature(get_target_temperature());
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
    LCD = 0,
    IRON,
    MAX
  } Item;
  static item_entry menu_items[MAX];
  
public:
  virtual ~MainMenuScreen() {
  }
  
  virtual void update() {
    switch(buttons[BUTTON_BACK].check()) {
      case ON:
        change_screen(SCREEN_MAIN);
      break;
    }
    switch(buttons[BUTTON_SELECT].check()) {
      case ON:
        switch(display_state.menu.selected_item) {
          case LCD:
                  change_screen(SCREEN_MENU_LCD);
          default:
          break;
        }
      break;
    }
    switch(buttons[BUTTON_UP].check()) {
      case ON:
      case HOLD:
          if(display_state.menu.selected_item < MAX -1) {
            display_state.menu.selected_item++;
          }
          redraw();
      break;
    }
    switch(buttons[BUTTON_DOWN].check()) {
      case ON:
      case HOLD:
          if(display_state.menu.selected_item > 0) {
            display_state.menu.selected_item--;
            redraw();
          }
      break;
    }
  }
  
  virtual void draw() {
    lcd_print_title(MY_STR("Main menu"));
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
  {MY_STR("LCD"), NULL},
  {MY_STR("Iron"), NULL}
};

/*
 * LCD menu screen
 */
class LCDMenuScreen: public View {
private:
  typedef enum {
    CONTRAST = 0,
    BLACKLIGHT,
    MAX
  } Item;
  static item_entry menu_items[MAX];
  
  static const char *get_contrast() {
    return my_sprintf(MY_STR("%d"), get_lcd_contrast());
  }
  
  static boolean set_contrast(boolean plus) {
    set_lcd_contrast(get_lcd_contrast() + (plus? + 2: -2));
    return true;
  }
  
  static const char *get_backlight_mode() {
    switch(get_lcd_backlight_mode()) {
      case LCD_ON:
        return MY_STR("On");
      case LCD_OFF:
      default:
        return MY_STR("Off");
    }
  }
  
  static boolean set_backlight_mode(boolean plus) {
    byte mode = (byte)get_lcd_backlight_mode();
    if(plus) {
      mode++;
      if(mode >= LCD_MAX) {
        mode = 0;
      }
    } else {
      if(mode <= 0) {
        mode = LCD_MAX;
      }
      mode--;
    }
    set_lcd_backlight_mode((lcd_mode)mode);
    return true;
  }
  
public:
  virtual ~LCDMenuScreen() {
  }
  
  virtual void update() {
    switch(buttons[BUTTON_BACK].check()) {
      case ON:
        if(display_state.menu.edit) {
          display_state.menu.edit = false;
          redraw();
        } else {
          change_screen(SCREEN_MENU_MAIN);
        }
      break;
    }
    switch(buttons[BUTTON_SELECT].check()) {
      case ON:
        display_state.menu.edit = true;
        redraw();
      break;
    }
    switch(buttons[BUTTON_UP].check()) {
      case ON:
      case HOLD:
          if(!display_state.menu.edit) {
            if(display_state.menu.selected_item < MAX -1) {
              display_state.menu.selected_item++;
              redraw();
            }
          } else {
            if(edit_menu(menu_items, MAX, display_state.menu.selected_item, true)) {
              redraw();
            }
          }
      break;
    }
    switch(buttons[BUTTON_DOWN].check()) {
      case ON:
      case HOLD:
          if(!display_state.menu.edit) {
            if(display_state.menu.selected_item > 0) {
              display_state.menu.selected_item--;
              redraw();
            }
          } else {
            if(edit_menu(menu_items, MAX, display_state.menu.selected_item, false)) {
              redraw();
            }
          }
      break;
    }
  }
  
  virtual void draw() {
    lcd_print_title(MY_STR("LCD menu"));
    display_menu(menu_items, MAX, display_state.menu.selected_item, display_state.menu.edit);
  }
  
  virtual void enter() {
    display_state.menu.selected_item = 0;
    display_state.menu.edit = false;
  }
  
  virtual void exit() {
  }
};

item_entry LCDMenuScreen::menu_items[LCDMenuScreen::MAX] = {
  {MY_STR("Contrast"), get_contrast, set_contrast},
  {MY_STR("Backlight"), get_backlight_mode, set_backlight_mode}
};

/*
 * Init display stuff
 */
void display_init() {
  static MainScreen ms;
  static MainMenuScreen mms;
  static LCDMenuScreen lms;
  screens[SCREEN_MAIN] = &ms;
  screens[SCREEN_MENU_MAIN] = &mms;
  screens[SCREEN_MENU_LCD] = &lms;
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
    Serial.println(MY_STR("Draw!"));
    #endif //DEBUG
    displayed_screen->draw();
    lcd_display();
    do_redraw = false;
  }
}
