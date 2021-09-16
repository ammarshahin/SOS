/*
 * SOS_Cfg.h
 *
 * Created: 11/24/2019 10:11:13 PM
 *  Author: Ammar Shahin 
 */
#ifndef SOS_CFG_H_
#define SOS_CFG_H_

/* maximum number of tasks in the system [1 to 6]*/
#define SOS_MAX_NUMBER_OF_TASKS 6

/* max priorities in the system and 0 is the highest priority */
#define SOS_MAX_PRIORITY 6

/* system tick in milliseconds */
#define SYSTEM_TICK_MS 1

/* [TIMER_0, TIMER_1, TIMER_2] */
#define SOS_TIMER TIMER_1

#endif /* SOS_CFG_H_ */