/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
 */

#ifdef __USE_CMSIS
#include "LPC17xx.h"
#include "type.h"
#include "timer.h"
#include "functions.h"
#include "clock.h"
#include "gpio.h"
#endif

#include <cr_section_macros.h>
#include <NXP/crp.h>

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP;

void TIMER0_IRQHandler(void) {
  // Flip LED pin
  LPC_GPIO0 ->FIOPIN ^= (1 << 22);

  // Clear interrupt flags, or else this interrupt will loop over and over
  LPC_TIM0->IR = 0xff;
}

int passedTimerValue = 0;

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

//Powers on and sets pin to output
void init_on_Board_led2 (void)
{
	// Set GPIO - P0_22 - to be output
	LPC_GPIO0->FIODIR |= (1 << 22);
}

//TODO REMOVE
// Function to turn LED2 on
void led2_on (void)
{
	LPC_GPIO0->FIOSET = (1 << 22);
}

// Function to turn LED2 off
void led2_off (void)
{
	LPC_GPIO0->FIOCLR = (1 << 22);
}


// Returns 1 if it has reset since last checked. Should only happen exactly one time for every LPC_TIM0->MR0 number of cycles.
// Returns 0 if it has NOT reset.
int hasTIM0Rest(){
	int currTimerValue = LPC_TIM0 -> TC;
	//If the passed timer value is large then the current timer value.  I.E. its been reset.
	if(passedTimerValue >= currTimerValue){
		passedTimerValue = currTimerValue;
		return 1;
	}else{
		passedTimerValue = currTimerValue;
		return 0;
	}
}

int captureTIM1(){

}

void blinkBetweenLEDsWithSimpleCounter(){
	volatile static int i = 0;
	int onIndicator = 0;
	while(1) {
		i++ ;
		if(i%100000 == 0){
			if(onIndicator == 0){
				led2_off();
				pin0_9_on();
				pin0_10_on();
				onIndicator = 1;
				pin0_gpio_toggle(11);
			}else{
				led2_on();
				pin0_9_off();
				pin0_10_on();
				pin0_gpio_toggle(11);
				onIndicator = 0;
			}
		}
	}
	return 0 ;
}

void blinkBetweenLEDsWithTimerUsingResetOnMatch(){
	setUpTimer0ForResetOnMatch();
	//TODO try 6000000
	LPC_TIM0->MR0 = 3000000;

	int onIndicator = 0;
	while(1) {
		if(hasTIM0Rest() == 1){
			pin0_gpio_toggle(11);
			pin0_gpio_toggle(23);
			if(onIndicator == 0){
				led2_off();
//				pin0_9_on();
				onIndicator = 1;
			}else{
				led2_on();
//				pin0_9_off();
				onIndicator = 0;
			}
		}
	}
	return 0;
}

void blinkBetweenLEDsWithTimerUsingInteruptOnMatch(){
	setUpClk();
	setUpTimer0ForInteruptOnMatch();
	//TODO try 6000000
	LPC_TIM0->MR0 = 3000000;

	int onIndicator = 0;
	while(1) {
		if(hasTIM0Rest() == 1){
			if(onIndicator == 0){
				led2_off();
				pin0_9_on();
				onIndicator = 1;
			}else{
				led2_on();
				pin0_9_off();
				onIndicator = 0;
			}
		}
	}
	return 0;
}

void initReactionDetection (void){
	//Inits and turns on reaction led.
	pin0_gpio_init(0, 10);
	pin0_gpio_set(22,HIGH);
}

void init_LED2_with_TIMER3_to_blink_every_second (void){
	init_on_Board_led2();
	setupTIMER3_to_interupt_on_match();
	blinkBetweenLEDsWithTimerUsingResetOnMatch();
}

void setupTIMER0_to_interupt_on_match(){

	  // Set bits 2 and 3 of PCLKSEL0 to choose peripheral divider for TIMER0
	  // Setting to 1 chooses no divider
	  LPC_SC ->PCLKSEL0 = (1 << 2);

	// Setup timer
	  LPC_SC ->PCONP |= 1;		 // power for timer

	  // No prescaling
	  LPC_TIM0 ->PR = 0; // no prescalling for the peripheral clock in

	  LPC_TIM0 ->CCR = (0x1 << 0)  // Setting up the Capture for CAP.0 on rising edge
					 | (0x1 << 3)  // Setting up the Capture for CAP.1 on rising edge
					 | (0x1 << 2)  // Enable interrupt for CAP.0
					 | (0x1 << 5); // Enable interrupt for CAP.1

	  // Interrupt and Reset on MR0 and MR1
		  // Match Control Register
		  //   1 in bit 0 - timer will trigger the interrupt when it matches
		  //   1 in bit 1 - timer will automatically reset to 0 when it matches
	  LPC_TIM0 ->MCR = (1 << 0) | (1 << 1);

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
void blinkOnBoardLED2OnMatchWithInteruptWithTimer0(){
	pin0_gpio_init(OUTPUT, LED2);
	setupTIMER0_to_interupt_on_match();
}


int init(void){
	//Sets up CPU and perh clock to be main with no divs
	setUpClkAsMainOscillatorNoDiv();

	//This will setup and use Timer0
	blinkOnBoardLED2OnMatchWithInteruptWithTimer0();

	//inits and set reaction LED to high. on  sets
	initReactionDetection();

	//	pin0_gpio_init(OUTPUT, LED2);
//	pin0_gpio_init(OUTPUT, 10);
//	pin0_gpio_init(OUTPUT, 11);
	//blinkBetweenLEDsWithSimpleCounter();
	//	blinkLED2WithTimer3UsingResetOnMatch();
	//	blinkBetweenLEDsWithTimerUsingResetOnMatch();





	//blinks on board LED2 to ensure microprocessor is running
	//setUpTimer3ToToggle_pin0_10_OnMatch();

//Not being used (blue)
	//pin0_init(9);
//Not being used (1 about yellow)
	//pin0_init(10);

}

int main(void) {
	init();

	volatile static int i = 0;
	//shouldNeverGetHere
	while(1) {
		i++;
	}
	return 0;
}

