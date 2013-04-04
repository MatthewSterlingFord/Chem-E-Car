/*
===============================================================================
 Name        : main.c
 Author      : 
 Version     :
 Copyright   : Copyright (C) 
 Description : main definition
===============================================================================
 */

#include <cr_section_macros.h>
#include <NXP/crp.h>
//#include "../include/redlib/sys/libconfig-arm.h"


//NEED TO SWITCH TO Redlib library variant that you require (None, Nohost, Semihost)
#include <stdio.h>


#ifdef __USE_CMSIS
#include "LPC17xx.h"
#endif

#include "lpc17xx_gpio.h"
#include "lpc17xx_pinsel.h"

#include "sc_GPIO.h"
#include "sc_timer.h"
#include "sc_pwm.h"
//#include "sc_timerPWM.h"

#include "type.h"
#include "timer.h"
#include "functions.h"
#include "clock.h"
#include "gpio.h"
#include "adc.h"
#include "alphanumeric.h"
#include "lpc_types.h"
#include "speed.h"
#include "sevenseg.h"

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP;

//VARIABLES

const char *HEX_CHAR_TABLE = "0123456789ABCDEF";
volatile static uint32_t idealLoops = 0;
uint_fast16_t analog_val;

//FUNCTIONS

//void ADC_IRQHandler(void) {
//  analog_val = (LPC_ADC ->ADDR0 >> 4) & 0x0fff;
//  alpha_display(HEX_CHAR_TABLE[analog_val >> 8]);
//
////  // Print result
//  if ((CoreDebug->DHCSR & CoreDebug_DHCSR_C_DEBUGEN_Msk)) {
//   printf("%#X  %d\n", analog_val, analog_val);
//  }
////
////  // Start conversion
//  LPC_ADC ->ADCR |= LEFT_BIT_SHIFT(HIGH,24);
//}

/******************************************************************************
** Function name:		PWM1_IRQHandler
**
** Descriptions:		PWM1 interrupt handler
**						For now, it only deals with PWM1 match 0
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void PWM1_IRQHandler (void)
{
  uint32_t regVal;
  PWM_Set(1,6,speed);								//Set PWM offset
  regVal = LPC_PWM1->IR;
//  if ( regVal & MR0_INT )
//  {
//	match_counter1++;
//  }
  LPC_PWM1->IR |= regVal;		/* clear interrupt flag on match 0 */
  return;
}

void TIMER0_IRQHandler(void) {
  // Flip LED pin
  //LPC_GPIO0 ->FIOPIN ^= (1 << 22);
  pin0_gpio_toggle(LED2);

  //toggleAllLEDs();

  // Clear ALL interrupt flags, or else this interrupt will loop over and over
  LPC_TIM0->IR = 0xff;
}

float timeSinceLastButtonDetection = 0;
//TODO determine best threshold (how to get it to be 1 second?)
float debouncingThreshHold = 10000;
uint32_t checkvalue;
void EINT3_IRQHandler (void)
{
//	GPIOSetValue(2, SEVEN_SEG_CLOCK_1, 0);
//	GPIOSetValue(2, SEVEN_SEG_DATA_INPUT_1, 0);
//	GPIOSetValue(2, SEVEN_SEG_LATCH_1, 0);

// Use Sys tick timer to debounce
//	printf("%f %s\n",  "PastNumber", timeSinceLastButtonDetection, "IdealLoops", idealLoops);
	if((LPC_TIM0 -> TC) > (debouncingThreshHold + timeSinceLastButtonDetection)){
		checkvalue = GPIOCheckInterrupts(2, 1);
		if (checkvalue == (1 << 2))
		{
//			GPIOSetValue(2, SEVEN_SEG_CLOCK_1, 0);
//			GPIOSetValue(2, SEVEN_SEG_DATA_INPUT_1, 0);
//			GPIOSetValue(2, SEVEN_SEG_LATCH_1, 1);
			if(speed <= 100)
				speed+=10;
			//TODO Display speed on seven segment!
			//GPIOSetValue(0, 10, 1);
		}
		else if (checkvalue == (1 << 3))
		{
//			GPIOSetValue(2, SEVEN_SEG_CLOCK_1, 1);
//			GPIOSetValue(2, SEVEN_SEG_DATA_INPUT_1, 0);
//			GPIOSetValue(2, SEVEN_SEG_LATCH_1, 0);
			if(speed)
				speed-=10;
			//GPIOSetValue(0, 10, 0);
		}
		else if (checkvalue == (1 << 4))
		{
//			GPIOSetValue(2, SEVEN_SEG_CLOCK_1, 0);
//			GPIOSetValue(2, SEVEN_SEG_DATA_INPUT_1, 1);
//			GPIOSetValue(2, SEVEN_SEG_LATCH_1, 0);
			speed = 0;
			//GPIOSetValue(0, 10, 0);
		}
	}
		timeSinceLastButtonDetection = LPC_TIM0 -> TC;
		alpha_display((char)((speed/10)+48));
		GPIOClearInterrupt();
}

