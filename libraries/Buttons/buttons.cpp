/*
 *  buttons.cpp
 *  One-shot and hold functions for buttons.
 *  Created by Franky on 29/01/09.
 *  Licensed under LGPL (free to modify and use as you wish)
 */



#if defined(ARDUINO) && ARDUINO >= 100
      #include "Arduino.h"
#else
      #include "WProgram.h"
#endif

#include "buttons.h"


Button::Button() { 
	init(OneShot, false);
}

Button::Button(bool inverted) { 
	init(OneShot, inverted);
}

Button::Button(Mode mode_v) {
	init(mode_v, false);
}

Button::Button(Mode mode_v, bool inverted) {
	init(mode_v, inverted);
}

void Button::init(Mode mode_v, bool inverted) {
	mode = mode_v;
	inverted = inverted;
    reset();
	pin = 0;
	hold_level = 1000; // 1 second
	hold_refresh = 100; // 100 ms
}

void Button::reset() {
	previous = false;
	hold_timer = millis();
	refresh_timer = millis();
	ack = false;
}

void Button::assign(byte pin_v) { 
	pin = pin_v; 
	pinMode(pin, INPUT);
}
void Button::turnOnPullUp() { if (pin) pinMode(pin, INPUT_PULLUP); }
void Button::turnOffPullUp() { if (pin) pinMode(pin, INPUT); }

// Setters
void Button::setMode(Mode mode_v) { mode = mode_v; }
void Button::setInverted(bool inverted_v) { inverted = inverted_v; }
void Button::setTimer(unsigned int t) { if (mode > Memory) hold_level = (unsigned long)t; }
void Button::setRefresh(unsigned int r) { hold_refresh = r; }

Button::State Button::check(Mode mode_v) {
	Mode mem = mode;
	mode = mode_v;
	State res = check();
	mode = mem;
	return res;
}

unsigned int Button::getHoldTime() {
	if(mode != Timer && mode != OneShotTimer && mode != MemoryTimer) {
		return 0;
	}
	if(!previous) {
		return 0;
	}
	return millis() - hold_timer;
}

void Button::acknowledge() {
	if(previous) {
		ack = true;
	}
}

Button::State Button::check() {
	unsigned long time_ms = millis();
	int val = (inverted & 0x1) ^ digitalRead(pin);
	if (val) {
		if(ack) {
			return OFF;
		}
		switch (mode) {
			case OneShot:
				if (previous) {
					return OFF;
				}
				else {
					previous = true;
					return ON;
				}
				break;
			case Memory:
				if (previous) {
					return ON;
				}
				else {
					previous = true;
					return PRESSED;
				}
				break;
			case Timer:
				if (previous) {
					// Is treshold reached?
					if (time_ms > hold_timer+hold_level) {
						if (time_ms > refresh_timer+hold_refresh) {
							refresh_timer = time_ms;
							return HOLD;
						}
						else return OFF;
					}
					else {
						return ON;
					}
				}
				else {
					previous = true;
					hold_timer = time_ms;
					refresh_timer = time_ms;
					return ON;
				}
				break;
			case OneShotTimer:
				if (previous) {
					// Is treshold reached?
					if (time_ms > hold_timer+hold_level) {
						if (time_ms > refresh_timer+hold_refresh) {
							refresh_timer = time_ms;
							return HOLD;
						}
						else return OFF;
					}
					else {
						return OFF;
					}
				}
				else {
					previous = true;
					hold_timer = time_ms;
					refresh_timer = time_ms;
					return ON;
				}
				break;
			case MemoryTimer:
				if (previous) {
					// Is treshold reached?
					if (time_ms > hold_timer+hold_level) {
						if (time_ms > refresh_timer+hold_refresh) {
							refresh_timer = time_ms;
							return HOLD;
						}
						else return OFF;
					}
					else {
						return ON;
					}
				}
				else {
					previous = true;
					hold_timer = time_ms;
					refresh_timer = time_ms;
					return PRESSED;
				}
				break;
			default:
				break;
		}
	}
	else {
		if (previous && (mode == Memory || mode == MemoryTimer)) {
			previous = false;
			return RELEASED;
		}
		previous = false;
		ack = false;
		hold_timer = time_ms;
		refresh_timer = time_ms;
		return OFF;
	}
	return OFF;
}

