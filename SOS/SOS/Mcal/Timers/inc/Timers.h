/*
 * timers.h
 * Description : This File is used to control the Timer Peripherals in the MCAL layer
 * Created: 10/22/2019 2:04:16 PM
 *  Author: Ammar Shahin
 */ 


#ifndef TIMERS_H_
#define TIMERS_H_

/************************************************************************/
/*                            Files Includes                            */
/************************************************************************/
#include "Timers_Lcfg.h"


/************************************************************************/
/*                     Timers' Registers                                */
/************************************************************************/
#define TIMSK  *((reg_type)0x59)
#define TIFR   *((reg_type)0x58)
#define TWCR   *((reg_type)0x56)
#define TCCR0  *((reg_type)0x53)
#define TCNT0  *((reg_type)0x52)
#define TCCR1A *((reg_type)0x4f)
#define TCCR1B *((reg_type)0x4e)
#define TCNT1H *((reg_type)0x4d)
#define TCNT1L *((reg_type)0x4c)
#define OCR1AH *((reg_type)0x4b)
#define OCR1AL *((reg_type)0x4a)
#define OCR1BH *((reg_type)0x49)
#define OCR1BL *((reg_type)0x48)
#define ICR1H  *((reg_type)0x47)
#define ICR1L  *((reg_type)0x46)
#define TCCR2  *((reg_type)0x45)
#define TCNT2  *((reg_type)0x44)
#define OCR2   *((reg_type)0x43)
#define OCR0   *((reg_type)0x5C)

/************************************************************************/
/*                     Defines and Macros                               */
/************************************************************************/
#define TIMER0_MAX_COUNT 256
#define TIMER1_MAX_COUNT 65536
#define TIMER2_MAX_COUNT 256

#define SECONDS_TO_NANOSECONSD_FACTOR  1000000000
#define SECONDS_TO_MICROSECONSD_FACTOR 1000000
#define SECONDS_TO_MILLISECONSD_FACTOR 1000
#define MILLISECONSD_TO_MICROSECONSD_FACTOR 1000
#define DUTY_CYCLE_PERCENTAGE_FACTOR   100


#define SECONDS_TO_SETCOUNTER 1000000

#define TIFR_TOV0_gEnumBcm_Tx_Flag_MASK 0x01
#define TIFR_TOV1_gEnumBcm_Tx_Flag_MASK 0x04
#define TIFR_TOV2_gEnumBcm_Tx_Flag_MASK 0x40

#define SWPWM_0_FREQ 40000UL 
#define SWPWM_0_PORT MYPORTA
#define SWPWM_0_PIN  BIT0

#define SWPWM_1_FREQ 100UL
#define SWPWM_1_PORT MYPORTB
#define SWPWM_1_PIN  BIT6

#define SWPWM_2_FREQ 1UL
#define SWPWM_2_PORT MYPORTB
#define SWPWM_2_PIN  BIT4



/* for timer 0 */
typedef enum {
	T0_NORMAL_MODE=0x00,
	T0_PWM_MODE=0x40,
	T0_COMP_MODE=0x08,
	T0_FastPWM_MODE=0x48
}T0_MODE;

typedef enum {
	T0_OC0_DIS=0x00,
	T0_OC0_TOGGLE=0x10,
	T0_OC0_CLEAR=0x20,
	T0_OC0_SET=0x30,
}T0_COM;

typedef enum {
	T0_NO_CLOCK=0,
	T0_PRESCALER_1=0x01,
	T0_PRESCALER_8=0x02,
	T0_PRESCALER_64=0x03,
	T0_PRESCALER_256=0x04,
	T0_PRESCALER_1024=0x05,
}T0_PRESCALER;

typedef enum {
	T0_POLLING=0x00,
	T0_INTERRUPT_NORMAL=0x01,
	T0_INTERRUPT_CMP=0x02
}T0_INTERRUPT;



