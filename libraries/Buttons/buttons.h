/*
 *  buttons.h
 *  One-shot and hold functions for buttons.
 *  Created by Franky on 29/01/09.
 *  Licensed under LGPL (free to modify and use as you wish)
 */
#ifndef _BUTTONS_H
#define _BUTTONS_H

#include <inttypes.h>

#define OneShot 0
#define Memory 1
#define Timer 2
#define OneShotTimer 3
#define MemoryTimer 4

#define OFF 0
#define ON 1
#define PRESSED 2
#define HOLD 3
#define RELEASED 4

typedef uint8_t byte;


class Button {
public:
	Button();
	Button(bool inverted);
	Button(byte type);
	Button(byte type, bool inverted);

	void assign(byte pin);
	byte check();
	byte check(byte mode_v);
	void acknowledge();
	unsigned int getHoldTime();

	// Setters
	void setMode(byte type_v);
	void setInverted(bool inverted_v);
	void setTimer(unsigned int t);
	void setRefresh(unsigned int r);
	void turnOnPullUp();
	void turnOffPullUp();
	
	
private:
	void init(byte mode_v, bool inverted);
	byte pin;
	byte mode;
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