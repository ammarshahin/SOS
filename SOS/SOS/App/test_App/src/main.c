/*
 * Created: 10/22/2019 2:03:42 PM
 * Author : Ammar Shahin
 */ 


#include "SOS.h"
#include "Led.h"


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

void Task4(void)
{
	
	Led_Tog(LED3);
}


int main(void)
{
	/* Initializing the Led To indicate The Tasks */
	Led_Init(LED0);
	Led_Init(LED1);
	Led_Init(LED2);
	Led_Init(LED3);
	
	Sos_Init();	
	
	Sos_Create_Task(Task1,5,300);
	Sos_Create_Task(Task2,4,150);
	Sos_Create_Task(Task3,3,75);
	Sos_Create_Task(Task4,2,30);
		
	Sos_Run();
}

