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

//void setUpTimer0ForInteruptOnMatch(void)
//{
//	// Turn on timer 0
//	BITON(LPC_SC->PCONP,0);
//
//	// Reset Timer
//	LPC_TIM0->TCR = 0x2;
//
//	// Set t0 to take the not scaling the input of clock signal
//	// LPC_SC->PCLKSEL0 |= 1 << 2;
//	SETBITS(LPC_SC->PCLKSEL0,0,2,0x01);
//
//
//
//	// No prescale (pg 495)
//	LPC_TIM0->PR = 0x0;
//	LPC_TIM0->PC = 0x0;
//
//	//makes it reset on match
//	LPC_TIM0->MCR = 0x2;
//
//	//TODO try 6000000
//	LPC_TIM0->MR0 = 60000;
//
//	// Enable Timer
//	LPC_TIM0->TCR = 0x01;
//}

void setupTIMER0_to_interupt_on_match(){
	  // Set bits 2 and 3 of PCLKSEL0 to choose peripheral divider for TIMER0
	  // Setting to 1 chooses no divider
	  LPC_SC ->PCLKSEL0 |= (1 << 2);
	  LPC_SC ->PCLKSEL0 &= ~(1 << 3);

	// Setup timer
	  LPC_SC ->PCONP |= 1;		 // power for timer

	  // No prescaling
	  LPC_TIM0 ->PR = 0; // no prescalling for the peripheral clock in

//	  LPC_TIM0 ->CCR = (0x1 << 0)  // Setting up the Capture for CAP.0 on rising edge
//					 | (0x1 << 3)  // Setting up the Capture for CAP.1 on rising edge
//					 | (0x1 << 2)  // Enable interrupt for CAP.0
//					 | (0x1 << 5); // Enable interrupt for CAP.1

	  // Interrupt and Reset on MR0 and MR1
		  // Match Control Register
		  //   1 in bit 0 - timer will trigger the interrupt when it matches
		  //   1 in bit 1 - timer will automatically reset to 0 when it matches
	  LPC_TIM0 ->MCR |= (1 << 0) | (1 << 1);

	  // Disable timer
	  LPC_TIM0 ->TCR = 0x02;

	  // Match value
	  LPC_TIM0 ->MR0 = 12000;

	  // Reset all interrupts
	  LPC_TIM0 ->IR = 0xff;

	  // Start timer
	  LPC_TIM0 ->TCR = 1;

	  NVIC_EnableIRQ(TIMER0_IRQn);
}

void setupTIMER3_to_interupt_on_match(){
	  // Set bits 2 and 3 of PCLKSEL0 to choose peripheral divider for TIMER0
	  // Setting to 1 chooses no divider
	  LPC_SC ->PCLKSEL1 = (1 << 2);

	// Setup timer
	  LPC_SC ->PCONP |= 1;		 // power for timer

	  // No prescaling
	  LPC_TIM0 ->PR = 0; // no prescalling for the peripheral clock in

//	  LPC_TIM0 ->CCR = (0x1 << 0)  // Setting up the Capture for CAP.0 on rising edge
//					 | (0x1 << 3)  // Setting up the Capture for CAP.1 on rising edge
//					 | (0x1 << 2)  // Enable interrupt for CAP.0
//					 | (0x1 << 5); // Enable interrupt for CAP.1

	  // Interrupt and Reset on MR0 and MR1
		  // Match Control Register
		  //   1 in bit 0 - timer will trigger the interrupt when it matches
		  //   1 in bit 1 - timer will automatically reset to 0 when it matches
	  LPC_TIM0 ->MCR |= (1 << 0) | (1 << 1);

	  // Disable timer
	  LPC_TIM0 ->TCR = 0x02;

	  // Match value
	  LPC_TIM0 ->MR0 = 12000000;

	  // Reset all interrupts
	  LPC_TIM0 ->IR = 0xff;

	  // Start timer
	  LPC_TIM0 ->TCR = 1;

	  NVIC_EnableIRQ(TIMER0_IRQn);
}
