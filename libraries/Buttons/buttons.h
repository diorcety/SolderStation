/*
 *  buttons.h
 *  One-shot and hold functions for buttons.
 *  Created by Franky on 29/01/09.
 *  Licensed under LGPL (free to modify and use as you wish)
 */
#ifndef _BUTTONS_H
#define _BUTTONS_H

#include <inttypes.h>

typedef uint8_t byte;

class Button {
public:
	enum Mode {
		OneShot,
		Memory,
		Timer,
		OneShotTimer,
		MemoryTimer
	};
	
	enum State {
		OFF = 0,
		ON,
		PRESSED,
		HOLD,
		RELEASED
	};
public:
	Button();
	Button(bool inverted);
	Button(Mode type);
	Button(Mode type, bool inverted);

	void assign(byte pin);
	State check();
	State check(Mode mode_v);
	void acknowledge();
	void reset();
	unsigned int getHoldTime();

	// Setters
	void setMode(Mode type_v);
	void setInverted(bool inverted_v);
	void setTimer(unsigned int t);
	void setRefresh(unsigned int r);
	void turnOnPullUp();
	void turnOffPullUp();

private:
	void init(Mode mode_v, bool inverted);
	byte pin;
	Mode mode;
	bool inverted;
	unsigned long hold_timer;
	unsigned long refresh_timer;
	unsigned int hold_level;
	unsigned int hold_refresh;
	bool previous;
	bool ack;
};



/*
 
 Button modes:
 
 - OneShot: OneShot only, returns 2 values (ON/OFF)
 - Memory: Returns (Pressed/ON/Released/OFF)
 - Timer: Hold System (OFF/ON/Hold)
 - OneShotTimer: Combi OneShot & Timer (ON/Hold/OFF)
 - MemoryTimer: Combi Memory & Timer 
 (Pressed/ON/Hold/Released/OFF)
 
 */

 #endif //_BUTTONS_H