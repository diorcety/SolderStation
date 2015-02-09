#include "solder_station.h"
#include "display.h"
#include "screen.h"
#include "lcd.h"

display_state_struct display_state;
byte displayed_screen = 0;

/*
 * Init display stuff
 */
void display_init() {
}

/*
 * Main screen
 */
static void display_main_screen() {
  lcd_print_target_temperature(get_target_temperature());
  lcd_print_iron_temperature(get_iron_temperature());
  lcd_print_heat(get_iron_pwm() > 0);
}

static void display_menu_screen() {
  lcd_print_title("Menu");
}

/*
 * Update display
 */
void display_update() {
  if(current_screen != displayed_screen) {
    lcd_clear();
    memset(&display_state, '\0', sizeof(display_state));
  }
  switch(current_screen) {
    default:
    case SCREEN_MAIN:
      display_main_screen();
      break;
    case SCREEN_MENU:
      display_menu_screen();
      break;
  }
  displayed_screen = current_screen;
}
