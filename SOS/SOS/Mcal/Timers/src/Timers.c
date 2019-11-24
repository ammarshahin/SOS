/*
 * Timers.c
 * Description : This File is used to control the Timer Peripherals in the MCAL layer
 * Created: 10/22/2019 2:04:16 PM
 *  Author: Ammar Shahin
 */ 

/************************************************************************/
/*                            Files Includes                            */
/************************************************************************/
#include "Typedefs.h"
#include "Gpio.h"
#include "Timers_Lcfg.h"
#include "Timers.h"
#include "Interrupts.h"
#include "Led.h"

/************************************************************************/
/*                          Global Variables                            */
/************************************************************************/

/* Global variables for the absolute value of the prescaller */
volatile uint16 Gv_PrescallerTimer0_AbsoluteValue;
volatile uint16 Gv_PrescallerTimer1_AbsoluteValue;
volatile uint16 Gv_PrescallerTimer2_AbsoluteValue;

/* Global variables for the Mask value of the prescaler (values set as default) */
volatile uint8 Gv_PrescallerTimer0_Mask = T0_PRESCALER_1;
volatile uint8 Gv_PrescallerTimer1_Mask = T1_PRESCALER_1024;
volatile uint8 Gv_PrescallerTimer2_Mask = T2_PRESCALER_1;

static volatile uint32 Gv_F_CPU;
static volatile uint16  Gv_Count;
volatile uint8 Timer_gEnumBcm_Tx_Flag;

volatile uint8 Time_Init;

/************************************************************************/
/*                               MACROS                                 */
/************************************************************************/
#define SHIFT_FACTOR 8
#define PRESCALER_MASK 0xf8

/************************************************************************/
/*                   Timers' Functions' Implementations                 */
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
uint8 Timers_Init(Timers_CFG_S* cfg_s)
{
	uint8 cfg_Result = NOT_OK;
	Gv_F_CPU = cfg_s->CPU_CLK;
	switch (cfg_s->ch_no)
	{
			case TIMER0:
			TCCR0 |= cfg_s->Timers_Mode;
			TIMSK |= cfg_s->Timers_Interrupt;
			switch(Gv_PrescallerTimer0_Mask)
			{
				case T0_NO_CLOCK :
				Gv_PrescallerTimer0_AbsoluteValue = 0;
				break;
				case  T0_PRESCALER_1 :
				Gv_PrescallerTimer0_AbsoluteValue = 1;
				break;
				case  T0_PRESCALER_8 :
				Gv_PrescallerTimer0_AbsoluteValue = 8;
				break;
				case  T0_PRESCALER_64 :
				Gv_PrescallerTimer0_AbsoluteValue = 64;
				break;
				case  T0_PRESCALER_256 :
				Gv_PrescallerTimer0_AbsoluteValue = 256;
				break;
				case  T0_PRESCALER_1024 :
				Gv_PrescallerTimer0_AbsoluteValue = 1024;
				break;
			}
			cfg_Result = OK;
			break;
			
			case TIMER1:				
			TCCR1A |= (cfg_s->Timers_Mode & 0x03);
			TCCR1B |= (cfg_s->Timers_Mode & 0x18);
			TIMSK |= 0x04;
			Interrupts_On();
			switch(Gv_PrescallerTimer1_Mask)
			{
				case T1_NO_CLOCK :
				Gv_PrescallerTimer1_AbsoluteValue = 0;
				break;
				case  T1_PRESCALER_1 :
				Gv_PrescallerTimer1_AbsoluteValue = 1;
				break;
				case  T1_PRESCALER_8 :
				Gv_PrescallerTimer1_AbsoluteValue = 8;
				break;
				case  T1_PRESCALER_64 :
				Gv_PrescallerTimer1_AbsoluteValue = 64;
				break;
				case  T1_PRESCALER_256 :
				Gv_PrescallerTimer1_AbsoluteValue = 256;
				break;
				case  T1_PRESCALER_1024 :
				Gv_PrescallerTimer1_AbsoluteValue = 1024;
				break;
			}
			cfg_Result = OK;
			break;
			
			case TIMER2:	
			TCCR2 |= cfg_s->Timers_Mode;
			TIMSK |= cfg_s->Timers_Interrupt;
			switch(Gv_PrescallerTimer2_Mask)
			{
				case T2_NO_CLOCK :
				Gv_PrescallerTimer2_AbsoluteValue = 0;
				break;
				case  T2_PRESCALER_1 :
				Gv_PrescallerTimer2_AbsoluteValue = 1;
				break;
				case  T2_PRESCALER_8 :
				Gv_PrescallerTimer2_AbsoluteValue = 8;
				break;
				case  T2_PRESCALER_64 :
				Gv_PrescallerTimer2_AbsoluteValue = 64;
				break;
				case  T2_PRESCALER_256 :
				Gv_PrescallerTimer2_AbsoluteValue = 256;
				break;
				case  T2_PRESCALER_1024 :
				Gv_PrescallerTimer2_AbsoluteValue = 1024;
				break;
			}
			cfg_Result = OK;
			break;
			
			default:
			cfg_Result = NOT_OK;
			break;
	}
	Gv_Count = cfg_s->Timers_count;
	Timers_SetCounter(cfg_s->ch_no,Gv_Count);
	return cfg_Result;
}




