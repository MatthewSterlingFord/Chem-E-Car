/*
 * gpio.c
 *
 *  Created on: Mar 30, 2013
 *      Author: Matthew
 */
#include "LPC17xx.h"
#include "type.h"
#include "timer.h"
#include "clock.h"
#include "functions.h"

void pin0_gpio_toggle (int pinNumber)
{
	//XOR s the pinNumber bit
	LPC_GPIO0 -> FIOPIN ^= (1<<pinNumber);
}

//0 is 0utput and 1 is 1nput
void pin0_gpio_init (int input, int pinNumber)
{
	switch (input){
	case 0:
		LPC_GPIO0 -> FIODIR  |= 1 << pinNumber;
		LPC_GPIO0 -> FIOPIN  |= 1 << pinNumber;
	break;
	case 1:
		LPC_GPIO0 -> FIODIR  &= ~(1<<pinNumber);
	break;
	}
}

// Function to turn pin10 on
void pin0_gpio_set (int pinNumber, int setValue)
{
	switch (setValue){
	case 0:
		LPC_GPIO0 -> FIOPIN &= ~(1<<pinNumber);
	case 1:
		LPC_GPIO0 -> FIOPIN |= (1<<pinNumber);
	}
}

// Function to turn pin10 off
void pin0_10_off (void)
{

}
