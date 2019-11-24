/*
 * Led_Cfg.h
 *
 * Created: 10/21/2019 6:38:15 PM
 *  Author: Ammar Shahin 
 */ 


#ifndef _PINCONFIG_H_
#define _PINCONFIG_H_
/************************************************************************/
/*                         INCLUDES                                      */
/************************************************************************/
#include "Gpio.h"

/************************************************************************/
/*          Define the ports and pins where the leds are connected      */
/************************************************************************/
#define LED_PORT MYPORTB   

/************************************************************************/
/*               Define the LEDs on the Kit as enum                     */
/************************************************************************/
typedef enum{
	LED0 = BIT4,
	LED1 = BIT5,
	LED2 = BIT6,
	LED3 = BIT7,
} led;


#endif /* _PINCONFIG_H_ */