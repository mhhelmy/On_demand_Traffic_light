/*
 * bitwise_operations.h
 *
 * Created: 04/11/2022 22:59:51
 *  Author: Mohamed Khalil
 */ 


#ifndef BITWISE_OPERATIONS_H_
#define BITWISE_OPERATIONS_H_

#include "basetypes.h"

/************************************************************************/
/* Function definitions                        */
/************************************************************************/

// set a specific bit in an 8-bit Field
void static inline set_bit_8_bit_field( volatile uint8_t* p_field, uint8_t location)
{
	uint8_t mask;
	
	mask = 1<<location;
	
	*p_field |= mask;
}

// reset a specific bit in an 8-bit Field
void static inline reset_bit_8_bit_field(volatile uint8_t* p_field, uint8_t location)
{
	uint8_t mask;
	
	mask = ~(1<< location);
	
	*p_field &=mask;
}

// read a specific bit in an 8-bit Field
uint8_t static inline read_bit_8_bit_field(uint8_t field, uint8_t location)
{
	uint8_t mask;
	
	mask = 1<< location;
	
	return (field & mask) >>location;
}

// toggle a specific bit in an 8-bit Field
void static inline toggle_bit_8_bit_field( volatile uint8_t* p_field, uint8_t location)
{
	uint8_t mask;
	
	mask = 1<< location;
	
	*p_field ^= mask;
}

#endif /* BITWISE_OPERATIONS_H_ */
