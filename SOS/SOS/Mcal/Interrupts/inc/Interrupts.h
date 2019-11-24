/*
 * Interrupts.h
 *	Description : This file is for the Implementation of the Atmga32 Interrupts
 * Created: 10/26/2019 2:15:28 AM
 *  Author: ammarPC
 */ 


#ifndef INTERRUPT_LIB_H_
#define INTERRUPT_LIB_H_

/************************************************************************/
/*                        Files Includes                                */
/************************************************************************/
#include "BitMasking_Macros.h"
#include "Typedefs.h"


/************************************************************************/
/*                        Defines and Type defines                      */
/************************************************************************/

/* External Interrupts Config */
#define LOW_LEVEL 0
#define ANY_CHANGE 1
#define FALLING_EDGE 2
#define RISING_EDGE 3

/* Bit numbers */

/* GICR */
#define INT1    7
#define INT0    6
#define INT2    5

/* defines for the interrupt handler */				
#define _VECTOR(n)  __vector_##n  

/* Interrupt vectors */

/* External Interrupt Request 0 */
#define INT0_vect_num		1
#define INT0_vect			_VECTOR(1)
#define SIG_INTERRUPT0			_VECTOR(1)

/* External Interrupt Request 1 */
#define INT1_vect_num		2
#define INT1_vect			_VECTOR(2)
#define SIG_INTERRUPT1			_VECTOR(2)

/* External Interrupt Request 2 */
#define INT2_vect_num		3
#define INT2_vect			_VECTOR(3)
#define SIG_INTERRUPT2			_VECTOR(3)

/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_vect_num	4
#define TIMER2_COMP_vect		_VECTOR(4)
#define SIG_OUTPUT_COMPARE2		_VECTOR(4)

/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vect_num		5
#define TIMER2_OVF_vect			_VECTOR(5)
#define SIG_OVERFLOW2			_VECTOR(5)

/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_vect_num	6
#define TIMER1_CAPT_vect		_VECTOR(6)
#define SIG_INPUT_CAPTURE1		_VECTOR(6)

/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_vect_num	7
#define TIMER1_COMPA_vect		_VECTOR(7)
#define SIG_OUTPUT_COMPARE1A		_VECTOR(7)

/* Timer/Counter1 Compare Match B */
#define TIMER1_COMPB_vect_num	8
#define TIMER1_COMPB_vect		_VECTOR(8)
#define SIG_OUTPUT_COMPARE1B		_VECTOR(8)

/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect_num		9
#define TIMER1_OVF_vect			_VECTOR(9)
#define SIG_OVERFLOW1			_VECTOR(9)

/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_vect_num	10
#define TIMER0_COMP_vect		_VECTOR(10)
#define SIG_OUTPUT_COMPARE0		_VECTOR(10)

/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect_num		11
#define TIMER0_OVF_vect			_VECTOR(11)
#define SIG_OVERFLOW0			_VECTOR(11)

/* Serial Transfer Complete */
#define SPI_STC_vect_num		12
#define SPI_STC_vect			_VECTOR(12)
#define SIG_SPI				_VECTOR(12)

/* USART, Rx Complete */
#define USART_RXC_vect_num		13
#define USART_RXC_vect			_VECTOR(13)
#define SIG_USART_RECV			_VECTOR(13)
#define SIG_UART_RECV			_VECTOR(13)

/* USART Data Register Empty */
#define USART_UDRE_vect_num		14
#define USART_UDRE_vect			_VECTOR(14)
#define SIG_USART_DATA			_VECTOR(14)
#define SIG_UART_DATA			_VECTOR(14)

/* USART, Tx Complete */
#define USART_TXC_vect_num		15
#define USART_TXC_vect			_VECTOR(15)
#define SIG_USART_TRANS			_VECTOR(15)
#define SIG_UART_TRANS			_VECTOR(15)

/* ADC Conversion Complete */
#define ADC_vect_num		16
#define ADC_vect			_VECTOR(16)
#define SIG_ADC				_VECTOR(16)

/* EEPROM Ready */
#define EE_RDY_vect_num		17
#define EE_RDY_vect			_VECTOR(17)
#define SIG_EEPROM_READY		_VECTOR(17)

/* Analog Comparator */
#define ANA_COMP_vect_num		18
#define ANA_COMP_vect			_VECTOR(18)
#define SIG_COMPARATOR			_VECTOR(18)

/* 2-wire Serial Interface */
#define TWI_vect_num		19
#define TWI_vect			_VECTOR(19)
#define SIG_2WIRE_SERIAL		_VECTOR(19)

/* Store Program Memory Ready */
#define SPM_RDY_vect_num		20
#define SPM_RDY_vect			_VECTOR(20)
#define SIG_SPM_READY			_VECTOR(20)


#define __INTR_ATTRS used, externally_visible

#define ISR_T(vector, ...)            \
void vector (void) __attribute__ ((signal,__INTR_ATTRS)) __VA_ARGS__; \
void vector (void)


/************************************************************************/
/*                        Functions Prototypes                          */
/************************************************************************/

/**
 * Function : Interrupts_On
 * Description : This function is used to turn On the global interrupt mask
 * Return : the function Returns nothing
 */
void Interrupts_On(void);

/**
 * Function : interrupts_Off
 * Description : This function is used to turn Off the global interrupt mask
 * Return : the function Returns nothing
 */
void interrupts_Off(void);

/**
 * Function : Interrupts_ExtIntInit
 * Description : This function is used to initialize the External Interrupts
 * @pram  extInt  : is the External Interrupt Number that the user want to initialize [INT0,INT1,INT2]
 * @pram  cfg     : is the Configuration that the user want to configure the Interrupt to 
					ex: [LOW_LEVEL,ANY_CHANGE,FALLING_EDGE,RISING_EDGE]
					Note : INT2 only works in the edge mode [FALLING_EDGE,RISING_EDGE]
 * Return : the function Returns nothing
 */
void Interrupts_ExtInt_Init(uint8 extInt , uint8 cfg);


#endif /* INTERRUPT_LIB_H_ */