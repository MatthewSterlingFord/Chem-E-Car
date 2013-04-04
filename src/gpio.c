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
//FIOxDIR
//0 Controlled pin is input.
//1 Controlled pin is output.
void pin0_gpio_init (int output, int pinNumber)
{
	switch (output){
	case 1:
		LPC_GPIO0 -> FIODIR  |= 1 << pinNumber;
		LPC_GPIO0 -> FIOSET  |= 1 << pinNumber;
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

void init_both_RGB_LEDs(){
//	PINSEL_CFG_Type PinCfg;
//
//	PinCfg.Funcnum   = 0;
//	PinCfg.OpenDrain = 0;
//	PinCfg.Pinmode   = 0;
//
//	PinCfg.Pinnum    = LED_R1;
//	PinCfg.Portnum   = 0;
//	PINSEL_ConfigPin(&PinCfg);
//	GPIO_SetDir(PinCfg.Portnum, 1 << PinCfg.Pinnum, OUTPUT);
//	//BELOW NOT WORKING SO DOING ANOTHER WAY
//	GPIO_SetValue(PinCfg.Portnum, 1 << PinCfg.Pinnum);
////		LPC_GPIO0 ->FIOSET3 = (1<<3);
//
//	PinCfg.Pinnum    = LED_B1;
//	PinCfg.Portnum   = 0;
//	PINSEL_ConfigPin(&PinCfg);
//	GPIO_SetDir(PinCfg.Portnum, 1 << PinCfg.Pinnum, OUTPUT);
//	//BELOW NOT WORKING SO DOING ANOTHER WAY
//	GPIO_SetValue(PinCfg.Portnum, 1 << PinCfg.Pinnum);
////		LPC_GPIO0 ->FIOPIN3 |= (1<<4);
//
//	PinCfg.Pinnum    = LED_G1_p2;
//	PinCfg.Portnum   = 2;
//	PINSEL_ConfigPin(&PinCfg);
//	GPIO_SetDir(PinCfg.Portnum, 1 << PinCfg.Pinnum, OUTPUT);
//	GPIOSetValue(PinCfg.Portnum, PinCfg.Pinnum, HIGH);
//
//
//	PinCfg.Pinnum    = LED_R2;
//	PinCfg.Portnum   = 0;
//	PINSEL_ConfigPin(&PinCfg);
//	GPIO_SetDir(PinCfg.Portnum, 1 << PinCfg.Pinnum, OUTPUT);
//
//	PinCfg.Pinnum    = LED_B2;
//	PinCfg.Portnum   = 0;
//	PINSEL_ConfigPin(&PinCfg);
//	GPIO_SetDir(PinCfg.Portnum, 1 << PinCfg.Pinnum, OUTPUT);
//	GPIOSetValue(PinCfg.Portnum, PinCfg.Pinnum, HIGH);
//
//
//	PinCfg.Pinnum    = LED_G2;
//	PinCfg.Portnum   = 0;
//	PINSEL_ConfigPin(&PinCfg);
//	GPIO_SetDir(PinCfg.Portnum, 1 << PinCfg.Pinnum, OUTPUT);
//	GPIOSetValue(PinCfg.Portnum, PinCfg.Pinnum, HIGH);

// //OLD WAY OF INITING RGB LEDS
	pin0_gpio_init(OUTPUT, LED_R1);
	pin0_gpio_init(OUTPUT, LED_B1);
	pin2_gpio_init(OUTPUT, LED_G1_p2); //Must be pin 2!

	pin0_gpio_init(OUTPUT, LED_R2);
	pin0_gpio_init(OUTPUT, LED_B2);
	pin0_gpio_init(OUTPUT, LED_G2);
}

