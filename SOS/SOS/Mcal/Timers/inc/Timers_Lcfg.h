/*
 * Timers_PCFG.c
 * Description : This File is used to control the Timer Peripherals in the MCAL layer
 * Created: 10/22/2019 2:04:16 PM
 *  Author: Ammar Shahin
 */ 
#ifndef  _Timers_LCFG_H
#define  _Timers_LCFG_H

/************************************************************************/
/*                            Files Includes                            */
/************************************************************************/
#include "Typedefs.h"

/************************************************************************/
/*                               Macros                                 */
/************************************************************************/
#define TIMER0  0
#define TIMER1  1
#define TIMER2  2

#define Timers_MODE    0
#define Counter_MODE  1

#define INTERRUPT     1
#define POLLING       0


/************************************************************************/
/*                          Linking Structure                            */
/************************************************************************/
typedef struct Timers_CFG_S{
	uint8  ch_no;
	uint8  Timers_Mode;
	uint32 Timers_count;
	uint8  Timers_Interrupt;
	uint32 CPU_CLK;
}Timers_CFG_S;

/************************************************************************/
/*                       Extern Global variables                        */
/************************************************************************/
extern Timers_CFG_S timer0_cfg_s;
extern Timers_CFG_S timer1_cfg_s;
extern Timers_CFG_S timer2_cfg_s;

#endif /* _Timers_LCFG_H */
