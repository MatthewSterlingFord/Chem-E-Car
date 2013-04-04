#include "LPC17xx.h"
#include "sevenseg.h"
#include "type.h"
#include "sc_timer.h"

void short_delay (int n) __attribute__((noinline));
void short_delay(int n){
volatile int d, f;
for (d=0; d<n*3000; d++)
	f++;
}

void display(int numberToDisplay, int point){
//	// Clock pin high
//	int i = 0;
//	for(i = 0; i < 8; i++){
//		LPC_GPIO2->FIOCLR |= (1 << SEVEN_SEG_CLOCK_1);
//		decode(i, numberToDisplay, point);
//		LPC_GPIO2->FIOSET |= (1 << SEVEN_SEG_CLOCK_1);
//		//short_delay(800);
//	}
//	LPC_GPIO2->FIOSET |= (1 << SEVEN_SEG_LATCH_1);
//	short_delay(800);// Latch pin Low
//	LPC_GPIO2->FIOCLR |= (1 << SEVEN_SEG_LATCH_1);
//	//short_delay(800);// Latch pin Low
//	//LPC_GPIO2->FIOSET |= (1 << SEVEN_SEG_LATCH_1);
//	//short_delay(800);// Latch pin Low
//	//LPC_GPIO2->FIOCLR |= (1 << SEVEN_SEG_LATCH_1);
}



void decode(int segment, int numberToDisplay, int point){
//	switch(segment){
//	case(0):
//		switch(numberToDisplay){
//		case(1):
//		case(4):
//			LPC_GPIO2->FIOSET |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		default:
//			LPC_GPIO2->FIOCLR |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		}
//	break;
//	case(1):
//		switch(numberToDisplay){
//		case(5):
//		case(6):
//			LPC_GPIO2->FIOSET |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		default:
//			LPC_GPIO2->FIOCLR |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		}
//		break;
//	case(2):
//		switch(numberToDisplay){
//		case(2):
//			LPC_GPIO2->FIOSET |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		default:
//			LPC_GPIO2->FIOCLR |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		}
//		break;
//	case(3):
//		switch(numberToDisplay){
//		case(1):
//		case(4):
//		case(7):
//			LPC_GPIO2->FIOSET |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		default:
//			LPC_GPIO2->FIOCLR |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		}
//		break;
//	case(4):
//		switch(numberToDisplay){
//		case(1):
//		case(3):
//		case(4):
//		case(5):
//		case(7):
//		case(9):
//			LPC_GPIO2->FIOSET |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		default:
//			LPC_GPIO2->FIOCLR |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		}
//		break;
//	case(5):
//		switch(numberToDisplay){
//		case(1):
//		case(2):
//		case(3):
//		case(7):
//			LPC_GPIO2->FIOSET |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		default:
//			LPC_GPIO2->FIOCLR |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		}
//		break;
//	case(6):
//		switch(numberToDisplay){
//		case(0):
//		case(1):
//		case(7):
//			LPC_GPIO2->FIOSET |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		default:
//			LPC_GPIO2->FIOCLR |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//			break;
//		}
//		break;
//	case(7):
//		if(point)
//			LPC_GPIO2->FIOCLR |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//		else
//			LPC_GPIO2->FIOSET |= ( 1 << SEVEN_SEG_DATA_INPUT_1);
//	break;
//	}
}
