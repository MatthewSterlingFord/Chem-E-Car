/*
 * functions.c
 *
 *  Created on: Mar 30, 2013
 *      Author: Matthew
 */
#include "LPC17xx.h"
#include "type.h"
#include "timer.h"
#include "clock.h"
#include "gpio.h"
#include "functions.h"

void setBit (int location, int bitOffSet, int value) {
	if(value){
		BITON(location, bitOffSet);
	} else {
		BITOFF(location, bitOffSet);
	}
}