//int rising_edge = 1;
//void TIMER0_IRQHandler(void) {
//  LPC_TIM0 ->TC = 0;
//
//  // 120482 cycles is 10ms at 12mhz
//  if (!rising_edge && LPC_TIM0 ->CR0 > 120482) {
//    LPC_GPIO0 ->FIOPIN ^= (1 << 22);
//
//    // Play with Timer1 to reset the out pin
//    LPC_TIM1 ->MR0 = 0; // match value
//    LPC_TIM1 ->EMR = 1 << 4;
//    LPC_TIM1 ->TCR = 1;
//
//    // make sure it has a clock cycle to reset
//    __NOP();
//
//    // Reconfigure emr to
//    LPC_TIM1 ->TCR = 0x02;          // reset timer
//    LPC_TIM1 ->EMR = 2 << 4;
//    LPC_TIM1 ->MR0 = LPC_TIM0 ->CR0; // match value
//    LPC_TIM1 ->TCR = 1;
//  }
//
//  rising_edge = !rising_edge;
//  LPC_TIM0 ->IR = 0xff;           // reset all interrrupts
//}

int color = 0;
void toggleAllLEDs(){
	switch(color){
	case(0):
		GPIOSetValue(0, LED_R1, HIGH);
		GPIOSetValue(0, LED_B1, LOW);
		GPIOSetValue(2, LED_G1_p2, LOW);

		GPIOSetValue(0, LED_R2, HIGH);
		GPIOSetValue(0, LED_B2, LOW);
		GPIOSetValue(0, LED_G2, LOW);

	// 	 pin0_gpio_set(LED_R1, HIGH);
//	 pin0_gpio_set(LED_B1, LOW);
//	 //MUST BE PIN 2
//	 pin2_gpio_set(LED_G1_p2, LOW);
//
//	 pin0_gpio_set(LED_R2, HIGH);
//	 pin0_gpio_set(LED_B2, LOW);
//	 pin0_gpio_set(LED_G2, LOW);
	 color = color + 1;
	 break;
	case(1):
		GPIOSetValue(0, LED_R1, LOW);
		GPIOSetValue(0, LED_B1, HIGH);
		GPIOSetValue(2, LED_G1_p2, LOW);

		GPIOSetValue(0, LED_R2, LOW);
		GPIOSetValue(0, LED_B2, HIGH);
		GPIOSetValue(0, LED_G2, LOW);

//	 pin0_gpio_set(LED_R1, LOW);
//     pin0_gpio_set(LED_B1, HIGH);
//	 //MUST BE PIN 2
//     pin2_gpio_set(LED_G1_p2, LOW);
//
//     pin0_gpio_set(LED_R2, LOW);
//     pin0_gpio_set(LED_B2, HIGH);
//     pin0_gpio_set(LED_G2, LOW);
     color = color + 1;
	break;
	case(2):
		GPIOSetValue(0, LED_R1, LOW);
		GPIOSetValue(0, LED_B1, LOW);
		GPIOSetValue(2, LED_G1_p2, HIGH);

		GPIOSetValue(0, LED_R2, LOW);
		GPIOSetValue(0, LED_B2, LOW);
		GPIOSetValue(0, LED_G2, HIGH);

//	 pin0_gpio_set(LED_R1, LOW);
//	 pin0_gpio_set(LED_B1, LOW);
//	 //MUST BE PIN 2
//	 pin2_gpio_set(LED_G1_p2, HIGH);
//
//     pin0_gpio_set(LED_R2, LOW);
//	 pin0_gpio_set(LED_B2, LOW);
//	 pin0_gpio_set(LED_G2, HIGH);
	 color = 0;
	break;
	}
}

//// Returns 1 if it has reset since last checked. Should only happen exactly one time for every LPC_TIM0->MR0 number of cycles.
//// Returns 0 if it has NOT reset.
//int passedTimerValue = 0;
//int hasTIM0Rest(){
//	int currTimerValue = LPC_TIM0 -> TC;
//	//If the passed timer value is large then the current timer value.  I.E. its been reset.
//	if(passedTimerValue >= currTimerValue){
//		passedTimerValue = currTimerValue;
//		return 1;
//	}else{
//		passedTimerValue = currTimerValue;
//		return 0;
//	}
//}

//void blinkBetweenLEDsWithSimpleCounter(){
//	volatile static int i = 0;
//	int onIndicator = 0;
//	while(1) {
//		i++ ;
//		if(i%100000 == 0){
//			if(onIndicator == 0){
//				onIndicator = 1;
//				pin0_gpio_toggle(11);
//			}else{
//				pin0_gpio_toggle(11);
//				onIndicator = 0;
//			}
//		}
//	}
//}

