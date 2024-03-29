/*
 * SOS.c
 *
 * Created: 11/24/2019 5:55:10 PM
 *  Author: Ammar Shahin
 */

/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include "SOS.h"
#include "Timers.h"
#include "Interrupts.h"
#include <avr/sleep.h>

/************************************************************************/
/*                           Private Enums                              */
/************************************************************************/

typedef enum
{
    TaskDormant,
    TaskReady,
    TaskRunning,
    TaskWaiting,
} EnumSOSTaskState_type;

/************************************************************************/
/*                           Private Structs                            */
/************************************************************************/

typedef struct
{
    v_PtrFunc_v_type PtrTask;
    uint8 Priority;
    uint16 Periodicity;
    EnumSOSTaskState_type TaskState;
} StrSOSTask_type;

/************************************************************************/
/*                   GLOBAL STATIC(Private) VARIABLES                   */
/************************************************************************/
static StrSOSTask_type StrArrOfTasks[SOS_MAX_NUMBER_OF_TASKS];

static volatile uint16 Systick;

/************************************************************************/
/*                         Private MACROS                               */
/************************************************************************/
#define MAX_SYSTICK_VALUS 65000u

/************************************************************************/
/*                           Private Functions                          */
/************************************************************************/
/**
 * Function : TimerSysticCallback
 * Description: this function is Called by the ISR to Update the System Ticks
 * @return void 
 */
static void TimerSysticCallback(void)
{
    Systick++;
    if (Systick == MAX_SYSTICK_VALUS)
    {
        Systick = INITIAL_ONE;
    }
    else
    {
        //Do Nothing
    }
}

/************************************************************************/
/*                           APIs IMPLEMENTATION                        */
/************************************************************************/
/**
 * Function : Sos_Init
 * Description: this function is to initialize the SOS
 * @return Status: of the initialization according to the Error handling macros 
 */
EnumSOSError_type Sos_Init(void)
{
    uint8 index;
    EnumSOSError_type API_State = OK_T;
    Systick = INITIAL_ONE;
    uint32 TimerCount_Time;

    /* Enable the Global Interrupt */
    Interrupts_On();

    /* Set the Sleep Mode To Idle */
    set_sleep_mode(SLEEP_MODE_IDLE);

    /* Set the Systick of the Timer ISR */
    TimerCount_Time = MILLISECONSD_TO_MICROSECONSD_FACTOR * SYSTEM_TICK_MS;

    /* Set the timer Call Back Value */
    Timers_SetCallBack(TimerSysticCallback);

    /* Initialize the Buffer used in the SOS */
    for (index = INITIAL_ZERO; index < SOS_MAX_NUMBER_OF_TASKS; index++)
    {
        StrArrOfTasks[index].Periodicity = INITIAL_ZERO;
        StrArrOfTasks[index].Priority = INITIAL_ZERO;
        StrArrOfTasks[index].TaskState = TaskDormant;
        StrArrOfTasks[index].PtrTask = NULL;
    }

    /* Initialize the Timer used in the TMU */
    switch (SOS_TIMER)
    {
    case TIMER_0:
        /* Initialize the Timer Used  */
        Timers_Init(&timer0_cfg_s);

        /* Set the default resolution  */
        Timers_SetCounter(TIMER_0, TimerCount_Time);
        break;
    case TIMER_1:
        /* Initialize the Timer Used  */
        Timers_Init(&timer1_cfg_s);

        /* Set the default resolution  */
        Timers_SetCounter(TIMER_1, TimerCount_Time);
        break;

    case TIMER_2:
        /* Initialize the Timer Used  */
        Timers_Init(&timer2_cfg_s);

        /* Set the default resolution  */
        Timers_SetCounter(TIMER_2, TimerCount_Time);
        break;
    default:
        API_State = ERROR_INVALID_INPUT;
        break;
    }
    return API_State;
}

/**
 * Function : Sos_Create_Task
 * Description: this function is to create Task and add it to the Operating System
 * @param PtrFunc:
					i/p: Pointer to the Task
 * @param priority: 
					i/p: The priority of the task to be entered
	Note : The Valid priority range [1 to SOS_MAX_PRIORITY] >> any Larger Priority will be ignored.
 * @param periodicity:
					i/p: The periodicity of the Task
	Note : The Stable range of the Task is in range [5 to 2000 Systicks]
 * @return EnmTMUError_t: the status of the function according to the Error handling Enum 
 */
