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
#include "lpc17xx_qei.h"
#include "lpc17xx_mcpwm.h"
//#include "nxp_qei.c"

// Variable to store CRP value in. Will be placed automatically
// by the linker when "Enable Code Read Protect" selected.
// See crp.h header for more information
__CRP const unsigned int CRP_WORD = CRP_NO_CRP;

//VARIABLES

const char *HEX_CHAR_TABLE = "0123456789ABCDEF";
volatile static uint32_t idleLoops = 0;
uint_fast16_t analog_val;


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
  if(LPC_PWM1 -> IR == (LPC_PWM1->IR) & (1<<1)){
	  PWM_Set(1,1,speed);			//Set PWM offset
  }else{
 	  PWM_Set(1,5,17);			//Set PWM offset
  }
  regVal = (LPC_PWM1->IR);
  LPC_PWM1->IR |= regVal;		/* clear interrupt flag on match 0 */
}

long int num_overflows = 0;
int current_anode = 1;

char disp[4] = {'A', 'B', 'C', 'D'};
int dots[4] = {0, 1, 0, 1};

int led2_toggle = 0;

void TIMER0_IRQHandler(void) {
  // Flip LED pin
  //LPC_GPIO0 ->FIOPIN ^= (1 << 22);
  if(led2_toggle == 100){
	  pin0_gpio_toggle(LED2);
	  led2_toggle = 0;
  }else{
	  led2_toggle++;
  }
  alpha_display(disp[current_anode-1],current_anode, dots[current_anode-1]);
  //toggleAllLEDs();
  if(current_anode < 4){
	  current_anode++;
  }else{
	  current_anode=1;
  }
  num_overflows++;

  // Clear ALL interrupt flags, or else this interrupt will loop over and over
  LPC_TIM0->IR = 0xff;
}

//float timeSinceLastButtonDetection = 0;
//TODO determine best threshold (how to get it to be 1 second?)

float debouncingThreshHold = 150;
uint32_t checkvalue;
void EINT3_IRQHandler (void)
{
	if(num_overflows >= debouncingThreshHold){
	//	printf("%d %d stuff\n", LPC_QEI->QEIVEL, LPC_QEI->QEICAP);
		checkvalue = GPIOCheckInterrupts(2, 1);
		if (checkvalue == (1 << 2))
		{
			if(speed < 100)
				speed+=5;
		}
		else if (checkvalue == (1 << 3))
		{
			if(speed)
				speed-=5;
		}
		else if (checkvalue == (1 << 4))
		{
			speed = 0;
		}
		num_overflows = 0;
	}
	if(speed == 100){
		disp[0] = 'a'; disp[1] = '0';
	}else{
		//48 since zero is 48 in ascii
		disp[0] = (char)((speed/10)+48); disp[1] = (char)((speed%10)+48);
	}
		//alpha_display((char)((speed/10)+48), current_anode, TRUE);
	GPIOClearInterrupt();
}

int show_big_battery = 1;