//void blinkBetweenLEDsWithTimerUsingResetOnMatch(){
//	setUpTimer0ForResetOnMatch();
//	//TODO try 6000000
//	LPC_TIM0->MR0 = 3000000;
//
//	int onIndicator = 0;
//	while(1) {
//		if(hasTIM0Rest() == 1){
//			pin0_gpio_toggle(11);
//			pin0_gpio_toggle(23);
//			if(onIndicator == 0){
//				led2_off();
////				pin0_9_on();
//				onIndicator = 1;
//			}else{
//				led2_on();
////				pin0_9_off();
//				onIndicator = 0;
//			}
//		}
//	}
//}

//void blinkBetweenLEDsWithTimerUsingInteruptOnMatch(){
//	setUpClk();
//	setUpTimer0ForInteruptOnMatch();
//	//TODO try 6000000
//	LPC_TIM0->MR0 = 3000000;
//
//	int onIndicator = 0;
//	while(1) {
//		if(hasTIM0Rest() == 1){
//			if(onIndicator == 0){
//				led2_off();
//				pin0_9_on();
//				onIndicator = 1;
//			}else{
//				led2_on();
//				pin0_9_off();
//				onIndicator = 0;
//			}
//		}
//	}
//}

void initReactionDetection (void){
 //Inits and turns on reaction led.
	PINSEL_CFG_Type PinCfg;

	PinCfg.Funcnum   = 0;
	PinCfg.OpenDrain = 0;
	PinCfg.Pinmode   = 0;
	PinCfg.Pinnum    = 11;
	PinCfg.Portnum   = 0;
	PINSEL_ConfigPin(&PinCfg);
	GPIO_SetDir(0, 1 << PinCfg.Pinnum, OUTPUT);
	GPIO_SetValue(0, 1<< PinCfg.Pinnum);
	//pin0_gpio_init(OUTPUT, 11);
 	//pin0_gpio_set(11,HIGH);

	//Inits reaction detection ADC pin.
	initADC(0);
}

//void init_LED2_with_TIMER3_to_blink_every_second (void){
//	init_on_Board_led2();
//	setupTIMER3_to_interupt_on_match();
//	blinkBetweenLEDsWithTimerUsingResetOnMatch();
//}

