/* LED Latching Switch (has debouncing)*/
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

int main(void)
{

  // Enable port B & C
  RCC->AHB1ENR |= (1 << 2);
  RCC->AHB1ENR |= (1 << 1);

  // Output setup for port C
  GPIOC->MODER |= (1 << 26);
  GPIOC->OTYPER &= ~(1 << 13);
  GPIOC->OSPEEDR |= (1 << 27);
  GPIOC->PUPDR &= ~( (1 << 27)|(1 << 26) );

  // Port B input setting
  GPIOB->MODER &= ~( (1 << 2)|(1 << 3) );
  GPIOB->PUPDR &= ~( (1 << 2)|(1 << 3) );

  GPIOC->BSRR |= (1 << 13);

  volatile char bp = 0;
  volatile char LEDstate = 0;

  while (1)
  {

	  if((GPIOB->IDR & (1 << 1)))
  	  {
  		  // Button is pressed
  		  bp = 1;

  	  }
  	  else
  	  {
  		  // If the button is pressed in previous iteration toggle LED on or off
  		  if(bp == 1)
  		  {
  			  if(LEDstate == 0)
  			  {
  				  // Toggling LED on
  				  LEDstate = 1;
  				  GPIOC->BSRR |= (1 << 29);

  			  }
  			  else
  			  {
  				  // Toggling LED off
  				  LEDstate = 0;
  				  GPIOC->BSRR |= (1 << 13);
  			  }
  		  }

  		  // Reset button press state to check if button is pressed again next time
  		  bp = 0;
  	  }

  }


}
