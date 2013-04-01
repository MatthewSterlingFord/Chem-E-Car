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

//typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;
//typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;

#endif  /* __TYPE_H__ */
