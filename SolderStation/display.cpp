#include "solder_station.h"
#include "display.h"
#include "screen.h"
#include "lcd.h"


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

/*
 * Update display
 */
void display_update() {
  switch(current_screen) {
    default:
    case SCREEN_MAIN:
      display_main_screen();
      break;
  }
}
