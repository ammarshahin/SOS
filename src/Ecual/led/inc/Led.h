/*
 *  Led.h
 *	Description : This file is used to control the Leds.
 *  Created: 10/21/2019 11:08:54 PM
 *  Author: Ammar Shahin
 */

#ifndef LED_H_
#define LED_H_

/************************************************************************/
/*				              Files Includes                           */
/************************************************************************/
#include "Led_Cfg.h"

/************************************************************************/
/*				          Functions Prototype                           */
/************************************************************************/

/*===========================Led_Init Function===============================*/
/**
 * Description: This function is used to initialize the led on the Kit.
 * @param led_Num is a variable of the user defined data type led to indicate which led to be initialized. 
 */
void Led_Init(led led_Num);

/*===========================Led_On Function===============================*/
/**
 * Description: This function is used to turn on the led on the Kit.
 * @param led_Num is a variable of the user defined data type led to indicate which led to be turned On. 
 */
void Led_On(led led_Num);

/*===========================Led_Off Function===============================*/
/**
 * Description: This function is used to turn off the led on the Kit.
 * @param led_Num is a variable of the user defined data type led to indicate which led to be turned Off. 
 */
void Led_Off(led led_Num);

/*===========================Led_Tog Function===============================*/
/**
 * Description: This function is used to toggle the led on the Kit.
 * @param led_Num is a variable of the user defined data type led to indicate which led to be toggled. 
 */
void Led_Tog(led led_Num);

#endif /* LED_H_ */