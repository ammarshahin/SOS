/*
 * Timers_PCFG.c
 * Description : This File is used to control the Timer Peripherals in the MCAL layer
 * Created: 10/22/2019 2:04:16 PM
 *  Author: Ammar Shahin
 */ 

/************************************************************************/
/*                            Files Includes                            */
/************************************************************************/
#include "Timers_Lcfg.h"
#include "Timers.h"
#include "MCU_Frequency.h"

#define Counter_Default 1000000


/************************************************************************/
/*                     Linking Structures Definitions                    */
/************************************************************************/

/* timer 0 structure */
Timers_CFG_S timer0_cfg_s = {
    TIMER0,
    Timers_MODE,
    Counter_Default,
    INTERRUPT,
    F_CPU,
};

/* timer 1 structure */
Timers_CFG_S timer1_cfg_s = {
	TIMER1,
	T1_NORMAL_MODE,
	Counter_Default,
	INTERRUPT,
	F_CPU,
};


/* timer 2 structure */
Timers_CFG_S timer2_cfg_s = {
	TIMER2,
	Timers_MODE,
	Counter_Default,
	INTERRUPT,
	F_CPU,
}; 