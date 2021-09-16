/*
 * led.c
 *
 *  Created: 10/21/2019 6:37:05 PM
 *  Author: Ammar Shahin
 */

/************************************************************************/
/*				              Files Includes                           */
/************************************************************************/
#include "Typedefs.h"
#include "Gpio.h"
#include "Led.h"
#include "Led_Cfg.h"

/*===========================Led Control Functions===============================*/

/**
 * Description: Initializing Function to the Led
 * @param led_Num the number of the Led [LED0,LED1,LED2,LED3]
 */
void Led_Init(led led_Num)
{
    switch (led_Num)
    {
    case LED0:
        Gpio_PinDirection(LED_PORT, LED0, SET_OUT);
        Gpio_PinWrite(LED_PORT, LED0, FALSE);
        break;
    case LED1:
        Gpio_PinDirection(LED_PORT, LED1, SET_OUT);
        Gpio_PinWrite(LED_PORT, LED1, FALSE);
        break;
    case LED2:
        Gpio_PinDirection(LED_PORT, LED2, SET_OUT);
        Gpio_PinWrite(LED_PORT, LED2, FALSE);
        break;
    case LED3:
        Gpio_PinDirection(LED_PORT, LED3, SET_OUT);
        Gpio_PinWrite(LED_PORT, LED3, FALSE);
        break;
    default:
        break;
    }
}

/**
 * Description: Function to set the Led to On
 * @param led_Num the number of the Led [LED0,LED1,LED2,LED3]
 */
void Led_On(led led_Num)
{
    switch (led_Num)
    {
    case LED0:
        Gpio_PinWrite(LED_PORT, LED0, HIGH);
        break;
    case LED1:
        Gpio_PinWrite(LED_PORT, LED1, HIGH);
        break;
    case LED2:
        Gpio_PinWrite(LED_PORT, LED2, HIGH);
        break;
    case LED3:
        Gpio_PinWrite(LED_PORT, LED3, HIGH);
        break;
    default:
        break;
    }
}

/**
 * Description: Function to set the Led to Off.
 * @param led_Num the number of the Led [LED0,LED1,LED2,LED3].
 */
void Led_Off(led led_Num)
{
    switch (led_Num)
    {
    case LED0:
        Gpio_PinWrite(LED_PORT, LED0, FALSE);
        break;
    case LED1:
        Gpio_PinWrite(LED_PORT, LED1, FALSE);
        break;
    case LED2:
        Gpio_PinWrite(LED_PORT, LED2, FALSE);
        break;
    case LED3:
        Gpio_PinWrite(LED_PORT, LED3, FALSE);
        break;
    default:
        break;
    }
}

/**
 * Description: Function to Toggle the Led.
 * @param led_Num the number of the Led [LED0,LED1,LED2,LED3]
 */
void Led_Tog(led led_Num)
{
    switch (led_Num)
    {
    case LED0:
        Gpio_PinToggle(LED_PORT, LED0);
        break;
    case LED1:
        Gpio_PinToggle(LED_PORT, LED1);
        break;
    case LED2:
        Gpio_PinToggle(LED_PORT, LED2);
        break;
    case LED3:
        Gpio_PinToggle(LED_PORT, LED3);
        break;
    default:
        break;
    }
}