/**
 * Function : Timers_SetCounter
 * Description: Function to set the interrupt to come every no of us
 * @param ch_no the Timer no {TIMER0,TIMER1,TIMER2}
 * @param count the no to wait for 
 * @return the Status of the initialization [OK Or NOT_OK]
 */
uint8 Timers_SetCounter(uint8 ch_no,uint32 count)
{
	uint32 no_Of_Counts,cfg_Result = NOT_OK;
	switch (ch_no)
	{
	case TIMER0:
		no_Of_Counts = ( count / ( Gv_PrescallerTimer0_AbsoluteValue * SECONDS_TO_MICROSECONSD_FACTOR / Gv_F_CPU) );
		if(no_Of_Counts > TIMER0_MAX_COUNT)
		{
			cfg_Result = NOT_OK;
		}
		else
		{
			Gv_Count = TIMER0_MAX_COUNT - no_Of_Counts;
			TCNT0 = Gv_Count;
			cfg_Result = OK;
		}
		break;
		
	case TIMER1:
		no_Of_Counts = ( count / ( Gv_PrescallerTimer1_AbsoluteValue * SECONDS_TO_MICROSECONSD_FACTOR / Gv_F_CPU) );
		if(no_Of_Counts > TIMER1_MAX_COUNT)
		{
			cfg_Result = NOT_OK;
		}
		else
		{  
			Gv_Count = TIMER1_MAX_COUNT - no_Of_Counts;
			TCNT1H = (uint8)( Gv_Count >> SHIFT_FACTOR);
			TCNT1L = (uint8) (Gv_Count);
			cfg_Result = OK;
		}
	break;
	
	case TIMER2:
		no_Of_Counts = ( count / ( Gv_PrescallerTimer2_AbsoluteValue * SECONDS_TO_MICROSECONSD_FACTOR / Gv_F_CPU) );
		if(no_Of_Counts > TIMER2_MAX_COUNT)
		{
			cfg_Result = NOT_OK;
		}
		else
		{
			Gv_Count = TIMER2_MAX_COUNT - no_Of_Counts;
			TCNT2 = Gv_Count;
			cfg_Result = OK;
		}
	break;
	
	default:
		cfg_Result = NOT_OK;
	break;
	
	}
	Gv_Count = count;
	return cfg_Result;
}
/**
 * Function : Timers_Start 
 * Description: start the counter/Timer
 * @param ch_no : The timer Channel >> {TIMER0,TIMER1,TIMER2}
 * @return the Status of the initialization [OK Or NOT_OK]
 */


uint8 Timers_Start(uint8 ch_no)
{
	switch (ch_no)
	{
	case TIMER0:
		TCCR0 = ( (TCCR0 & PRESCALER_MASK) | Gv_PrescallerTimer0_Mask);
		break;
	case TIMER1:
		TCCR1B= ( (TCCR1B & PRESCALER_MASK) | Gv_PrescallerTimer1_Mask);
		break;
	case TIMER2:
		TCCR2 = ( (TCCR2 & PRESCALER_MASK) | Gv_PrescallerTimer2_Mask);
		break;
	default:
		break;
	}
	return OK;
}



