/*****************************************************************************
 *   type.h:  Type definition Header file for NXP LPC17xx Family 
 *   Microprocessors
 *
 *   Copyright(C) 2009, NXP Semiconductor
 *   All rights reserved.
 *
 *   History
 *   2009.05.25  ver 1.00    Prelimnary version, first Release
 *
******************************************************************************/
#include <stdint.h>

#ifndef __TYPE_H__
#define __TYPE_H__

#ifndef NULL
#define NULL    ((void *)0)
#endif

// For displaying. 0-3 mean digits 1, 2, 3, 4
// dots is just the array for showing the decimal point or not

//#ifndef FALSE
//#define FALSE   (0)
//#endif
//
//#ifndef TRUE
//#define TRUE    (1)
//#endif

#ifndef LOW
#define LOW   (0)
#endif

#ifndef HIGH
#define HIGH    (1)
#endif

#ifndef OUTPUT
#define OUTPUT   (1)
#endif

#ifndef INPUT
#define INPUT   (0)
#endif

#ifndef LED2
#define LED2   (22)
#endif

#ifndef LED_R1
#define LED_R1   (27)
#endif

#ifndef LED_B1
#define LED_B1   (28)
#endif

#ifndef LED_G1_p2
#define LED_G1_p2   (13)
#endif

#ifndef LED_R2
#define LED_R2   (24)
#endif

#ifndef LED_B2
#define LED_B2   (25)
#endif

#ifndef LED_G2
#define LED_G2   (26)
#endif

#ifndef TOP_SEG_1
#define TOP_SEG_1  (6)
#endif

#ifndef TOP_LEFT_SEG_1
#define TOP_LEFT_SEG_1   (12)
#endif

#ifndef TOP_RIGHT_SEG_1
#define TOP_RIGHT_SEG_1   (7)
#endif

#ifndef MIDDLE_SEG_1
#define MIDDLE_SEG_1   (1)
#endif

#ifndef BOTTOM_LEFT_SEG_1
#define BOTTOM_LEFT_SEG_1   (11)
#endif

#ifndef BOTTOM_RIGHT_SEG_1
#define BOTTOM_RIGHT_SEG_1   (8)
#endif

#ifndef BOTTOM_SEG_1
#define BOTTOM_SEG_1   (10)
#endif

#ifndef DOT_SEG_1
#define DOT_SEG_1   (1)
#endif

#ifndef ANODE_1
#define ANODE_1   (16)
#endif

#ifndef ANODE_2
#define ANODE_2   (15)
#endif

#ifndef ANODE_3
#define ANODE_3   (17)
#endif

#ifndef ANODE_4
#define ANODE_4   (18)
#endif

#ifndef INDEX
#define INDEX   (24)
#endif

#ifndef PHASE_A
#define PHASE_A   (20)
#endif

#ifndef PHASE_B
#define PHASE_B   (23)
#endif

//#ifndef SEVEN_SEG_DATA_INPUT_1
//#define SEVEN_SEG_DATA_INPUT_1   (6)
//#endif
//
//#ifndef SEVEN_SEG_DATA_INPUT_1
//#define SEVEN_SEG_DATA_INPUT_1   (6)
//#endif
//
//#ifndef SEVEN_SEG_LATCH_1
//#define SEVEN_SEG_LATCH_1   (7)
//#endif
//
//#ifndef SEVEN_SEG_CLOCK_1
//#define SEVEN_SEG_CLOCK_1   (8)
//#endif
//
//#ifndef SEVEN_SEG_DATA_INPUT_2
//#define SEVEN_SEG_DATA_INPUT_2   (10)
//#endif
//
//#ifndef SEVEN_SEG_LATCH_2
//#define SEVEN_SEG_LATCH_2   (11)
//#endif
//
//#ifndef SEVEN_SEG_CLOCK_2
//#define SEVEN_SEG_CLOCK_2   (12)
//#endif
//typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
//typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

#endif  /* __TYPE_H__ */
