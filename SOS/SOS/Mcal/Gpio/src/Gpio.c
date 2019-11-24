/*
 * Gpio.c
 *  Description : This file is to control the Gpio module in the MCAL Layer
 * Created: 10/21/2019 3:00:30 PM
 *  Author: Ammar Shahin
 */ 

/************************************************************************/
/*				 		       Files Includes                           */
/************************************************************************/
#include "Gpio.h"

/************************************************************************/
/*				    Privet defines and macros                           */
/************************************************************************/

/********* Memory GPIO Register Maping *************/
#define PORT_A  *((reg_type)0X3B)
#define DDR_A   *((reg_type)0X3A)
#define PIN_A   *((reg_type)0X39)
#define PORT_B  *((reg_type)0X38)
#define DDR_B   *((reg_type)0X37)
#define PIN_B   *((reg_type)0X36)
#define PORT_C  *((reg_type)0X35)
#define DDR_C   *((reg_type)0X34)
#define PIN_C   *((reg_type)0X33)
#define PORT_D  *((reg_type)0X32)
#define DDR_D   *((reg_type)0X31)
#define PIN_D   *((reg_type)0X30)

/************************************************************************/
/*				      GPIO functions' Definitions                       */
/************************************************************************/

/*===========================PORT Control===============================*/
/**
 * Description: This Function is used to initialize the direction of the port Selected
 * @param port : the port {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param direction : The Direction of the Port >> {SET_IN , SET_OUT}
 * Return : void
 */
void Gpio_PortDirection(uint8 port, uint8 direction)
{
	switch(port)
	{
		case MYPORTA : 
						DDR_A = direction;
						break;
		case MYPORTB :
						DDR_B = direction;
						break;
		case MYPORTC :
						DDR_C = direction;
						break;
		case MYPORTD :
						DDR_D = direction;
						break;	
	}
}

/**
 * Description: This Function is used to Write a value to the port Selected
 * @param port : the port {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param value : The value of the Port
 * Return : void
 */
void Gpio_PortWrite(uint8 port, uint8 value)
{
	switch(port)
	{
		case MYPORTA :
			PORT_A = value;
			break;
		case MYPORTB :
			PORT_B = value;
			break;
		case MYPORTC :
			PORT_C = value;
			break;
		case MYPORTD :
			PORT_D = value;
			break;
	}
}

/**
 * Description: This Function is used to Toggle the value of the port Selected
 * @param port : the port {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * Return : void
 */
void Gpio_PortToggle(uint8 port)
{
	switch(port)
	{
		case MYPORTA :
		PORT_A ^= 0xff;
		break;
		case MYPORTB :
		PORT_B ^= 0xff;
		break;
		case MYPORTC :
		PORT_C ^= 0xff;
		break;
		case MYPORTD :
		PORT_D ^= 0xff;
		break;
	}
}

/**
 * Description: This Function is used to Read the value of the port Selected
 * @param port : the port {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * Return : the value read by the function
 */
uint8 Gpio_PortRead(uint8 port)
{
	uint8 result = 0;
	switch(port)
	{
		case MYPORTA :
		result =  PIN_A;
		break;
		case MYPORTB :
		result = PIN_B;
		break;
		case MYPORTC :
		result = PIN_C;
		break;
		case MYPORTD :
		result = PIN_D;
		break;
	}
	return result;
}

/*===========================PIN Control===============================*/
/**
 * Description: This Function is used to initialize the direction of the pin Selected
 * @param port : the port that includes the pin {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param pins : the pin Number {BIT0,BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7}
 * @param direction : The Direction of the PIN >> {SET_IN , SET_OUT}
 * Return : void
 */
void Gpio_PinDirection(uint8 port, uint8 pins, uint8 direction)
{
	switch(port)
	{
		case MYPORTA :
		{
		switch(direction)
		{
		case SET_IN : 
		DDR_A &= ~(pins);
		break;
		case SET_OUT : 
		DDR_A |= (pins);
		break;
		}
		}
		break;
		
		case MYPORTB :
		{
		switch(direction)
		{
		case SET_IN :
			DDR_B &= ~(pins);
			break;
		case SET_OUT :
			DDR_B |= (pins);
			break;
		}
		}
		break;
		case MYPORTC :
		{
			switch(direction)
			{
				case SET_IN :
				DDR_C &= ~(pins);
				break;
				case SET_OUT :
				DDR_C |= (pins);
				break;
			}
		}
		break;
		case MYPORTD :
		{
			switch(direction)
			{
				case SET_IN :
				DDR_D &= ~(pins);
				break;
				case SET_OUT :
				DDR_D |= (pins);
				break;
			}
		}
		break;
	}
}

