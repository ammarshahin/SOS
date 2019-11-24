/*
 * Gpio.h
 *  Description : This file is to control the Gpio module in the MCAL Layer
 * Created: 10/21/2019 3:00:30 PM
 *  Author: Ammar Shahin
 */ 


#ifndef T_GPIO_H_
#define T_GPIO_H_

/************************************************************************/
/*				 		       Files Includes                           */
/************************************************************************/
#include "Typedefs.h"
#include "MCU_Frequency.h"

/************************************************************************/
/*				 		defining the PORTS Numbers                      */
/************************************************************************/

/********* Main Gpio Ports *************/
#define MYPORTA  0
#define MYPORTB  1
#define MYPORTC  2
#define MYPORTD  3



/************************************************************************/
/*				 Enum for defining bit numbers                          */
/************************************************************************/
typedef enum EN_bits
{
	BIT0 = 0x01,	// defines BIT0 in a register
	BIT1 = 0x02,	// defines BIT1 in a register
	BIT2 = 0x04,	// defines BIT2 in a register
	BIT3 = 0x08,	// defines BIT3 in a register
	BIT4 = 0x10,	// defines BIT4 in a register
	BIT5 = 0x20,	// defines BIT5 in a register
	BIT6 = 0x40,	// defines BIT6 in a register
	BIT7 = 0x80,	// defines BIT7 in a register
}EN_bits;


/************************************************************************/
/*				 Enum for defining PIN numbers                          */
/************************************************************************/
typedef enum EN_PINS
{
	PIN0 = 0,	// defines BIT0 in a register
	PIN1 = 1,	// defines BIT1 in a register
	PIN2 = 2,	// defines BIT2 in a register
	PIN3 = 3,	// defines BIT3 in a register
	PIN4 = 4,	// defines BIT4 in a register
	PIN5 = 5,	// defines BIT5 in a register
	PIN6 = 6,	// defines BIT6 in a register
	PIN7 = 7,	// defines BIT7 in a register
}EN_PINS;


/************************************************************************/
/*						 LOW/HIGH defines                               */
/************************************************************************/
#define LOW  0	// defines LOW value for a bit
#define HIGH 1	// defines HIGH value for a bit

/************************************************************************/
/*                       ENUM to set the Direction                      */
/************************************************************************/

typedef enum{
	SET_IN = 0x00,
	SET_OUT = 0xff,
}En_Dir;

/************************************************************************/
/*				 GPIO functions' prototypes	                            */
/************************************************************************/

/*===========================PORT Control===============================*/
/**
 * Description: This Function is used to initialize the direction of the port Selected
 * @param port : the port {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param direction : The Direction of the Port >> {SET_IN , SET_OUT}
 * Return : void
 */
void Gpio_PortDirection(uint8 port, uint8 direction);

/**
 * Description: This Function is used to Write a value to the port Selected
 * @param port : the port {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param value : The value of the Port
 * Return : void
 */
void Gpio_PortWrite(uint8 port, uint8 value);

/**
 * Description: This Function is used to Toggle the value of the port Selected
 * @param port : the port {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * Return : void
 */
void Gpio_PortToggle(uint8 port);

/**
 * Description: This Function is used to Read the value of the port Selected
 * @param port : the port {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * Return : the value read by the function
 */
uint8 Gpio_PortRead(uint8 port);

/*===========================PIN Control===============================*/
/**
 * Description: This Function is used to initialize the direction of the pin Selected
 * @param port : the port that includes the pin {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param pins : the pin Number {BIT0,BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7}
 * @param direction : The Direction of the PIN >> {SET_IN , SET_OUT}
 * Return : void
 */
void Gpio_PinDirection(uint8 port, uint8 pins, uint8 direction);

/**
 * Description: This Function is used to Write a value of the pin Selected
 * @param port : the port that includes the pin {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param pins : the pin Number {BIT0,BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7}
 * @param value : The value of the PIN >> {HIGH , LOW}
 * Return : void
 */
void Gpio_PinWrite(uint8 port, uint8 pins, uint8 value);

/**
 * Description: This Function is used to Toggle a value of the pin Selected
 * @param port : the port that includes the pin {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param pins : the pin Number {BIT0,BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7}
 * Return : void
 */
void Gpio_PinToggle(uint8 port, uint8 pins);

/**
 * Description: This Function is used to Read the value of the pin Selected
 * @param port : the port that includes the pin {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param pins : the pin Number {BIT0,BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7}
 * Return : the value Read by the function 
 */
uint8 Gpio_PinRead(uint8 port, uint8 pin);

/*===========================Upper Nibble Control===============================*/
/**
 * Description: This Function is used to initialize the direction of the UpperNibble
 * @param port : the port that includes the UpperNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param direction : The Direction of the UpperNibble >> {SET_IN , SET_OUT}
 * Return : void
 */
void Gpio_UpperNibbleDirection(uint8 port, uint8 direction);

/**
 * Description: This Function is used to Write a value of the UpperNibble Selected
 * @param port : the port that includes the UpperNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param value : The value of the UpperNibble
 * Return : void
 */
void Gpio_UpperNibbleWrite(uint8 port, uint8 value);

/**
 * Description: This Function is used to Toggle a value of the UpperNibble Selected
 * @param port : the port that includes the UpperNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * Return : void
 */
void Gpio_UpperNibbleToggle(uint8 port);

/**
 * Description: This Function is used to Read the value of the UpperNibble Selected
 * @param port : the port that includes the UpperNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * Return : the value Read by the function 
 */
uint8 Gpio_UpperNibbleRead(uint8 port);

/*===========================Lower Nibble Control===============================*/
/**
 * Description: This Function is used to initialize the direction of the LowerNibble
 * @param port : the port that includes the LowerNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param direction : The Direction of the LowerNibble >> {SET_IN , SET_OUT}
 * Return : void
 */
void Gpio_LowerNibbleDirection(uint8 port, uint8 direction);

/**
 * Description: This Function is used to Write a value of the LowerNibble Selected
 * @param port : the port that includes the LowerNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param value : The value of the LowerNibble
 * Return : void
 */
void Gpio_LowerNibbleWrite(uint8 port, uint8 value);

/**
 * Description: This Function is used to Toggle a value of the LowerNibble Selected
 * @param port : the port that includes the LowerNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * Return : void
 */
void Gpio_LowerNibbleToggle(uint8 port);

/**
 * Description: This Function is used to Read the value of the LowerNibble Selected
 * @param port : the port that includes the LowerNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * Return : the value read by the function 
 */
uint8 Gpio_LowerNibbleRead(uint8 port);


#endif /* T_GPIO_H_ */