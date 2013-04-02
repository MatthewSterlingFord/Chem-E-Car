/*
 * adc.c
 *
 *  Created on: Mar 31, 2013
 *      Author: Matthew
 */

#include "LPC17xx.h"
#include <cr_section_macros.h>

#include "type.h"
#include "timer.h"
#include "clock.h"
#include "functions.h"

//simpleCortex includes
#include "lpc17xx.h"
#include "lpc_types.h"
#include "sc_adc.h"
//sc_adc.h doesnt include all of variables in sc_adc.c....
//#include "sc_adc.c"

extern volatile uint32_t ADCValue[ADC_NUM];
extern volatile uint32_t ADCIntDone;
uint32_t variable=0;


void initADC (int ADCNumber) {
	ADCInit(ADC_CLK);
	while(1)
	{
		ADCRead( 5 );
		//other code can be done here
		while ( !ADCIntDone );
		int variable = ADCValue[5];
		ADCIntDone = 0;
	}
}

//void initADC_george (int ADCNumber) {
//	switch (ADCNumber){
//	case(0):
//	  // Configure pins
//	  //   P0.23 as AD0.0
//	  LPC_PINCON ->PINSEL1 |= (1 << 14);
//
//	  // A/D Control Register
//	  //  1 in bit 0 - Select AD0.0 to be sampled
//	  //  0 in bits 15:8 - Don't divide clock
//	  //  0 in bit 16 - Disable burst mode
//	  //  1 in bit 21 - Not in power-down mode
//	  //  0 in bits 26:24 - don't start a conversion yet
//	  LPC_ADC ->ADCR = LEFT_BIT_SHIFT(1, 0) | LEFT_BIT_SHIFT(1,21);
//
//	  // A/D Interrupt Enable Register
//	  //  1 in bit 0 - Interrupt when conversion on ADC channel 0 completes
//	  LPC_ADC ->ADINTEN = LEFT_BIT_SHIFT(1,0);
//
//	  NVIC_EnableIRQ(ADC_IRQn);
//
//	  // Start conversion
//	  LPC_ADC ->ADCR |= LEFT_BIT_SHIFT(1,24);
//	break;
//	}
//}
