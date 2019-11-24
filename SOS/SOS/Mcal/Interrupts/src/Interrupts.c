/*
 * Interrupts.c
 *	Description : This file is for the Implementation of the Atmga32 Interrupts
 * Created: 10/26/2019 2:15:28 AM
 *  Author: ammarPC
 */ 

/************************************************************************/
/*                        Files Includes                                */
/************************************************************************/
#include "Interrupts.h"

/************************************************************************/
/*                        Defines and Type defines                      */
/************************************************************************/
/* defines for the External Interrupt Registers */
#define SREG  *((reg_type)0X5F)
#define GICR  *((reg_type)0X5B)
#define MCUCR *((reg_type)0X55)

/* Bit numbers */

/* SREG Reg */
#define GIE      7

/* MCUCR */
#define ISC11   3
#define ISC10   2
#define ISC01   1
#define ISC00   0


/************************************************************************/
/*                        Functions Definitions                         */
/************************************************************************/
/**
 * Function : Interrupts_On
 * Description : This function is used to turn On the global interrupt mask
 * Return : the function Returns nothing
 */

void Interrupts_On(void)
{     
	SET_BIT(SREG,GIE);
}

/**
 * Function : interrupts_Off
 * Description : This function is used to turn Off the global interrupt mask
 * Return : the function Returns nothing
 */
void interrupts_Off(void)
{    
	CLR_BIT(SREG,GIE);
}

/**
 * Function : Interrupts_ExtIntInit
 * Description : This function is used to initialize the External Interrupts
 * @pram  extInt  : the External Interrupt Number that the user want to initialize [INT0,INT1,INT2]
 * @pram  cfg     : the Configuration that the user want to configure the Interrupt to 
					ex: [LOW_LEVEL,ANY_CHANGE,FALLING_EDGE,RISING_EDGE]
					Note : INT2 only works in the edge mode [FALLING_EDGE,RISING_EDGE]
 * Return : the function Returns nothing
 */
void Interrupts_ExtInt_Init(uint8 extInt , uint8 cfg)
{	
	switch(extInt)
	{
		case INT0 : 
		switch(cfg)
		{
		
		case LOW_LEVEL :
		SET_BIT(GICR,INT0);
		CLR_BIT(MCUCR,ISC00);
		CLR_BIT(MCUCR,ISC01);
		break;
		
		case ANY_CHANGE :
		SET_BIT(GICR,INT0);
		SET_BIT(MCUCR,ISC00);
		CLR_BIT(MCUCR,ISC01);
		break;
		
		case FALLING_EDGE :
		SET_BIT(GICR,INT0);
		SET_BIT(MCUCR,ISC01);
		CLR_BIT(MCUCR,ISC00);
		break;
		
		case RISING_EDGE :
		SET_BIT(GICR,INT0);
		SET_BIT(MCUCR,ISC01);
		SET_BIT(MCUCR,ISC00);
		break;
		
		default:
		break;
		
		}
		
		break;
		
		case INT1 :
		switch(cfg)
		{
		
		case LOW_LEVEL :
		SET_BIT(GICR,INT1);
		CLR_BIT(MCUCR,ISC10);
		CLR_BIT(MCUCR,ISC11);
		break;
		
		case ANY_CHANGE :
		SET_BIT(GICR,INT1);
		SET_BIT(MCUCR,ISC10);
		CLR_BIT(MCUCR,ISC11);
		break;
		
		case FALLING_EDGE :
		SET_BIT(GICR,INT1);
		SET_BIT(MCUCR,ISC11);
		CLR_BIT(MCUCR,ISC10);
		break;
		
		case RISING_EDGE :
		SET_BIT(GICR,INT1);
		SET_BIT(MCUCR,ISC11);
		SET_BIT(MCUCR,ISC10);
		break;
		
		default:
		break;
		
		}
		break;
		
		case INT2 :
		SET_BIT(GICR,INT2);
		break;
		
		default: 
		break;
	}
}