/**
 * Function : Timers_Stop 
 * Description: Stop the Timer/Counter by setting the the prescaler pins to 0 
 * @param ch_no : The timer Channel >> {TIMER0,TIMER1,TIMER2}
 * @return the Status of the initialization [OK Or NOT_OK]
 */
uint8 Timers_Stop(uint8 ch_no)
{
	switch (ch_no)
	{
	case TIMER0:
		TCCR0 &= PRESCALER_MASK;
		break;
	case TIMER1:
		TCCR1B &= PRESCALER_MASK;
		break;
	case TIMER2:
		TCCR2 &= PRESCALER_MASK;
		break;
	default:
		break;
	}
	return OK;
}


/**
 * Function : Timers_Read 
 * Description: Read the Timer/Counter Register
 * @param ch_no : The timer Channel >> {TIMER0,TIMER1,TIMER2}
 * return the value read by the function
 */
uint32 Timers_Read(uint8 ch_no)
{
	switch (ch_no)
	{
	case TIMER0:
		return TCNT0;
		break;
	case TIMER1:
		break;
	case TIMER2:
		break;
	default:
		break;
	}
	return OK;
}

/*===========================Timer0 Control===============================*/

/**
 * Function : Timers_timer0_Init
 * Description: this function is to initialize the Timer0 
 * @param control the control Reg value which include the mode and the Gv_PrescallerTimer0_AbsoluteValue
 * @param initialValue the initial value to be set in the TCNT0 Reg
 * @param outputCompare the value to be set in the OCR0 Reg 
 * @param interruptMask Enable or disable the interrupts of the Timer
 */
void Timers_timer0_Init(T0_MODE mode,T0_COM OC0,T0_PRESCALER prescal, uint8 initialValue, uint8 outputCompare, T0_INTERRUPT interruptMask)
{
	TCCR0 |= (mode|OC0);
	TCNT0 = initialValue;
	OCR0  = outputCompare;
	TIMSK |= interruptMask;
	Gv_PrescallerTimer0_Mask = prescal;
		switch(prescal)
		{
			case T0_NO_CLOCK :
			Gv_PrescallerTimer0_AbsoluteValue= 0;
			break;
			case  T0_PRESCALER_1 :
			Gv_PrescallerTimer0_AbsoluteValue= 1;
			break;
			case  T0_PRESCALER_8 :
			Gv_PrescallerTimer0_AbsoluteValue= 8;
			break;
			case  T0_PRESCALER_64 :
			Gv_PrescallerTimer0_AbsoluteValue= 64;
			break;
			case  T0_PRESCALER_256 :
			Gv_PrescallerTimer0_AbsoluteValue= 256;
			break;
			case  T0_PRESCALER_1024 :
			Gv_PrescallerTimer0_AbsoluteValue= 1024;
			break;
		}
}

/**
 * Function : Timers_timer0_Set
 * Description: Function to set the timer Reg with a value
 * @param value the value to set 
 */
void Timers_timer0_Set(uint8 value)
{
	TCNT0 = value;
}

/**
 * Function : Timers_timer0_Read
 * Description: read the value of the TCNT0 Register
 * @return the value Read by the function
 */
uint8 Timers_timer0_Read(void)
{
	return TCNT0;
}

/**
 * Function : Timers_timer0_Start
 * Description: start the counter/Timer
 */
void Timers_timer0_Start(void)
{
	TCCR0 |= Gv_PrescallerTimer0_Mask;
}


/**
 * Function : Timers_timer0_Stop
 * Description: Stop the Timer/Counter by setting the the prescaller pins to 0
 */
void Timers_timer0_Stop(void)
{
	TCCR0 &= ~(0x07);
}

/**
 * Function : Timers_timer0_Delay_ms
 * Description: Delay function pooling based to block the code for a specific amount of time
 * @param delay the time I want to delay in ms
 */
void Timers_timer0_Delay_ms(uint16 delay)
{
	volatile sint64 counter = ((sint64)delay) * Gv_F_CPU / (TIMER0_MAX_COUNT * Gv_PrescallerTimer0_AbsoluteValue * SECONDS_TO_MILLISECONSD_FACTOR);
	TCNT0 = 0;
	Timers_timer0_Start();
	while(counter--)
	{
		while( (TIFR & TIFR_TOV0_gEnumBcm_Tx_Flag_MASK) == FALSE);
		TIFR |= TIFR_TOV0_gEnumBcm_Tx_Flag_MASK;
	}
	Timers_timer0_Stop();
}


