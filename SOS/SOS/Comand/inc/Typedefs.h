/*
 * Typedefs.h
 * Description : This file is used to define all the standard types and the used types used in the project   
 * Created: 10/21/2019 3:33:11 PM
 *  Author: Ammar Shahin
 */ 


#ifndef Typedefs_H_
#define Typedefs_H_

/************************************************************************/
/*                   typedefs for standard types                        */
/************************************************************************/
typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long int uint32;
typedef unsigned long long uint64;
typedef signed char sint8;
typedef signed int sint16;
typedef signed long int sint32;
typedef signed long long sint64;
typedef volatile uint8* const reg_type;

typedef void(*v_PtrFunc_v_type)(void);
/************************************************************************/
/*				      defining the NULL Pointer                         */
/************************************************************************/
#define NULL ((void *)0)
/************************************************************************/
/*				 		defining boolean values                         */
/************************************************************************/
#define FALSE 	0	// defines boolean false
#define TRUE 	1	// defines boolean true	

#define  INITIAL_ZERO 0
#define INITIAL_ONE 1
#define INITIAL_MINUS_ONE -1

/************************************************************************/
/*               Defines for the State of the Function                  */
/************************************************************************/
#define  NOT_OK 0
#define  OK		1
#define  NO_CHANGE -1

#endif /* Typedefs_H_ */