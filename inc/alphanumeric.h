/*
 * alphanumeric.h
 *
 *  Created on: Mar 31, 2013
 *      Author: Matthew
 */

#ifndef __ALPHANUMERIC_h_
#define __ALPHANUMERIC_h_

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

void alpha_init();
void alpha_display(char c, int digit, int dp);
void alpha_dot_on();
void alpha_dot_off();

#endif
