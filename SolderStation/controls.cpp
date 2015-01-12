#include "controls.h"
#include "config.h"
#include "screen.h"
#include "solder_station.h"
#include <buttons.h>

Button buttons[BUTTON_MAX];
byte buttons_pin[BUTTON_MAX] = {BUTTON_UP_PIN, BUTTON_DOWN_PIN, BUTTON_SELECT_PIN, BUTTON_BACK_PIN};

/*
 * Init controls stuff
 */
void controls_init() {
  for(int i = 0; i < BUTTON_MAX; ++i) {
    buttons[i].setMode(OneShotTimer);
    buttons[i].setTimer(1500);
    buttons[i].setRefresh(200);
    buttons[i].assign(buttons_pin[i]);
  }
}


/*
 * Main screen
 */
static void controls_main_screen() {
  switch(buttons[BUTTON_UP].check()) {
    case ON:
    case HOLD:
      set_target_temperature(get_target_temperature() + 5);
    break;
  }
  switch(buttons[BUTTON_DOWN].check()) {
    case ON:
    case HOLD:
      set_target_temperature(get_target_temperature() - 5);
    break;
  }
}

/*
 * Update controls
 */
void constrols_update() {
  switch(current_screen) {
    default:
    case SCREEN_MAIN:
      controls_main_screen();
      break;
  }
}
