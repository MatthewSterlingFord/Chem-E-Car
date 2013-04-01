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

//1 is output and 0 is input
void pin0_gpio_init (int output, int pinNumber)
{
	switch (output){
	case 1:
		LPC_GPIO0 -> FIODIR  |= 1 << pinNumber;
		LPC_GPIO0 -> FIOPIN  |= 1 << pinNumber;
	break;
	case 0:
		LPC_GPIO0 -> FIODIR  &= ~(1<<pinNumber);
	break;
	}
}

// Function to turn pin to setToValue
void pin0_gpio_set (int pinNumber, int setToValue)
{
	switch (setToValue){
	case 0:
		LPC_GPIO0 -> FIOPIN &= ~(1<<pinNumber);
	break;
	case 1:
		LPC_GPIO0 -> FIOPIN |= (1<<pinNumber);
	break;
	}
}

void pin0_gpio_toggle (int pinNumber){
	//XOR s the pinNumber bit
	LPC_GPIO0 -> FIOPIN ^= (1<<pinNumber);
}

//0 is 0utput and 1 is 1nput
void pin2_gpio_init (int output, int pinNumber)
{
	switch (output){
	case 1:
		LPC_GPIO2 -> FIODIR  |= 1 << pinNumber;
		LPC_GPIO2 -> FIOPIN  |= 1 << pinNumber;
	break;
	case 0:
		LPC_GPIO2 -> FIODIR  &= ~(1<<pinNumber);
	break;
	}
}

// Function to turn pin to setToValue
void pin2_gpio_set (int pinNumber, int setToValue)
{
	switch (setToValue){
	case 0:
		LPC_GPIO2 -> FIOPIN &= ~(1<<pinNumber);
	break;
	case 1:
		LPC_GPIO2 -> FIOPIN |= (1<<pinNumber);
	break;
	}
}

void pin2_gpio_toggle (int pinNumber)
{
	//XOR s the pinNumber bit
	LPC_GPIO2 -> FIOPIN ^= (1<<pinNumber);
}
