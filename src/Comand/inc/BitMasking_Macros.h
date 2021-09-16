/*
 * BitMasking_Macros.h
 * Description : This File Contains all the Bit Masking Operations
 * Created: 10/21/2019 3:33:11 PM
 *  Author: Ammar Shahin
*/

#ifndef _MACROS_H_
#define _MACROS_H_

/************************************************************************/
/*               Bit Masking Operations on single Bits                  */
/************************************************************************/
#define SET_BIT(reg, gBufferRxIndex) (reg |= (1 << gBufferRxIndex))
#define CLR_BIT(reg, gBufferRxIndex) (reg &= (~(1 << gBufferRxIndex)))
#define TOG_BIT(reg, gBufferRxIndex) (reg ^= (1 << gBufferRxIndex))
#define GET_BIT(reg, gBufferRxIndex) ((reg >> gBufferRxIndex) & 0x01)

/************************************************************************/
/*               Bit Masking Operations on Nibbles (4 bits)             */
/************************************************************************/
#define SET_HIGH_NIBBLE(reg) (reg |= 0xf0)
#define SET_LOWER_NIBBLE(reg) (reg |= 0x0f)
#define CLR_HIGH_NIBBLE(reg) (reg &= 0x0f)
#define CLR_LOWER_NIBBLE(reg) (reg &= 0xf0)
#define GET_HIGH_NIBBLE(reg) (reg >> 4)
#define GET_LOWER_NIBBLE(reg) (reg & 0x0f)
#define PUTVAL_HIGH_NIBBLE(reg, val) (reg = (reg & 0x0f) | (val << 4))
#define PUTVAL_LOWER_NIBBLE(reg, val) (reg = (reg & 0xf0) | (val & 0x0f))
#define SET_REG_NIBBLE(reg) (reg |= 0xff)

#endif