/**
 * Timers_timer0_Delay_ns
 * Description: Delay function pooling based to block the code for a specific amount of time
 * @param delay the time I want to delay in ns
 */
void Timers_timer0_Delay_ns(uint32 delay)
{
	volatile sint64 counter = ((uint64) delay) * Gv_F_CPU / (TIMER0_MAX_COUNT * Gv_PrescallerTimer0_AbsoluteValue * SECONDS_TO_NANOSECONSD_FACTOR);
	Timers_timer0_Start();
	while(counter--)
	{
		while( (TIFR & TIFR_TOV0_gEnumBcm_Tx_Flag_MASK) == FALSE);
		TIFR |= TIFR_TOV0_gEnumBcm_Tx_Flag_MASK;
	}
	Timers_timer0_Stop();
}

/**
 * Timers_timer0_SwPWM
 * Description: Timers_timer0_SwPWM is a function to generate a software PWM on a GPIO pin 
			the freq, port, and the pin of the output in the timers.h 
 * @param dutyCycle : the duty cycle of the PWM in percentage
 * @param freq : the frequency of the PWM in Hz
 */
void Timers_timer0_SwPWM(uint8 dutyCycle,uint64 freq)
{
	uint32 time_Total_ns = (SECONDS_TO_NANOSECONSD_FACTOR / freq);
	uint32 time_On_ns  = ((dutyCycle/DUTY_CYCLE_PERCENTAGE_FACTOR) * time_Total_ns);
	uint32 time_Off_ns = time_Total_ns - time_On_ns;
	Gpio_PinDirection(SWPWM_0_PORT,SWPWM_0_PIN,SET_OUT);
	while(TRUE)
	{
		Gpio_PinWrite(SWPWM_0_PORT,SWPWM_0_PIN,TRUE);
		Timers_timer0_Delay_ns(time_On_ns);
		Gpio_PinWrite(SWPWM_0_PORT,SWPWM_0_PIN,FALSE);
		Timers_timer0_Delay_ns(time_Off_ns);
	}
}


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
void Timers_timer1_Init(T1_MODE mode,T1_COM OC,T1_PRESCALER prescal, uint16 initialValue, uint8 outputCompareLow, uint8 outputCompareHigh,uint16 inputCapture, T1_INTERRUPT interruptMask)
{
	OCR1AL = outputCompareLow;
	OCR1AH = outputCompareHigh;
	TCCR1A |= (mode & 0x03); 
	TCCR1A |= OC;
	TCCR1B |= (mode & 0b00011000);
	TCNT1L = initialValue;
	Gpio_PinDirection(MYPORTD,BIT5,SET_OUT);
	TIMSK |= interruptMask;
	Gv_PrescallerTimer1_Mask = prescal;
	switch(prescal)
	{
		case  T1_NO_CLOCK :
		Gv_PrescallerTimer1_AbsoluteValue= 0;
		break;
		case  T1_PRESCALER_1 :
		Gv_PrescallerTimer1_AbsoluteValue= 1;
		break;
		case  T1_PRESCALER_8 :
		Gv_PrescallerTimer1_AbsoluteValue= 8;
		break;
		case  T1_PRESCALER_64 :
		Gv_PrescallerTimer1_AbsoluteValue= 64;
		break;
		case  T1_PRESCALER_256 :
		Gv_PrescallerTimer1_AbsoluteValue= 256;
		break;
		case  T1_PRESCALER_1024 :
		Gv_PrescallerTimer1_AbsoluteValue= 1024;
		break;
	}
		
}

/**
 * Function : Timers_timer1_SetLowReg 
 * Description: set the Reg TCNT1L to a value
 * @param value the value to be set with no more than 256
 */

void Timers_timer1_SetLowReg(uint8 value)
{
	TCNT1L = value;
}
/**
 * Description: set the Reg TCNT1H to a value
 * @param value the value to be set with no more than 256
 */

void Timers_timer1_SetHighReg(uint8 value)
{
	TCNT1H = value;
}
/**
 * Description: read the value of the TCNT1L Register
 * @return return the value
 */

