#ifndef _CONTROLS_H
#define _CONTROLS_H

#include <buttons.h>

#define BUTTON_UP 0
#define BUTTON_DOWN 1
#ifdef BUTTON_EXTENDED
#define BUTTON_SELECT 2
#define BUTTON_BACK 3
#define BUTTON_MAX 4
#else //BUTTON_EXTENDED
#define BUTTON_MAX 2
#endif //BUTTON_EXTENDED

void controls_init();

extern Button buttons[BUTTON_MAX];

#define BUTTON_ACTION(b) (b&0x3)

#endif //_CONTROLS_H
