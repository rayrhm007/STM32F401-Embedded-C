/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "main.h"

void Delay(int volatile count)
{
	while(count != 0)
	{
		count--;
	}

}

int main(void)
{
	// Enable AHB for port C
	RCC->AHB1ENR |= (1 << 2);	//shift a 1 at bit position 2

	// Mode: general purpose output
	GPIOC->MODER |= (1 << 26);

	// Output type: push-pull
	GPIOC->OTYPER &= ~(1 << 13);

	// Output speed: high
	GPIOC->OSPEEDR |= (1 << 27);

	// Pullup-pulldown registers: disabled
	GPIOC->PUPDR &= ~( (1 << 27)|(1 << 26) );

	while (1)
	{
		// Bit set reset register
		GPIOC->BSRR |= (1 << 13);

		Delay(1000000);

		// Turn LED on (assert low LED)
		GPIOC->BSRR |= (1 << (13+16));

		Delay(1000000);
	}

}
