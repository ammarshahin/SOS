/*
 * Created: 10/22/2019 2:03:42 PM
 * Author : Ammar Shahin
 */ 


#include "SOS.h"
#include "Led.h"



void FirstTask(void)
{
	Led_Tog(LED0);
}

void SecondTask(void)
{
	Led_Tog(LED1);
}

void ThirdTask(void)
{
	Led_Tog(LED2);
}

void ForthTask(void)
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
	
	SOS_Init();	
	
    StrTask_t Task1 = {FirstTask  ,  0 , 1000 };
	StrTask_t Task2 = {SecondTask ,  0 , 2000 };
	StrTask_t Task3 = {ThirdTask  ,  1 , 4000 };
	StrTask_t Task4 = {ForthTask  ,  1 , 10000};
	
	 SOS_CreateTask(&Task1);
	 SOS_CreateTask(&Task2);
	 SOS_CreateTask(&Task3);
	 SOS_CreateTask(&Task4);	
		
	SOS_Scheduler();
}

