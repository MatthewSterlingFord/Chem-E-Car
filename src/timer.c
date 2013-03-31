/*
 * timer.c
 *
 *  Created on: Mar 30, 2013
 *      Author: Matthew
 */
#include "LPC17xx.h"
#include "type.h"
#include "timer.h"
#include "functions.h"

void setUpTimer0ForResetOnMatch(void)
{
	// Turn on timer 0
	LPC_SC-> PCONP |= (1 << 0);

	// Reset Timer
	LPC_TIM0->TCR = 0x2;

	// Set t0 to take the not scaling the input of clock signal
	//	      LPC_SC->PCLKSEL0 |= 1 << 2;
	SETBITS(LPC_SC->PCLKSEL0,0,2,0x01);

	// No prescale (pg 495)
	LPC_TIM0->PR = 0x0;
	LPC_TIM0->PC = 0x0;

	//makes it reset on match
	LPC_TIM0->MCR = 0x2;

	//TODO try 6000000
	LPC_TIM0->MR0 = 6000000;

	// Enable Timer
	LPC_TIM0->TCR = 0x01;
}

void setUpTimer3ToToggle_pin0_10_OnMatch(){
	// Turn on timer 3
	BITON(LPC_SC->PCONP,23);

	// Reset Timer
	LPC_TIM3->TCR = 0x2;

	// Make sure timer 3 is in timer mode (pg 494 table 428)
	SETBITS(LPC_TIM3->CTCR,0,2,0x0);

	// Set t0 to take the not scaling the input of clock signal
	//	      LPC_SC->PCLKSEL0 |= 1 << 2;
	SETBITS(LPC_SC->PCLKSEL1,14,2,0x01);

	// No prescale (pg 495)
	LPC_TIM3->PR = 0x0;
	LPC_TIM3->PC = 0x0;

    // Set Timer 3 match register 0 interrupt off, reset on, stop off (pg 496 table 429)
    BITOFF(LPC_TIM3->MCR,0); // int off Interrupt on MR0: an interrupt is generated when MR0 matches the value in the TC.
    BITON(LPC_TIM3->MCR,1);  // reset on
    BITOFF(LPC_TIM3->MCR,2); // stop off

	//TODO try 6000000
	LPC_TIM3->MR0 = 6000000;

	// Enable Timer
	LPC_TIM3->TCR = 0x01;

	 //Set the MAT3[0] pin to toggle on match (pg 498 tb 431,432)
	 SETBITS(LPC_TIM3->EMR,4,2,0x3);
	 // You can find the actual pin in table 73, sec 7.1.1

	 // Set pin 0[10] to MAT3[0] mode (pg 108)
	 SETBITS(LPC_PINCON->PINSEL0,20,2,0x3);
	 // Now pin 40 (0[10]) is connected to the Timer 3 Match 0 external thing
	 //  rather than the default (which is probably gpio)
	 // (just read chapter 8, it has all the details on choosing specific
	 // functions for each pin.)
}

void setupTIMER3_to_interupt_on_match(){

}

void setUpTimer0ForInteruptOnMatch(void)
{
	// Turn on timer 0
	BITON(LPC_SC->PCONP,0);

	// Reset Timer
	LPC_TIM0->TCR = 0x2;

	// Set t0 to take the not scaling the input of clock signal
	// LPC_SC->PCLKSEL0 |= 1 << 2;
	SETBITS(LPC_SC->PCLKSEL0,0,2,0x01);



	// No prescale (pg 495)
	LPC_TIM0->PR = 0x0;
	LPC_TIM0->PC = 0x0;

	//makes it reset on match
	LPC_TIM0->MCR = 0x2;

	//TODO try 6000000
	LPC_TIM0->MR0 = 6000000;

	// Enable Timer
	LPC_TIM0->TCR = 0x01;
}