uint8 Timers_timer1_ReadLowReg(void)
{
	return TCNT1L;
}
/**
 * Description: read the value of the TCNT1H Register
 * @return return the value
 */
uint8 Timers_timer1_ReadHighReg(void)
{
	return TCNT1H;
}
/**
 * Description: start the counting from the moment of this function call
  * @param value the value to be set in the prescaller pins in the TCCR2 Reg
 */
void Timers_timer1_Start(void)
{
	TCCR1B |= Gv_PrescallerTimer1_Mask;
}
/**
* Description: Stop the Timer/Counter by setting the the prescaller pins to 0
*/
void Timers_timer1_Stop(void)
{
	TCCR1B &= 0xf8;
}
/**
 * Description: Delay function pooling based to block the code for a specific amount of time
 * @param delay the time I want to delay in ms
 */
void Timers_timer1_Delay_ms(uint16 delay)
{
	volatile sint64 counter = (((sint64)delay) * Gv_F_CPU) / (TIMER1_MAX_COUNT * Gv_PrescallerTimer1_AbsoluteValue * SECONDS_TO_MILLISECONSD_FACTOR);
	Timers_timer1_Start();
	while(counter--)
	{
		while( (TIFR & TIFR_TOV1_gEnumBcm_Tx_Flag_MASK) == FALSE);
		TIFR |= TIFR_TOV1_gEnumBcm_Tx_Flag_MASK;
	}
	Timers_timer1_Stop();
}

/**
 * Description: Delay function pooling based to block the code for a specific amount of time
 * @param delay the time I want to delay in ns
 */
void Timers_timer1_Delay_ns(uint32 delay)
{
	volatile sint64 counter = ((uint64) delay) * Gv_F_CPU / (TIMER1_MAX_COUNT * Gv_PrescallerTimer1_AbsoluteValue * SECONDS_TO_NANOSECONSD_FACTOR);
	Timers_timer1_Start();
	while(counter--)
	{
		while( (TIFR & TIFR_TOV1_gEnumBcm_Tx_Flag_MASK) == FALSE);
		TIFR |= TIFR_TOV1_gEnumBcm_Tx_Flag_MASK;
	}
	Timers_timer1_Stop();
}

/**
 * Description: Timers_timer1_SwPWM is a function to generate a software PWM on a GPIO pin 
			the freq, port, and the pin of the output is configured in timers.h 
 * @param dutyCycle : the duty cycle of the PWM in percentage
 * @param freq : the frequency of the PWM in Hz
 */
void Timers_timer1_SwPWM(uint8 dutyCycle,uint64 freq)
{
	uint32 time_Total_ns = (SECONDS_TO_NANOSECONSD_FACTOR / freq);
	uint32 time_On_ns  = ((dutyCycle/DUTY_CYCLE_PERCENTAGE_FACTOR) * time_Total_ns);
	uint32 time_Off_ns = time_Total_ns - time_On_ns;
	Gpio_PinDirection(SWPWM_1_PORT,SWPWM_1_PIN,SET_OUT);

	while(TRUE)
	{
		Gpio_PinWrite(SWPWM_1_PORT,SWPWM_1_PIN,TRUE);
		Timers_timer1_Delay_ns(time_On_ns);
		Gpio_PinWrite(SWPWM_1_PORT,SWPWM_1_PIN,FALSE);
		Timers_timer1_Delay_ns(time_Off_ns);
	}	
}
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
void Timers_timer2_Init(T2_MODE mode,T2_COM OC0,T2_PRESCALER prescal, uint8 initialValue, uint8 outputCompare, T2_INTERRUPT interruptMask)
{
	TCCR2 |= (mode|OC0);
	TCNT2 = initialValue;
	OCR2  = outputCompare;
	TIMSK |= interruptMask;
	Gv_PrescallerTimer2_Mask = prescal;
		switch(prescal)
		{
			case T2_NO_CLOCK : 
			Gv_PrescallerTimer2_AbsoluteValue= 0;
			break;	
			case  T2_PRESCALER_1 :
			Gv_PrescallerTimer2_AbsoluteValue= 1;
			break;
			case  T2_PRESCALER_8 :
			Gv_PrescallerTimer2_AbsoluteValue= 8;
			break;
			case  T2_PRESCALER_32 :
			Gv_PrescallerTimer2_AbsoluteValue= 32;
			break;
			case  T2_PRESCALER_64 :
			Gv_PrescallerTimer2_AbsoluteValue= 64;
			break;
			case  T2_PRESCALER_128 :
			Gv_PrescallerTimer2_AbsoluteValue= 128;
			break;
			case  T2_PRESCALER_256 :
			Gv_PrescallerTimer2_AbsoluteValue= 256;
			break;
			case  T2_PRESCALER_1024 :
			Gv_PrescallerTimer2_AbsoluteValue= 1024;
			break;
		}
}