void ADC_IRQHandler (void) {
	uint32_t res;
	//float big_battery_voltage;
	//float small_battey_voltage;
	float voltage;
	if((LPC_ADC->ADDR0 >> 31) & 1){
		  res = (LPC_ADC->ADDR0 >> 4) & 0xFFF;
		  voltage = ((float)res/(float)0xFFF)*(float)3.1;
		  disp[2] = (char)(((int)voltage%10)+48);
		  disp[3] = (char)(((int)(voltage*10)%10)+48);
		  //printf("%d %s\n", (int)voltage, "Volts");
		  if(res >= 0xAAA){
			  GPIOSetValue(0, LED_R2, HIGH);
			  GPIOSetValue(0, LED_B2, LOW);
			  GPIOSetValue(0, LED_G2, LOW);
		  }else if(res >= 0x555){
			  GPIOSetValue(0, LED_R2, LOW);
			  GPIOSetValue(0, LED_B2, HIGH);
			  GPIOSetValue(0, LED_G2, LOW);
		  }else{
			  GPIOSetValue(0, LED_R2, LOW);
			  GPIOSetValue(0, LED_B2, LOW);
    		  GPIOSetValue(0, LED_G2, HIGH);
		  }
		  //Restarts ADC Read
		  LPC_ADC->ADCR |= (1 << 24);
	}

	//disp[2] = 'n'; disp[3] = 'a';

	// CANNOT WORK UNTIL BURST MODE GETS WORKING

	// BIG BATTERY const = 3.357, which is hooked into AD4
//	if((LPC_ADC->ADDR3 >> 31) & 1){
//		res = (LPC_ADC->ADDR3 >> 4) & 0xFFF;
//		big_battery_voltage = (((float)res/(float)0xFFF)*(float)3.1)*3.357;
//		//disp[2] = (char)(((int)big_battery_voltage%10)+48);
//		//disp[3] = (char)(((int)(big_battery_voltage*10)%10)+48);
//		//Restarts ADC Read
//		LPC_ADC->ADCR |= (1 << 24);
//	}
//	// SMALL BATTERY const = 3.263, which is hooked into AD5
//	if((LPC_ADC->ADDR4 >> 31) & 1){
//		res = (LPC_ADC->ADDR4 >> 4) & 0xFFF;
//		small_battery_voltage = (((float)res/(float)0xFFF)*(float)3.1)*3.263;
//		//disp[2] = (char)(((int)small_battery_voltage%10)+48);
//		//disp[3] = (char)(((int)(small_battery_voltage*10)%10)+48);
//		//Restarts ADC Read
//		LPC_ADC->ADCR |= (1 << 24);
//	}
//
//	if(show_big_battery){
//		disp[2] = (char)(((int)big_battery_voltage%10)+48);
//		disp[3] = (char)(((int)(big_battery_voltage*10)%10)+48);
//	}else{
//		disp[2] = (char)(((int)small_battery_voltage%10)+48);
//		disp[3] = (char)(((int)(small_battery_voltage*10)%10)+48);
//	}

}

void QEI_IRQHandler(void) {
 // printf("%d, %d, %s\n", LPC_QEI->QEIVEL, LPC_QEI->QEICAP, "Speed to lowwwww");
  //LPC_QEI->QEICLR = 0xff;
// Clear all Interrupt pending
  LPC_QEI->QEICLR = QEI_INTCLR_BITMASK;
 // QEI_IntClear(LPC_QEI, QEI_INTFLAG_DIR_Int);
}

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

}

//void init_LED2_with_TIMER3_to_blink_every_second (void){
//	init_on_Board_led2();
//	setupTIMER3_to_interupt_on_match();
//	blinkBetweenLEDsWithTimerUsingResetOnMatch();
//}