/**
 * Description: This Function is used to Write a value of the pin Selected
 * @param port : the port that includes the pin {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param pins : the pin Number {BIT0,BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7}
 * @param value : The value of the PIN >> {HIGH , LOW}
 * Return : void
 */
void Gpio_PinWrite(uint8 port, uint8 pins, uint8 value)
{
	switch(value)
	{
		case HIGH:
			switch(port)
			{
					case MYPORTA :
						PORT_A |= (pins);
						break;
					case MYPORTB :
						PORT_B |= (pins);
						break;
					case MYPORTC :
						PORT_C |= (pins);
						break;
					case MYPORTD :
						PORT_D |= (pins);
						break;
		}
		break;
		
		case LOW : 
		switch(port)
		{
			case MYPORTA :
			PORT_A &= ~(pins);
			break;
			case MYPORTB :
			PORT_B &= ~(pins);
			break;
			case MYPORTC :
			PORT_C &= ~(pins);
			break;
			case MYPORTD :
			PORT_D &= ~(pins);
			break;
		}
		break;	
	}
}

/**
 * Description: This Function is used to Toggle a value of the pin Selected
 * @param port : the port that includes the pin {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param pins : the pin Number {BIT0,BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7}
 * Return : void
 */
void Gpio_PinToggle(uint8 port, uint8 pins)
{
	switch(port)
	{
		case MYPORTA :
		PORT_A ^= (pins);
		break;
		case MYPORTB :
		PORT_B ^= (pins);
		break;
		case MYPORTC :
		PORT_C ^= (pins);
		break;
		case MYPORTD :
		PORT_D ^= (pins);
		break;
	}
}
/**
 * Description: This Function is used to Read the value of the pin Selected
 * @param port : the port that includes the pin {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param pins : the pin Number {BIT0,BIT1,BIT2,BIT3,BIT4,BIT5,BIT6,BIT7}
 * Return : the value Read by the function 
 */
uint8 Gpio_PinRead(uint8 port, uint8 pin)
{
	uint8 result = 0;
	switch(port)
	{
		case MYPORTA :
		result = ((PIN_A >> pin) & 0x01);
		break;
		case MYPORTB :
		result = ((PIN_B >> pin) & 0x01);
		break;
		case MYPORTC :
		result = ((PIN_C >> pin) & 0x01);
		break;
		case MYPORTD :
		result = ((PIN_D >> pin) & 0x01);
		break;
	}
	return result;
}
/*===========================Upper Nibble Control===============================*/
/**
 * Description: This Function is used to initialize the direction of the UpperNibble
 * @param port : the port that includes the UpperNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param direction : The Direction of the UpperNibble >> {SET_IN , SET_OUT}
 * Return : void
 */
void Gpio_UpperNibbleDirection(uint8 port, uint8 direction)
{
	switch(port)
	{
		case MYPORTA :
		{
			switch(direction)
			{
				case SET_IN :
				DDR_A &= 0x0f;
				break;
				case SET_OUT :
				DDR_A |= 0xf0;
				break;
			}
		}
		break;
		case MYPORTB :
		{
			switch(direction)
			{
				case SET_IN :
				DDR_B &= 0x0f;
				break;
				case SET_OUT :
				DDR_B |= 0xf0;
				break;
			}
		}
		break;
		case MYPORTC :
		{
			switch(direction)
			{
				case SET_IN :
				DDR_C &= 0x0f;
				break;
				case SET_OUT :
				DDR_C |= 0xf0;
				break;
			}
		}
		break;
		case MYPORTD :
		{
			switch(direction)
			{
				case SET_IN :
				DDR_D &= 0x0f;
				break;
				case SET_OUT :
				DDR_D |= 0xf0;
				break;
			}
		}
		break;
	}
}

/**
 * Description: This Function is used to Write a value of the UpperNibble Selected
 * @param port : the port that includes the UpperNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param value : The value of the UpperNibble
 * Return : void
 */
void Gpio_UpperNibbleWrite(uint8 port, uint8 value)
{
	switch(port)
	{
		case MYPORTA :
		PORT_A = ((PORT_A & 0x0f) | (value << 4));
		break;
		case MYPORTB :
		PORT_B = ((PORT_B & 0x0f) | (value << 4));
		break;
		case MYPORTC :
		PORT_C = ((PORT_C & 0x0f) | (value << 4));
		break;
		case MYPORTD :
		PORT_D = ((PORT_D & 0x0f) | (value << 4));
		break;
	}
}

