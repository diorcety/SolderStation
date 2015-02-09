#include "controls.h"
#include "config.h"
#include "screen.h"
#include "solder_station.h"
#include <buttons.h>

#undef PIN
#undef PULL
#undef INVERTED

#define PIN_BIT 0
#define PIN_MASK 0xf

#define PULL_BIT 4
#define PULL_MASK 0x1

#define INVERTED_BIT 5
#define INVERTED_MASK 0x1

#define GET_OFFSET(state) state##_BIT
#define GET_MASK(state) state##_MASK

#define SET_STATE(value, state) ((value & GET_MASK(state)) << GET_OFFSET(state))
#define GET_STATE(value, state) ((value >> GET_OFFSET(state)) & GET_MASK(state))

Button buttons[BUTTON_MAX];
byte buttons_state[BUTTON_MAX] = {
  SET_STATE(BUTTON_UP_PIN, PIN) | SET_STATE(BUTTON_UP_PULL, PULL) | SET_STATE(BUTTON_UP_INVERTED, INVERTED), 
  SET_STATE(BUTTON_DOWN_PIN, PIN) | SET_STATE(BUTTON_DOWN_PULL, PULL) | SET_STATE(BUTTON_DOWN_INVERTED, INVERTED), 
  SET_STATE(BUTTON_SELECT_PIN, PIN) | SET_STATE(BUTTON_SELECT_PULL, PULL) | SET_STATE(BUTTON_SELECT_INVERTED, INVERTED), 
  SET_STATE(BUTTON_BACK_PIN, PIN) | SET_STATE(BUTTON_BACK_PULL, PULL) | SET_STATE(BUTTON_BACK_INVERTED, INVERTED),
};

/*
 * Init controls stuff
 */
void controls_init() {
  for(int i = 0; i < BUTTON_MAX; ++i) {
    buttons[i].setMode(OneShotTimer);
    buttons[i].setTimer(750);
    buttons[i].setRefresh(150);
    buttons[i].assign(GET_STATE(buttons_state[i], PIN));
    if(GET_STATE(buttons_state[i], PULL)) {
      buttons[i].turnOnPullUp();
    } else {
      buttons[i].turnOffPullUp();
    }
    buttons[i].setInverted(GET_STATE(buttons_state[i], INVERTED));
  }
}


/*
 * Main screen
 */
static void controls_main_screen() {
  switch(buttons[BUTTON_SELECT].check()) {
    case ON:
      screen_change(SCREEN_MENU);
    break;
  }
  
  switch(buttons[BUTTON_UP].check()) {
    case ON:
    case HOLD:
      Serial.println("Increase target temp.");
      set_target_temperature(get_target_temperature() + 5);
    break;
  }
  switch(buttons[BUTTON_DOWN].check()) {
    case ON:
    case HOLD:
      Serial.println("Decrease target temp.");
      set_target_temperature(get_target_temperature() - 5);
    break;
  }
}

/*
 * Menu screen
 */
static void controls_menu_screen() {
  switch(buttons[BUTTON_BACK].check()) {
    case ON:
      screen_change(SCREEN_MAIN);
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
    case SCREEN_MENU:
      controls_menu_screen();
      break;
  }
}
