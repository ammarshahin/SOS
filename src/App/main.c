/*
 * Created: 10/22/2019 2:03:42 PM
 * Author : Ammar Shahin
 */

/************************************************************************/
/*                            Includes                                  */
/************************************************************************/
#include "SOS.h"
#include "Led.h"

/************************************************************************/
/*                            Private Macros                             */
/************************************************************************/
#define TASK1_PRIORITY 5
#define TASK2_PRIORITY 4
#define TASK3_PRIORITY 3

#define TASK1_PERIODICITY 90
#define TASK2_PERIODICITY 60
#define TASK3_PERIODICITY 30

/************************************************************************/
/*                            SOS Tasks                                 */
/************************************************************************/
void Task1(void)
{
    Led_Tog(LED0);
}

void Task2(void)
{
    Led_Tog(LED1);
}

void Task3(void)
{
    Led_Tog(LED2);
}

/************************************************************************/
/*                          Main Function                               */
/************************************************************************/
int main(void)
{
    /* Initializing the Led To indicate The Tasks */
    Led_Init(LED0);
    Led_Init(LED1);
    Led_Init(LED2);
    Led_Init(LED3);

    Sos_Init();

    Sos_Create_Task(Task1, TASK1_PRIORITY, TASK1_PERIODICITY);
    Sos_Create_Task(Task2, TASK2_PRIORITY, TASK2_PERIODICITY);
    Sos_Create_Task(Task3, TASK3_PRIORITY, TASK3_PERIODICITY);

    Sos_Run();
}