/**
 * Description: This Function is used to Toggle a value of the UpperNibble Selected
 * @param port : the port that includes the UpperNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * Return : void
 */
void Gpio_UpperNibbleToggle(uint8 port)
{
	switch(port)
	{
		case MYPORTA :
		PORT_A ^= 0xf0;
		break;
		case MYPORTB :
		PORT_B ^= 0xf0;
		break;
		case MYPORTC :
		PORT_C ^= 0xf0;
		break;
		case MYPORTD :
		PORT_D ^= 0xf0;
		break;
	}
}

/**
 * Description: This Function is used to Read the value of the UpperNibble Selected
 * @param port : the port that includes the UpperNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * Return : the value Read by the function 
 */
uint8 Gpio_UpperNibbleRead(uint8 port)
{
	uint8 result = 0;
	switch(port)
	{
		case MYPORTA :
		result = (PIN_A >> 4);
		break;
		case MYPORTB :
		result = (PIN_B >> 4);
		break;
		case MYPORTC :
		result = (PIN_C >> 4);
		break;
		case MYPORTD :
		result = (PIN_D >> 4);
		break;
	}
	return result;
}

/*===========================Lower Nibble Control===============================*/
/**
 * Description: This Function is used to initialize the direction of the LowerNibble
 * @param port : the port that includes the LowerNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param direction : The Direction of the LowerNibble >> {SET_IN , SET_OUT}
 * Return : void
 */
void Gpio_LowerNibbleDirection(uint8 port, uint8 direction)
{
	switch(port)
	{
		case MYPORTA :
		{
			switch(direction)
			{
				case SET_IN :
				DDR_A &= 0xf0;
				break;
				case SET_OUT :
				DDR_A |= 0x0f;
				break;
			}
		}
		break;
		case MYPORTB :
		{
			switch(direction)
			{
				case SET_IN :
				DDR_B &= 0xf0;
				break;
				case SET_OUT :
				DDR_B |= 0x0f;
				break;
			}
		}
		break;
		case MYPORTC :
		{
			switch(direction)
			{
				case SET_IN :
				DDR_C &= 0xf0;
				break;
				case SET_OUT :
				DDR_C |= 0x0f;
				break;
			}
		}
		break;
		case MYPORTD :
		{
			switch(direction)
			{
				case SET_IN :
				DDR_D &= 0xf0;
				break;
				case SET_OUT :
				DDR_D |= 0x0f;
				break;
			}
		}
		break;
	}
}

/**
 * Description: This Function is used to Write a value of the LowerNibble Selected
 * @param port : the port that includes the LowerNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * @param value : The value of the LowerNibble
 * Return : void
 */
void Gpio_LowerNibbleWrite(uint8 port, uint8 value)
{
	switch(port)
	{
		case MYPORTA :
		PORT_A = (PORT_A & 0xf0) | (value & 0x0f);
		break;
		case MYPORTB :
		PORT_B = (PORT_B & 0xf0) | (value & 0x0f);
		break;
		case MYPORTC :
		PORT_C = (PORT_C & 0xf0) | (value & 0x0f);
		break;
		case MYPORTD :
		PORT_D = (PORT_D & 0xf0) | (value & 0x0f);
		break;
	}
}

/**
 * Description: This Function is used to Toggle a value of the LowerNibble Selected
 * @param port : the port that includes the LowerNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * Return : void
 */
void Gpio_LowerNibbleToggle(uint8 port)
{
	switch(port)
	{
		case MYPORTA :
		PORT_A ^= 0x0f;
		break;
		case MYPORTB :
		PORT_B ^= 0x0f;
		break;
		case MYPORTC :
		PORT_C ^= 0x0f;
		break;
		case MYPORTD :
		PORT_D ^= 0x0f;
		break;
	}
}

/**
 * Description: This Function is used to Read the value of the LowerNibble Selected
 * @param port : the port that includes the LowerNibble {MYPORTA,MYPORTB,MYPORTC,MYPORTD}
 * Return : the value read by the function 
 */
uint8 Gpio_LowerNibbleRead(uint8 port)
{
	uint8 result = 0;
	switch(port)
	{
		case MYPORTA :
		result = (PIN_A & 0x0f);
		break;
		case MYPORTB :
		result = (PIN_B & 0x0f);
		break;
		case MYPORTC :
		result = (PIN_C & 0x0f);
		break;
		case MYPORTD :
		result = (PIN_D & 0x0f);
		break;
	}
	return result;
}