EnumSOSError_type Sos_Create_Task(v_PtrFunc_v_type PtrFunc, uint8 priority, uint16 periodicity)
{
    EnumSOSError_type API_State = OK_T;
    uint8 index;
    /* Protect from NUll pointer */
    if (NULL != PtrFunc)
    { /* Loop Through the Array of Tasks */
        for (index = INITIAL_ZERO; index < SOS_MAX_NUMBER_OF_TASKS; index++)
        { /* Find a task place that hasn't been Reserved by another task */
            if (StrArrOfTasks[index].PtrTask == NULL)
            {
                /* Set the Entered Values to the Empty Space in the Task's Array*/
                StrArrOfTasks[index].PtrTask = PtrFunc;
                StrArrOfTasks[index].Periodicity = periodicity;
                StrArrOfTasks[index].TaskState = TaskReady;

                /* Check If the entered priority is larger than the maximum one >> Set it to the Max */
                if (priority <= SOS_MAX_PRIORITY)
                {
                    StrArrOfTasks[index].Priority = priority;
                }
                else
                {
                    StrArrOfTasks[index].Priority = SOS_MAX_PRIORITY;
                }
                API_State = OK_T;
                break;
            }
            else
            {
                API_State = ERROR_MAX_TASKS_NUMBER_REACHED;
            }
        }
    }
    else
    {
        API_State = ERROR_NULL_POINTER;
    }
    return API_State;
}

/**
 * Function : Sos_Run
 * Description: this function is to run the System Scheduler (Algorithm)
 * @return void
 */
void Sos_Run(void)
{
    sint8 index = INITIAL_ZERO;
    sint8 MaxPriorityIndex = INITIAL_MINUS_ONE;
    sint8 MaxPriority = INITIAL_ZERO;
    /* Start the Timer Used  */
    Timers_Start(SOS_TIMER);
    while (TRUE)
    {
        for (index = INITIAL_ZERO; index < SOS_MAX_NUMBER_OF_TASKS; index++)
        {
            switch ((StrArrOfTasks[index].TaskState))
            {
            case TaskDormant:
                //Do Nothing
                break;
            case TaskReady:
                if (MaxPriority < StrArrOfTasks[index].Priority)
                {
                    MaxPriority = StrArrOfTasks[index].Priority;
                    MaxPriorityIndex = index;
                }
                else
                {
                    //Do Nothing
                }
                break;
            case TaskRunning:
                /* Return the State of the Task to waiting */
                StrArrOfTasks[index].TaskState = TaskWaiting;
                index = index - INITIAL_ONE;
                break;
            case TaskWaiting:
                if ((Systick % StrArrOfTasks[index].Periodicity) == FALSE)
                {
                    /* Return the State of the Task to Ready */
                    StrArrOfTasks[index].TaskState = TaskReady;
                    index = index - INITIAL_ONE;
                }
                else
                {
                    //Do nothing
                }
                break;
            default:
                break;
            }
        }

        if (MaxPriorityIndex >= INITIAL_ZERO)
        {
            StrArrOfTasks[MaxPriorityIndex].PtrTask();
            StrArrOfTasks[MaxPriorityIndex].TaskState = TaskRunning;
            MaxPriorityIndex = INITIAL_MINUS_ONE;
            MaxPriority = INITIAL_ZERO;
        }
        else
        {
            //Do Nothing
        }
        sleep_mode();
    }
}

/**
 * Function : Sos_Delete_Task
 * Description: this function is to Delete the Task
 * param PtrTaskFunction: pointer to function to the task to be deleted
 * @return the State of the API according to the Enum of the Error Handler
 */
EnumSOSError_type Sos_Delete_Task(v_PtrFunc_v_type PtrTaskFunction)
{
    EnumSOSError_type API_State = OK_T;
    uint8 index;

    if (PtrTaskFunction != NULL)
    {
        for (index = INITIAL_ZERO; index < SOS_MAX_NUMBER_OF_TASKS; index++)
        {
            if (StrArrOfTasks[index].PtrTask == PtrTaskFunction)
            {
                StrArrOfTasks[index].PtrTask = NULL;
                StrArrOfTasks[index].Periodicity = FALSE;
                StrArrOfTasks[index].Priority = FALSE;
                StrArrOfTasks[index].TaskState = TaskDormant;
                API_State = OK_T;
                break;
            }
            else
            {
                API_State = ERROR_INVALID_INPUT;
            }
        }
    }
    else
    {
        API_State = ERROR_NULL_POINTER;
    }
    return API_State;
}