void setupTIMER0_to_interupt_on_match(){
	  // Set bits 2 and 3 of PCLKSEL0 to choose peripheral divider for TIMER0
	  // Setting to 1 chooses no divider
	  LPC_SC ->PCLKSEL0 = (1 << 2);

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
void initAndBlinkOnBoardLED2OnMatchWithInteruptWithTimer0(){
	pin0_gpio_init(OUTPUT, LED2);
	//Timer will be set up to interrupt on match about every one second. Interupt above should toggle LED and clear interrupt.
	setupTIMER0_to_interupt_on_match();
}

void init_both_RGB_LED_to_blink(){
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

//void init_button_press_detection_george(void){
//	  LPC_SC ->CLKSRCSEL = 1;   // Select main clock source
//	  LPC_SC ->PLL0CON = 0;     // Bypass PLL0, use clock source directly
//
//	  // Feed the PLL register so the PLL0CON value goes into effect
//	  LPC_SC ->PLL0FEED = 0xAA; // set to 0xAA
//	  LPC_SC ->PLL0FEED = 0x55; // set to 0x55
//
//	  // Set clock divider to 0+1=1
//	  LPC_SC ->CCLKCFG = 0;
//
//	  // Choose undivided peripheral clocks for TIMER0,1
//	  LPC_SC ->PCLKSEL0 |= (1 << 2);
//	  LPC_SC ->PCLKSEL0 |= (1 << 4);
//
//	  // Power TIMER0, TIMER1
//	  LPC_SC ->PCONP |= 3;
//
//	  // Bring MAT1.0 low on timer1 match
//	  LPC_TIM1 ->EMR = 2 << 4;
//
//	  // Setup IO pins
//	  LPC_GPIO0 ->FIODIR = (1 << 22);
//	  LPC_GPIO0 ->FIOSET = (1 << 22);
//
//	  // Configure pins
//	  //   P1.26 as CAP0.0 (TIMER0 capture pin 0)
//	  //   P1.27 as CAP0.1 (TIMER0 capture pin 1)
//	  //   P1.22 as MAT1.0
//	  LPC_PINCON ->PINSEL3 |= (3 << 20) | (3 << 22) | (3 << 12);
//
//	  // Timer0 interrupt
//	  NVIC_EnableIRQ(TIMER0_IRQn);
//
//	  // Configure timer one so that it constantly counts up, at the undivided
//	  // clock rate. When CAP0.0 goes high or low, capture value is stored and
//	  // timer value is reset and interrupt is triggered
//	  LPC_TIM0 ->MCR = 1 << 1;
//	  LPC_TIM0 ->TCR = 0x02;           // reset timer
//	  LPC_TIM0 ->PR = 1;               // No prescale
//	  LPC_TIM0 ->MR0 = 0xffffffff;     // match value (unnecessary)
//	  LPC_TIM0 ->IR = 0xff;            // reset all interrrupts
//	  LPC_TIM0 ->TCR = 1;              // enable timer
//
//	  // Capture Control Register
//	  //   bit 0 - Capture on CAP0.0 rising edge
//	  //   bit 1 - Capture on CAP0.0 falling edge
//	  //   bit 2 - Interrupt on CAP0.0 event
//	  LPC_TIM0 ->CCR = 1 | (1 << 1) | (1 << 2);
//
//	  // Timer 1, which controls led.
//	  LPC_TIM1 ->PR = 1;          // Prescale
//	  LPC_TIM1 ->TC = 0;          //  counter
//}
void init_button_press_detection(){
	GPIOSetPull(2, 2, 2);
	GPIOSetPull(2, 3, 2);
	GPIOSetPull(2, 4, 2);
	GPIOSetInterrupt(2, 2, 1);
	GPIOSetInterrupt(2, 3, 1);
	GPIOSetInterrupt(2, 4, 1);
}

void init_both_SEVEN_SEGMENT_DISPLAY_pins(){
//	pin2_gpio_init(OUTPUT, SEVEN_SEG_DATA_INPUT_1);
//	pin2_gpio_init(OUTPUT, SEVEN_SEG_LATCH_1);
//	pin2_gpio_init(OUTPUT, SEVEN_SEG_CLOCK_1);
//
//	pin2_gpio_init(OUTPUT, SEVEN_SEG_DATA_INPUT_2);
//	pin2_gpio_init(OUTPUT, SEVEN_SEG_LATCH_2);
//	pin2_gpio_init(OUTPUT, SEVEN_SEG_CLOCK_2);
}

void init_pwm_mixer(){
	PWM_Init(1,6,100);											//Initialize PWM port 6
	PWM_Start(1);												//Start PWM

	//TODO ensure this does not cause issues with Debug LED
	TimerInit(0, 100);											//Initialize timer

	int pwmoffset = 0;											//Declare pwmoffset as integer

//    while(1)													//Infinite loop
//    {
//    	for (pwmoffset = 0; pwmoffset < 1000; ++pwmoffset) {	//For loop to set offset from 0 to 1000
//    		PWM_Set(1,6,pwmoffset);								//Set PWM offset
//    		delayMs(0,5);										//Delay 5 ms
//
//		}
//    	for (pwmoffset = 1000; pwmoffset > 0; --pwmoffset) {	//For loop to set offset for 1000 to 0
//    		PWM_Set(1,6,pwmoffset);								//Set PWM offset
//    		delayMs(0,5);										//Delay 5 ms
//		}
//   }
}

void init_timer1(){
	timer
}

void init(void){
	//Sets up CPU and perh clock to be main with no divs
	setUpClkAsMainOscillatorNoDiv();

	//TODO stop from reseting all interupts in timer0 at end of interupt...
	//Set up debug blinking led.
	initAndBlinkOnBoardLED2OnMatchWithInteruptWithTimer0();
	//TODO need to determine what macros are failing to get each to RGB LED to blink. RGB LED 2 is working. Need to check RGB led 1. Now only green comes on when red should.
	init_both_RGB_LED_to_blink();

	//TODO int 2nd seven segment and use them
	init_both_SEVEN_SEGMENT_DISPLAY_pins();

//	int i = 0;
//	//for(i = 0; i <= 9; i++){
//		display(3,FALSE);
//	//	short_delay(2000);
//	//}
	//This will setup and use Timer0
	//TODO remove from interupt all the RGG Blinking function!!!!!

	//inits and set reaction LED to high. Sets up reaction detection with ADC pin.
	initReactionDetection();

	init_timer1();
	init_button_press_detection();

	init_pwm_mixer();

	alpha_init();
	alpha_display('0');

	//MANY NOT BE WORKING ANYMORE
	//blinkBetweenLEDsWithSimpleCounter();
	//	blinkLED2WithTimer3UsingResetOnMatch();
	//	blinkBetweenLEDsWithTimerUsingResetOnMatch();

	//blinks on board LED2 to ensure microprocessor is running
	//setUpTimer3ToToggle_pin0_10_OnMatch();;
}
int main(void) {

	init();
	//Will ideal here and wait for interupts
	while(1) {
		idealLoops++;
	}
	return 0;
}

