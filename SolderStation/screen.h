#ifndef _SCREEN_H
#define _SCREEN_H

#if defined(ARDUINO) && ARDUINO >= 100
      #include "Arduino.h"
#else
      #include "WProgram.h"
#endif

// Define screens
#define SCREEN_MAIN 0
#define SCREEN_MENU 1
#define SCREEN_SCREEN_SETTINGS 2

extern byte current_screen;
extern byte old_screen;

/*
 * Change current screen to provided one
 */
inline void screen_change(byte new_screen) {
  old_screen = current_screen;
  current_screen = new_screen;
}

#endif //_SCREEN_H
