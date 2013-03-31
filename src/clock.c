/*
 * clock.c
 *
 *  Created on: Mar 30, 2013
 *      Author: Matthew
 */
#include "LPC17xx.h"
#include "type.h"
#include "timer.h"
#include "clock.h"
#include "functions.h"

void setUpClkAsMainOscillatorNoDiv(void)
{
//BREAKING EVEYTHING!!!!!!!!!!!!!!!!!!
	//Selects the main oscillator as the PLL0 clock source.
	//setBit (LPC_SC->CLKSRCSEL, 0, HIGH);
	// = 0x1; //Picks main oscillator clock as PLL0 in
	//setBit (LPC_SC->PLL0CON, 0, LOW); //Muse be committed. Skips  PLL0

	LPC_SC->CLKSRCSEL = 0x1; //Picks main oscillator clock as PLL0 in

	LPC_SC->PLL0CON = 0x0; //Muse be committed. Skips  PLL0

	//COMMIT SEQUENCE PLL change
	LPC_SC->PLL0FEED = 0xAA; // set to 0xAA
	LPC_SC->PLL0FEED = 0x55; // set to 0x55

	// sets 0-7 bits of CCLKCFG to all be zero.
	SETBITS(LPC_SC->CCLKCFG, 0, 7, 0);
}

//Selects the Internal RC oscillator as the PLL0 clock source
void setUpClkAsInternal_RC_Ocillator_NoDiv(void)
{
	// Using the Internal RC Oscillator for a 4MHz signal and continue from there.
	    //SETBITS(LPC_SC->CLKSRCSEL,0,2,0x0);
	 // FIXME : Apperantly the IRC is 16MHz? at least that what my math shows.
	LPC_SC->CLKSRCSEL = 0x00; //Picks main oscillator clock as PLL0 in

	LPC_SC->PLL0CON = 0x0; //Muse be committed. Skips  PLL0
	//COMMIT SEQUENCE PLL change
	LPC_SC->PLL0FEED = 0xAA; // set to 0xAA
	LPC_SC->PLL0FEED = 0x55; // set to 0x55

	SETBITS(LPC_SC->CCLKCFG, 0, 7, 0); // sets 0-7 bits of CCLKCFG to all be zero.
}
