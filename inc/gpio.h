/*
 * gpio.h
 *
 *  Created on: Mar 30, 2013
 *      Author: Matthew
 */

#ifndef GPIO_H_
#define GPIO_H_

//0 is 0utput and 1 is 1nput
void pin0_gpio_init (int input, int pinNumber);

// Function to turn pin10 on
void pin0_gpio_set (int pinNumber, int setToValue);

void pin0_gpio_toggle (int pinNumber);

//0 is 0utput and 1 is 1nput
void pin2_gpio_init (int input, int pinNumber);

// Function to turn pin to setToValue
void pin2_gpio_set (int pinNumber, int setToValue);

void pin2_gpio_toggle (int pinNumber);




#endif /* GPIO_H_ */
