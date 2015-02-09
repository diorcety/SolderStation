#ifndef _DISPLAY_H
#define _DISPLAY_H

/*
 * Init display stuff
 */
void display_init();

/*
 * Update display
 */
void display_update();

typedef union _display_state_struct {
  struct main_state {
  } main;
  struct menu_state {
    byte selected_entry;
  } menu;
} display_state_struct;

extern display_state_struct display_state;

#endif //_DISPLAY_H