/* for timer 1 */
typedef enum {
	T1_NORMAL_MODE=0x00							,
	T1_PWM8Bit_MODE=0x01					    ,
	T1_PWM9Bit_MODE=0x02						,
	T1_PWM10Bit_MODE=0x03					    ,
	T1_COMPA_OCR1A_MODE=0x08					,
	T1_FastPWM8Bit_MODE=0x09					,
	T1_FastPWM9Bit_MODE=0x0A					,
	T1_FastPWM10Bit_MODE=0x0B					,
	T1_PWM_PhaseAndFreqCorrect_ICR1_MODE=0x10   ,
	T1_PWM_PhaseCorrect_ICR1_MODE=0x12          ,
	T1_PWM_PhaseCorrect_OCR1A_MODE=0x13         ,
	T1_COMPA_ICR1_MODE=0x18                     ,
	T1_FastPWM_ICR1_MODE=0x1A                   ,
	T1_FastPWM_OCR1A_MODE=0x1B                  ,
}T1_MODE;

typedef enum {
	T1_OC1A_DIS=0x00,
	T1_OC1A_TOGGLE=0x40,
	T1_OC1A_CLEAR=0x80,
	T1_OC1A_SET=0xC0,
	T1_OC1B_DIS=0x00,
	T1_OC1B_TOGGLE=0x10,
	T1_OC1B_CLEAR=0x20,
	T1_OC1B_SET=0x30,
}T1_COM;

typedef enum {
	T1_NO_CLOCK=0x00,
	T1_PRESCALER_1=0x01,
	T1_PRESCALER_8=0x02,
	T1_PRESCALER_64=0x03,
	T1_PRESCALER_256=0x04,
	T1_PRESCALER_1024=0x05,
}T1_PRESCALER;

typedef enum {
	T1_POLLING=0x00,
	T1_INTERRUPT_NORMAL = 0x04,
	T1_INTERRUPT_CMPA = 0x10,
	T1_INTERRUPT_CMPB = 0x08,
	T1_INTERRUPT_INCAP = 0x20,
}T1_INTERRUPT;





/* for timer 2 */
typedef enum {
	T2_NORMAL_MODE=0x00,
	T2_PWM_MODE=0x40,
	T2_COMP_MODE=0x08,
	T2_FastPWM_MODE=0x48
}T2_MODE;

typedef enum {
	T2_OC0_DIS=0,
	T2_OC0_TOGGLE=0x10,
	T2_OC0_CLEAR=0x20,
	T2_OC0_SET=0x30
}T2_COM;

typedef enum {
	T2_NO_CLOCK=0x00,
	T2_PRESCALER_1=0x01,
	T2_PRESCALER_8=0x02,
	T2_PRESCALER_32=0x03,
	T2_PRESCALER_64=0x04,
	T2_PRESCALER_128=0x05,
	T2_PRESCALER_256=0x06,
	T2_PRESCALER_1024=0x07
}T2_PRESCALER;

typedef enum {
	T2_POLLING = 0x00,
	T2_INTERRUPT_NORMAL = 0x40,
	T2_INTERRUPT_CMP = 0x80
}T2_INTERRUPT;


/************************************************************************/
/*                       Extern Global Variables                        */
/************************************************************************/

/* Global variables for the absolute value of the prescaller */
extern volatile uint16 Gv_PrescallerTimer0_AbsoluteValue;
extern volatile uint16 Gv_PrescallerTimer1_AbsoluteValue;
extern volatile uint16 Gv_PrescallerTimer2_AbsoluteValue;

/* Global variables for the Mask value of the prescaler (values set as default) */
extern volatile uint8 Gv_PrescallerTimer0_Mask;
extern volatile uint8 Gv_PrescallerTimer1_Mask;
extern volatile uint8 Gv_PrescallerTimer2_Mask;
extern volatile uint8 Timer_gEnumBcm_Tx_Flag;
extern volatile uint8 Time_Init;
/************************************************************************/
/*                   Timers' Functions' prototypes                      */
/************************************************************************/
/**
 * Function : Timers_Init
 * Description: this function is to initialize the Timer0 
 * @param cfg_s the Configuration Structure which include:
 * 								1- the Channel of the Timer(Timer0,Timer1,Timer2)
 *								2- the mode(Timer or counter)
 * 								3- the amount of counters that the timer has to wait before in us
 * 								4- the interrupt mask
 * @return the Status of the initialization [OK Or NOT_OK] 
 */