/**
 * Description: set the Reg TCNT2 to a value
 * @param value the value to be set with no more than 255
 */

void Timers_timer2_Set(uint8 value)
{
	TCNT2 = value;
}


/**
 * Description: read the value of the TCNT2 Register
 * @return return the value
 */

uint8 Timers_timer2_Read(void)
{
	return TCNT2;
}

/**
 * Description: start the counting from the moment of this function call
  * @param value the value to be set in the prescaller pins in the TCCR2 Reg
 */
void Timers_timer2_Start(void)
{
		TCCR2 |= Gv_PrescallerTimer2_Mask;
}

/**
 * Description: Stop the Timer/Counter by setting the the prescaller pins to 0
 */
void Timers_timer2_Stop(void)
{
	TCCR2 &= ~(0x07);
}

/**
 * Description: Delay function pooling based to block the code for a specific amount of time
 * @param delay the time I want to delay in ms
 */
void Timers_timer2_Delay_ms(uint16 delay)
{
	volatile sint64 counter = delay *(Gv_F_CPU / (TIMER2_MAX_COUNT * Gv_PrescallerTimer2_AbsoluteValue * SECONDS_TO_MILLISECONSD_FACTOR));
	Timers_timer2_Start();
	while(counter--)
	{
		while( (TIFR & TIFR_TOV2_gEnumBcm_Tx_Flag_MASK) == FALSE);
		TIFR |= TIFR_TOV2_gEnumBcm_Tx_Flag_MASK;
	}
	Timers_timer2_Stop();
}


/**
 * Description: Delay function pooling based to block the code for a specific amount of time
 * @param delay the time I want to delay in ns
 */
void Timers_timer2_Delay_ns(uint32 delay)
{
	volatile sint64 counter = ((uint64) delay) * Gv_F_CPU / (TIMER2_MAX_COUNT * Gv_PrescallerTimer2_AbsoluteValue * SECONDS_TO_NANOSECONSD_FACTOR);
	Timers_timer2_Start();
	while(counter--)
	{
		while( (TIFR & TIFR_TOV2_gEnumBcm_Tx_Flag_MASK) == FALSE);
		TIFR |= TIFR_TOV2_gEnumBcm_Tx_Flag_MASK;
	}
	Timers_timer2_Stop();
}

/**
 * Description: Timers_timer2_SwPWM is a function to generate a software PWM on a GPIO pin 
			the freq, port, and the pin of the output in the timers.h 
 * @param dutyCycle : the duty cycle of the PWM in percentage
 */
void Timers_timer2_SwPWM(uint8 dutyCycle,uint64 freq)
{
	uint32 time_Total_ns = (SECONDS_TO_NANOSECONSD_FACTOR / freq);
	uint32 time_On_ns  = ((dutyCycle/DUTY_CYCLE_PERCENTAGE_FACTOR) * time_Total_ns);
	uint32 time_Off_ns = time_Total_ns - time_On_ns;
	
	
	Gpio_PinDirection(SWPWM_2_PORT,SWPWM_2_PIN,SET_OUT);
	while(TRUE)
	{
		Gpio_PinWrite(SWPWM_2_PORT,SWPWM_2_PIN,TRUE);
		Timers_timer2_Delay_ns(time_On_ns);
		Gpio_PinWrite(SWPWM_2_PORT,SWPWM_2_PIN,FALSE);
		Timers_timer2_Delay_ns(time_Off_ns);
	}
}


ISR_T(TIMER1_OVF_vect)
{
	Timer_gEnumBcm_Tx_Flag = TRUE;
	Timers_SetCounter(TIMER1,Gv_Count);
}