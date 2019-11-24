/*
 * SOS.h
 *
 * Created: 11/24/2019 5:55:22 PM
 *  Author: Ammar Shahin
 */ 

#ifndef SOS_H_
#define SOS_H_

#include "SOS_Cfg.h"
#include "Typedefs.h"

/************************************************************************/
/*                               Macros                                 */
/************************************************************************/
#define TIMER_0  0
#define TIMER_1  1
#define TIMER_2  2

/************************************************************************/
/*                        Enum Typedefs                                 */
/************************************************************************/
typedef enum { 
	OK_T							,
	ERROR_NULL_POINTER			,
	ERROR_INVALID_INPUT			,
	ERROR_MAX_TASKS_NUMBER_REACHED,
	ERROR_INVALID_PRIORITY      , 
} EnumSOSError_type;

typedef enum{ 
	TaskWaiting , 
	TaskReady   ,  
} EnumSOSTaskState_type;

/************************************************************************/
/*                           APIs PROTOTYPES                            */
/************************************************************************/
/**
 * Function : Sos_Init
 * Description: this function is to initialize the SOS
 * @return Status: of the initialization according to the Error handling macros 
 */
EnumSOSError_type Sos_Init(void);

/**
 * Function : Sos_Create_Task
 * Description: this function is to create Task and add it to the Operating System
 * @param priority: 
					i/p: The priority of the task to be entered
 * @param periodicity:
					i/p: The periodicity of the Task
 * @param PtrFunc: 
					i/p: Pointer to the Task
 * @return EnmTMUError_t: the status of the function according to the Error handling Enum 
 */
EnumSOSError_type Sos_Create_Task(v_PtrFunc_v_type PtrFunc,uint8 priority, uint16 periodicity);

/**
 * Function : Sos_Run
 * Description: this function is to run the System Scheduler (Algorithm)
 * @return void
 */
void Sos_Run(void);

/**
 * Function : Sos_Delete_Task
 * Description: this function is to Delete the Task
 * param PtrTaskFunction: pointer to function to the task to be deleted
 * @return the State of the API according to the Enum of the Error Handler
 */
EnumSOSError_type Sos_Delete_Task(v_PtrFunc_v_type PtrTaskFunction);
#endif /* SOS_H_ */