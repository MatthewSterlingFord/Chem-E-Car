/*
 * gpio.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Matthew
 */

#ifndef GPIO_H_
#define GPIO_H_

void pin0_gpio_toggle (int pinNumber);

//0 is 0utput and 1 is 1nput
void pin0_gpio_init (int input, int pinNumber);

void pin0_9_init (void);
// Function to turn LED2 on
void pin0_9_on (void);

// Function to turn LED2 off
void pin0_9_off (void);

void pin0_10_init (void);

// Function to turn pin10 on
void pin0_10_on (void);

// Function to turn pin10 off
void pin0_10_off (void);

#endif /* GPIO_H_ */
