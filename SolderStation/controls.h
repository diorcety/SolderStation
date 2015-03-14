#ifndef _CONTROLS_H
#define _CONTROLS_H

#include <buttons.h>

enum Controls {
  CONTROL_UP = 0,
  CONTROL_DOWN,
#ifdef BUTTON_EXTENDED
  CONTROL_SELECT,
  CONTROL_BACK,
#endif //BUTTON_EXTENDED
#ifdef BUTTON_STANDBY
  CONTROL_STANDBY,
#endif //BUTTON_STANDBY
  CONTROL_MAX,
};

void controls_init();

class Control {
public:
  virtual ~Control() = 0;
  virtual int getValue() = 0;
  virtual void acknowledge() = 0;
};

extern Control* controls[CONTROL_MAX];

#endif //_CONTROLS_H