uint8 Timers_Init(Timers_CFG_S* cfg_s);
/**
 * Function : Timers_SetCounter
 * Description: Function to set the interrupt to come every no of us
 * @param ch_no the Timer no {TIMER0,TIMER1,TIMER2}
 * @param count the no to wait for 
 * @return the Status of the initialization [OK Or NOT_OK]
 */
uint8 Timers_SetCounter(uint8 ch_no,uint32 count);

/**
 * Function : Timers_Start
 * Description: start the counter/Timer
 * @param ch_no the Timer no {TIMER0,TIMER1,TIMER2}
 * @return the Status of the initialization [OK Or NOT_OK]
 */
uint8 Timers_Start(uint8 ch_no);
/**
 * Function : Timers_Start
 * Description: Stop the Timer/Counter by setting the the prescaler pins to 0
 * @param ch_no the Timer no {TIMER0,TIMER1,TIMER2}
 * @return the Status of the initialization [OK Or NOT_OK]
 */
uint8 Timers_Stop(uint8 ch_no);

/**
 * Function : Timers_Read
 * Description: Read the Timer/Counter Register
 * @param ch_no the Timer no {TIMER0,TIMER1,TIMER2}
 * Return the value of the Register
 */
uint32 Timers_Read(uint8 ch_no);
/*===========================Timer0 Control===============================*/

/**
 * Function : Timers_timer0_Init
 * Description: this function is to initialize the Timer0 
 * @param control the control Reg value which include the mode and the Gv_PrescallerTimer0_AbsoluteValue
 * @param initialValue the initial value to be set in the TCNT0 Reg
 * @param outputCompare the value to be set in the OCR0 Reg 
 * @param interruptMask Enable or disable the interrupts of the Timer
 */
void Timers_timer0_Init(T0_MODE mode,T0_COM OC0,T0_PRESCALER prescal, uint8 initialValue, uint8 outputCompare, T0_INTERRUPT interruptMask);

/**
 * Function : Timers_timer0_Set
 * Description: Function to set the timer Reg with a value
 * @param value the value to set 
 */
void Timers_timer0_Set(uint8 value);

/**
 * Function : Timers_timer0_Read
 * Description: read the value of the TCNT0 Register
 * @return the value Read by the function
 */
uint8 Timers_timer0_Read(void);

/**
 * Function : Timers_timer0_Start
 * Description: start the counter/Timer
 */
void Timers_timer0_Start(void);


/**
 * Function : Timers_timer0_Stop
 * Description: Stop the Timer/Counter by setting the the prescaller pins to 0
 */
void Timers_timer0_Stop(void);

/**
 * Function : Timers_timer0_Delay_ms
 * Description: Delay function pooling based to block the code for a specific amount of time
 * @param delay the time I want to delay in ms
 */
void Timers_timer0_Delay_ms(uint16 delay);

/**
 * Timers_timer0_Delay_ns
 * Description: Delay function pooling based to block the code for a specific amount of time
 * @param delay the time I want to delay in ns
 */
void Timers_timer0_Delay_ns(uint32 delay);

/**
 * Timers_timer0_SwPWM
 * Description: Timers_timer0_SwPWM is a function to generate a software PWM on a GPIO pin 
			the freq, port, and the pin of the output in the timers.h 
 * @param dutyCycle : the duty cycle of the PWM in percentage
 * @param freq : the frequency of the PWM in Hz
 */
void Timers_timer0_SwPWM(uint8 dutyCycle,uint64 freq);


/*===========================Timer1 Control===============================*/

/**
 * Description:						 This function is to initialize timer 1. 
 * @param mode:						 The mode of the timer
 * @param OC:						 Compare match pin status
 * @param prescal:					 The prescaler of the timer
 * @param initialValue:				 The initial Value to be set
 * @param outputCompareLow:			 The low Reg set value
 * @param outputCompareHigh:         The High Reg set value
 * @param inputCapture:              The input Capture status
 * @param interruptMask:             The interrupt status
 */
