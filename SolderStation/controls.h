#ifndef _CONTROLS_H
#define _CONTROLS_H

#include <buttons.h>

#define BUTTON_UP 0
#define BUTTON_DOWN 1
#define BUTTON_SELECT 2
#define BUTTON_BACK 3
#define BUTTON_MAX 4

void controls_init();

extern Button buttons[BUTTON_MAX];

#endif //_CONTROLS_H
