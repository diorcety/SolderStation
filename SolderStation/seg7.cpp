#include "config.h"
#include "seg7.h"
#include "utils.h"

#include <Arduino.h>

#ifdef SEG7_MODULE

#ifndef SEG7_A_PIN
#error Missing configuration of SEG7_A_PIN
#endif //SEG7_A_PIN
#ifndef SEG7_B_PIN
#error Missing configuration of SEG7_B_PIN
#endif //SEG7_B_PIN
#ifndef SEG7_C_PIN
#error Missing configuration of SEG7_C_PIN
#endif //SEG7_C_PIN
#ifndef SEG7_D_PIN
#error Missing configuration of SEG7_D_PIN
#endif //SEG7_D_PIN
#ifndef SEG7_E_PIN
#error Missing configuration of SEG7_E_PIN
#endif //SEG7_E_PIN
#ifndef SEG7_F_PIN
#error Missing configuration of SEG7_F_PIN
#endif //SEG7_F_PIN
#ifndef SEG7_G_PIN
#error Missing configuration of SEG7_G_PIN
#endif //SEG7_G_PIN
#ifndef SEG7_DP_PIN
#error Missing configuration of SEG7_DP_PIN
#endif //SEG7_DP_PIN
#ifndef SEG7_SEL0_PIN
#error Missing configuration of SEG7_SEL0_PIN
#endif //SEG7_SEL0_PIN
#ifndef SEG7_SEL1_PIN
#error Missing configuration of SEG7_SEL1_PIN
#endif //SEG7_SEL1_PIN
#ifndef SEG7_SEL2_PIN
#error Missing configuration of SEG7_SEL2_PIN
#endif //SEG7_SEL2_PIN

static byte SEG_PIN[8] = {
  SEG7_A_PIN, SEG7_B_PIN, SEG7_C_PIN, SEG7_D_PIN,
  SEG7_E_PIN, SEG7_F_PIN, SEG7_G_PIN, SEG7_DP_PIN
};

static byte SELS_PIN[3] = {
  SEG7_SEL0_PIN,
  SEG7_SEL1_PIN,
  SEG7_SEL2_PIN
};

/*
 * Init SEG7 stuff
 */
void seg7_init() {
  DEBUG_LOG_LN("Init SEG7");
  for(byte i = 0; i < 8; i++) {
    digitalWrite(SEG_PIN[i], LOW); 
    pinMode(SEG_PIN[i], OUTPUT);
  }
  for(byte i = 0; i < 3; i++) {
    digitalWrite(SELS_PIN[i], LOW); 
    pinMode(SELS_PIN[i], OUTPUT);
  }
}

#define _SEG_A_BIT 0
#define _SEG_B_BIT 1
#define _SEG_C_BIT 2
#define _SEG_D_BIT 3
#define _SEG_E_BIT 4
#define _SEG_F_BIT 5
#define _SEG_G_BIT 6
#define _SEG_DP_BIT 7

#define GET_OFFSET(state) _SEG_##state##_BIT

#define GET_PIN(state) SEG_##state##_PIN

#define SET_STATE(value, state) ((value & 0x1) << GET_OFFSET(state))
#define GET_STATE(value, state) ((value >> GET_OFFSET(state)) & 0x1)

static byte DIGITS[10] = {
  SET_STATE(1, A) | SET_STATE(1, B) | SET_STATE(1, C) | SET_STATE(1, D) | SET_STATE(1, E) | SET_STATE(1, F),                   // 0
  SET_STATE(1, B) | SET_STATE(1, C),                                                                                           // 1
  SET_STATE(1, A) | SET_STATE(1, B) | SET_STATE(1, D) | SET_STATE(1, E) | SET_STATE(1, G),                                     // 2
  SET_STATE(1, A) | SET_STATE(1, B) | SET_STATE(1, C) | SET_STATE(1, D) | SET_STATE(1, G),                                     // 3
  SET_STATE(1, B) | SET_STATE(1, C) | SET_STATE(1, F) | SET_STATE(1, G),                                                       // 4
  SET_STATE(1, A) | SET_STATE(1, C) | SET_STATE(1, D) | SET_STATE(1, F) | SET_STATE(1, G),                                     // 5
  SET_STATE(1, A) | SET_STATE(1, C) | SET_STATE(1, D) | SET_STATE(1, E) | SET_STATE(1, F) | SET_STATE(1, G),                   // 6
  SET_STATE(1, A) | SET_STATE(1, B) | SET_STATE(1, C),                                                                         // 7
  SET_STATE(1, A) | SET_STATE(1, B) | SET_STATE(1, C) | SET_STATE(1, D) | SET_STATE(1, E) | SET_STATE(1, F) | SET_STATE(1, G), // 8
  SET_STATE(1, A) | SET_STATE(1, B) | SET_STATE(1, C) | SET_STATE(1, D) | SET_STATE(1, F) | SET_STATE(1, G),                   // 9
};

static void print_digit(byte digit) {
  byte digit_value = DIGITS[digit];
  for(byte i = 0; i < 8; i++) {
    digitalWrite(SEG_PIN[i], digit_value & 0x1);
    digit_value = digit_value >> 1;
  }
}


static byte current_sel = 2;

static void seg7_move() {
  current_sel = (current_sel + 1) % 3;
}

/*
 * Print temperature on 7-seg
 */
void seg7_print(int temp) {
  digitalWrite(SELS_PIN[current_sel], LOW);

  seg7_move();
  
  int div = 1;
  if(current_sel == 0) {
    div = 100;
  } else if(current_sel == 1) {
    div = 10;
  } else {
    div = 1;
  }
  print_digit((temp/div)%10);
  digitalWrite(SELS_PIN[current_sel], HIGH);
}

void seg7_print_fault() {
  digitalWrite(SELS_PIN[current_sel], LOW);
  
  seg7_move();
  
  for(byte i = 0; i < 8; i++) {
    digitalWrite(SEG_PIN[i], i < 7);
  }
  digitalWrite(SELS_PIN[current_sel], HIGH);
}

void seg7_print_heat(byte pwm) {
  digitalWrite(SEG7_DP_PIN, pwm >= (64*(current_sel + 1)));
}

#endif //SEG7_MODULE