void Timers_timer1_Init(T1_MODE mode,T1_COM OC,T1_PRESCALER prescal, uint16 initialValue, uint8 outputCompareLow, uint8 outputCompareHigh,uint16 inputCapture, T1_INTERRUPT interruptMask);

/**
 * Function : Timers_timer1_SetLowReg 
 * Description: set the Reg TCNT1L to a value
 * @param value the value to be set with no more than 256
 */

void Timers_timer1_SetLowReg(uint8 value);
/**
 * Description: set the Reg TCNT1H to a value
 * @param value the value to be set with no more than 256
 */

void Timers_timer1_SetHighReg(uint8 value);

/**
 * Description: read the value of the TCNT1L Register
 * @return return the value
 */

uint8 Timers_timer1_ReadLowReg(void);

/**
 * Description: read the value of the TCNT1H Register
 * @return return the value
 */
uint8 Timers_timer1_ReadHighReg(void);

/**
 * Description: start the counting from the moment of this function call
  * @param value the value to be set in the prescaller pins in the TCCR2 Reg
 */
void Timers_timer1_Start(void);

/**
* Description: Stop the Timer/Counter by setting the the prescaller pins to 0
*/
void Timers_timer1_Stop(void);
/**
 * Description: Delay function pooling based to block the code for a specific amount of time
 * @param delay the time I want to delay in ms
 */
void Timers_timer1_Delay_ms(uint16 delay);



/**
 * Description: Delay function pooling based to block the code for a specific amount of time
 * @param delay the time I want to delay in ns
 */
void Timers_timer1_Delay_ns(uint32 delay);

/**
 * Description: Timers_timer1_SwPWM is a function to generate a software PWM on a GPIO pin 
			the freq, port, and the pin of the output is configured in timers.h 
 * @param dutyCycle : the duty cycle of the PWM in percentage
 * @param freq : the frequency of the PWM in Hz
 */
void Timers_timer1_SwPWM(uint8 dutyCycle,uint64 freq);


/*===========================Timer2 Control===============================*/

/**
 * Description: this function is to initialize the Timer2 
 * @mode  the mode of the timer
 * @param OC0 the output pin
 * @param prescal the prescaller of the timer
 * @param initialValue the initial value to be set in the TCNT0 Reg
 * @param outputCompare the value to be set in the OCR0 Reg 
 * @param interruptMask Enable or disable the interrupts of the Timer
 */
void Timers_timer2_Init(T2_MODE mode,T2_COM OC0,T2_PRESCALER prescal, uint8 initialValue, uint8 outputCompare, T2_INTERRUPT interruptMask);

/**
 * Description: set the Reg TCNT2 to a value
 * @param value the value to be set with no more than 255
 */

void Timers_timer2_Set(uint8 value);

/**
 * Description: read the value of the TCNT2 Register
 * @return return the value
 */

uint8 Timers_timer2_Read(void);

/**
 * Description: start the counting from the moment of this function call
  * @param value the value to be set in the prescaller pins in the TCCR2 Reg
 */
void Timers_timer2_Start(void);

/**
 * Description: Stop the Timer/Counter by setting the the prescaller pins to 0
 */
void Timers_timer2_Stop(void);

/**
 * Description: Delay function pooling based to block the code for a specific amount of time
 * @param delay the time I want to delay in ms
 */
void Timers_timer2_Delay_ms(uint16 delay);


/**
 * Description: Delay function pooling based to block the code for a specific amount of time
 * @param delay the time I want to delay in ns
 */
void Timers_timer2_Delay_ns(uint32 delay);
/**
 * Description: Timers_timer2_SwPWM is a function to generate a software PWM on a GPIO pin 
			the freq, port, and the pin of the output in the timers.h 
 * @param dutyCycle : the duty cycle of the PWM in percentage
 */
void Timers_timer2_SwPWM(uint8 dutyCycle,uint64 freq);


#endif /* TIMERS_H_ */