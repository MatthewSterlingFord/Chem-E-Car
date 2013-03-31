/*
 * functions.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Matthew
 */

#ifndef FUNCTIONS_H_
#define FUNCTIONS_H_

// Some macros to speed bit twiddling
#define BITON(var,bit) var |= (1 << bit)
#define BITOFF(var,bit) var &= ~(1 << bit)

// MASK(3,4) = 0x78
#define MASK(start,len) (~(~0 << (len)) << start)
#define INVMASK(start,len) (~MASK(start,len))

// SETBITS assumes the variable is r/w capable
#define SETBITS(var,start,len,val) var = (((var) & INVMASK(start,len)) | (((val) << start) & MASK(start,len)))

// Everything not in range is set to 0 (possibly painful if you overwrite lesser bits)
#define SETBITS0(var,start,len,val) var = ((val) << start) & MASK(start,len)

void setBit (int var, int bit, int value);

#endif /* FUNCTIONS_H_ */
