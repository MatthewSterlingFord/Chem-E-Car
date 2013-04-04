/*
 * alphanumeric.c
 *
 *  Created on: Mar 31, 2013
 *      Author: Matthew
 */

#include "alphanumeric.h"
#include "type.h"

#define DEFINE_ALPHA_PIN(name, port, pin) \
inline void ALPHA_##name##_ON() { \
  LPC_GPIO##port ->FIOCLR |= (1 << pin); \
} \
inline void ALPHA_##name##_OFF() { \
  LPC_GPIO##port ->FIOSET |= (1 << pin); \
} \
inline void ALPHA_##name##_INIT() { \
  LPC_GPIO##port ->FIODIR |= (1 << pin); \
}

#define DEFINE_ANODE_PIN(name, port, pin) \
inline void ANODE_##name##_ON() { \
  LPC_GPIO##port ->FIOSET |= (1 << pin); \
} \
inline void ANODE_##name##_OFF() { \
  LPC_GPIO##port ->FIOCLR |= (1 << pin); \
} \
inline void ANODE_##name##_INIT() { \
  LPC_GPIO##port ->FIODIR |= (1 << pin); \
}

DEFINE_ALPHA_PIN(TOP, 2, TOP_SEG_1);
DEFINE_ALPHA_PIN(TOP_LEFT, 2, TOP_LEFT_SEG_1);
DEFINE_ALPHA_PIN(TOP_RIGHT, 2, TOP_RIGHT_SEG_1);
DEFINE_ALPHA_PIN(MIDDLE, 2, MIDDLE_SEG_1);
DEFINE_ALPHA_PIN(BOTTOM_LEFT, 2, BOTTOM_LEFT_SEG_1);
DEFINE_ALPHA_PIN(BOTTOM_RIGHT, 2, BOTTOM_RIGHT_SEG_1);
DEFINE_ALPHA_PIN(BOTTOM, 2, BOTTOM_SEG_1);
DEFINE_ALPHA_PIN(DOT, 0, DOT_SEG_1);
DEFINE_ANODE_PIN(D1, 0, ANODE_1);
DEFINE_ANODE_PIN(D2, 0, ANODE_2);
DEFINE_ANODE_PIN(D3, 0, ANODE_3);
DEFINE_ANODE_PIN(D4, 0, ANODE_4);


inline void alpha_init() {
  ALPHA_TOP_INIT();
  ALPHA_TOP_LEFT_INIT();
  ALPHA_TOP_RIGHT_INIT();
  ALPHA_MIDDLE_INIT();
  ALPHA_BOTTOM_LEFT_INIT();
  ALPHA_BOTTOM_RIGHT_INIT();
  ALPHA_BOTTOM_INIT();
  ALPHA_DOT_INIT();
  ANODE_D1_INIT();
  ANODE_D2_INIT();
  ANODE_D3_INIT();
  ANODE_D4_INIT();
}

//inline void alpha_dot_on() {
//  ALPHA_DOT_ON();
//}
//
//inline void alpha_dot_off() {
//  ALPHA_DOT_OFF();
//}

inline void alpha_display(char c, int digit, int dp) {
  // Characters generated from:
  // http://en.wikipedia.org/wiki/Seven-segment_display_character_representations
  if(dp)
	  ALPHA_DOT_ON();
  else
	  ALPHA_DOT_OFF();
  switch(digit){
  case 1:
	  ANODE_D1_ON();
	  ANODE_D2_OFF();
	  ANODE_D3_OFF();
	  ANODE_D4_OFF();
	  break;
  case 2:
	  ANODE_D1_OFF();
	  ANODE_D2_ON();
	  ANODE_D3_OFF();
	  ANODE_D4_OFF();
	  break;
  case 3:
	  ANODE_D1_OFF();
	  ANODE_D2_OFF();
	  ANODE_D3_ON();
	  ANODE_D4_OFF();
	  break;
  case 4:
	  ANODE_D1_OFF();
	  ANODE_D2_OFF();
	  ANODE_D3_OFF();
	  ANODE_D4_ON();
	  break;
  }
  switch (c) {
  case '0':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_OFF();
    break;

  case '1':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_OFF();
    ALPHA_BOTTOM_LEFT_OFF();
    ALPHA_TOP_LEFT_OFF();
    ALPHA_MIDDLE_OFF();
    break;

  case '2':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_OFF();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_OFF();
    ALPHA_MIDDLE_ON();
    break;

  case '3':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_OFF();
    ALPHA_TOP_LEFT_OFF();
    ALPHA_MIDDLE_ON();
    break;

  case '4':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_OFF();
    ALPHA_BOTTOM_LEFT_OFF();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case '5':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_OFF();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case '6':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case '7':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_OFF();
    ALPHA_BOTTOM_LEFT_OFF();
    ALPHA_TOP_LEFT_OFF();
    ALPHA_MIDDLE_OFF();
    break;

  case '8':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case '9':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_OFF();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case 'a':
  case 'A':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_OFF();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case 'b':
  case 'B':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case 'c':
  case 'C':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_OFF();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_OFF();
    break;

  case 'd':
  case 'D':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_OFF();
    ALPHA_MIDDLE_ON();
    break;

  case 'e':
  case 'E':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_OFF();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case 'f':
  case 'F':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_OFF();
    ALPHA_BOTTOM_OFF();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case 'g':
  case 'G':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_OFF();
    break;

  case 'h':
  case 'H':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_OFF();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case 'i':
  case 'I':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_OFF();
    ALPHA_BOTTOM_LEFT_OFF();
    ALPHA_TOP_LEFT_OFF();
    ALPHA_MIDDLE_OFF();
    break;

  case 'j':
  case 'J':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_OFF();
    ALPHA_MIDDLE_OFF();
    break;

  case 'k':
  case 'K':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_OFF();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case 'l':
  case 'L':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_OFF();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_OFF();
    break;

  case 'm':
  case 'M':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_OFF();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_OFF();
    ALPHA_MIDDLE_ON();
    break;

  case 'n':
  case 'N':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_OFF();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_OFF();
    ALPHA_MIDDLE_ON();
    break;

  case 'o':
  case 'O':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_OFF();
    break;

  case 'p':
  case 'P':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_OFF();
    ALPHA_BOTTOM_OFF();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case 'q':
  case 'Q':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_OFF();
    ALPHA_BOTTOM_LEFT_OFF();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case 'r':
  case 'R':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_OFF();
    ALPHA_BOTTOM_OFF();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_OFF();
    ALPHA_MIDDLE_ON();
    break;

  case 's':
  case 'S':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_OFF();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case 't':
  case 'T':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_OFF();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case 'u':
  case 'U':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_OFF();
    break;

  case 'v':
  case 'V':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_OFF();
    ALPHA_MIDDLE_OFF();
    break;

  case 'w':
  case 'W':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_OFF();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_OFF();
    ALPHA_MIDDLE_OFF();
    break;

  case 'x':
  case 'X':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_OFF();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case 'y':
  case 'Y':
    ALPHA_TOP_OFF();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_ON();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_OFF();
    ALPHA_TOP_LEFT_ON();
    ALPHA_MIDDLE_ON();
    break;

  case 'z':
  case 'Z':
    ALPHA_TOP_ON();
    ALPHA_TOP_RIGHT_ON();
    ALPHA_BOTTOM_RIGHT_OFF();
    ALPHA_BOTTOM_ON();
    ALPHA_BOTTOM_LEFT_ON();
    ALPHA_TOP_LEFT_OFF();
    ALPHA_MIDDLE_ON();
    break;
  }
}