void initAndBlinkOnBoardLED2OnMatchWithInteruptWithTimer0(){
	pin0_gpio_init(OUTPUT, LED2);
	//Timer will be set up to interrupt on match about every one second. Interupt above should toggle LED and clear interrupt.
	setupTIMER0_to_interupt_on_match();
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
	//PWM_Start(1);												//Start PWM

	//TODO ensure this does not cause issues with Debug LED
	TimerInit(1, 100);											//Initialize timer

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

void init_pwm_motor_controller(){

	LPC_SC ->PCONP |= 18;
	LPC_PINCON->PINSEL3 |= (1 << 6);
	LPC_PINCON->PINSEL3 &= ~(1 << 7);

	//PWM_Init(1,5,100);											//Initialize PWM port 5

		switch (5) {

			case 1:
				LPC_PINCON->PINSEL4 |= (01 << 0);
				break;

			case 2:
				LPC_PINCON->PINSEL4 |= (01 << 2);
				break;

			case 3:
				LPC_PINCON->PINSEL4 |= (01 << 4);
				break;

			case 4:
				LPC_PINCON->PINSEL4 |= (01 << 6);
				break;

			case 5:
				LPC_PINCON->PINSEL4 |= (01 << 8);
				break;

			case 6:
				LPC_PINCON->PINSEL4 |= (01 << 10);
				break;
		}


		LPC_PWM1->TCR = TCR_RESET;	/* Counter Reset */
		LPC_PWM1->PR = 0x00;		/* count frequency:Fpclk */
		LPC_PWM1->MCR = PWMMR5I;	/* interrupt on PWMMR0, reset on PWMMR0, reset
									TC if PWM matches */
		LPC_PWM1->MR5 = 100;		/* set PWM cycle */
		/* all PWM latch enabled */

		//TODO Change to only set PWM1.1 and PWM1.5
		LPC_PWM1->LER = LER0_EN | LER1_EN | LER2_EN | LER3_EN | LER4_EN | LER5_EN | LER6_EN;

	PWM_Start(1);												//Start PWM

	//TODO ensure this does not cause issues with Debug LED
	//TimerInit(1, 100);											//Initialize timer

	int pwmoffset = 0;											//Declare pwmoffset as integer

}

void init_encoder(){
	LPC_SC ->PCONP |= 18;
	LPC_SC ->PCLKSEL1 |= (1 << 0);
	LPC_SC ->PCLKSEL1 &= ~(1 << 1);

	LPC_PINCON->PINSEL3 |= (1 << PHASE_A);
    LPC_PINCON->PINSEL3 &= ~(1 << PHASE_A+1);

	LPC_PINCON->PINSEL3 |= (1 << PHASE_B);
    LPC_PINCON->PINSEL3 &= ~(1 << PHASE_B+1);

	LPC_PINCON->PINSEL3 |= (1 << INDEX);
    LPC_PINCON->PINSEL3 &= ~(1 << INDEX+1);

    //LPC_QEI->QEICONF |= (1 << 1);

//    typedef struct {
//    	uint32_t DirectionInvert	:1; 	/**< Direction invert option:
//    										- QEI_DIRINV_NONE: QEI Direction is normal
//    										- QEI_DIRINV_CMPL: QEI Direction is complemented
//    										*/
//    	uint32_t SignalMode			:1; 	/**< Signal mode Option:
//    										- QEI_SIGNALMODE_QUAD: Signal is in Quadrature phase mode
//    										- QEI_SIGNALMODE_CLKDIR: Signal is in Clock/Direction mode
//    										*/
//    	uint32_t CaptureMode		:1;		/**< Capture Mode Option:
//    										- QEI_CAPMODE_2X: Only Phase-A edges are counted (2X)
//    										- QEI_CAPMODE_4X: BOTH Phase-A and Phase-B edges are counted (4X)
//    										*/
//    	uint32_t InvertIndex		:1; 	/**< Invert Index Option:
//    										- QEI_INVINX_NONE: the sense of the index input is normal
//    										- QEI_INVINX_EN: inverts the sense of the index input
//    										*/
//    } QEI_CFG_Type;

    QEI_CFG_Type qei_parm = {QEI_DIRINV_NONE, QEI_SIGNALMODE_QUAD, QEI_CAPMODE_4X, QEI_INVINX_NONE};
    QEI_Init(LPC_QEI, &qei_parm);



    LPC_QEI->VELCOMP = 2000000; // velocity compare number
    LPC_QEI-> QEIIES |= (1 << 2); // set interupt on low velocity
    NVIC_EnableIRQ(QEI_IRQn);
}


void init(void){
	//Sets up CPU and perh clock to be main with no divs
	setUpClkAsMainOscillatorNoDiv();

	//TODO stop from reseting all interupts in timer0 at end of interupt...
	//Set up debug blinking led.
	initAndBlinkOnBoardLED2OnMatchWithInteruptWithTimer0();
	//TODO need to determine what macros are failing to get each to RGB LED to blink. RGB LED 2 is working. Need to check RGB led 1. Now only green comes on when red should.
	init_both_RGB_LEDs();

	//inits and set reaction LED to high. Sets up reaction detection with ADC pin.
	initReactionDetection();

	initADC(0);

	init_button_press_detection();

	init_pwm_mixer();

	//c_entry();
	init_encoder();

	//init_pwm_motor_controller();

	alpha_init();
	disp[1] = '8';

}
int main(void) {

	init();
	//Will ideal here and wait for interupts
	while(1) {
		idleLoops++;
	}
	return 0;
}

