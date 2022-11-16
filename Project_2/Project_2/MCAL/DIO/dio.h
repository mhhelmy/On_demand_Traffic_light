/*
 * dio.h
 *
 * Created: 04/11/2022 23:38:35
 *  Author: Mohamed Khalil
 */ 


#ifndef DIO_H_
#define DIO_H_

#include "../registers.h"
#include "../../Utilities/basetypes.h"
#include "../../Utilities/bitwise_operations.h"
#include "../../Utilities/error_handler.h"

#define MAX_NUM_PINS_PER_PORT (8)

// pin state
typedef enum _DIO_PIN_STATE
{
	DIO_PIN_STATE_LOW = 0,
	DIO_PIN_STATE_HIGH = 1
} T_DIO_PIN_STATE_E;

// pin direction
typedef enum _DIO_PIN_DIRECTION
{
	DIO_PIN_DIRECTION_INPUT = 0,
	DIO_PIN_DIRECTION_OUTPUT = 1
} T_DIO_PIN_DIRECTION_E;

// port ID
typedef enum _DIO_PORT_ID
{
	DIO_PORT_ID_A,
	DIO_PORT_ID_B,
	DIO_PORT_ID_C,
	DIO_PORT_ID_D,
  DIO_PORT_ID_MAX

} T_DIO_PORT_ID_E;

// initialize the micro controller pin to be in or out
T_ERROR_ID_E dio_pin_direction_init(T_DIO_PORT_ID_E port_id, uint8_t pin_number, T_DIO_PIN_DIRECTION_E pin_direction);

// write a new pin state to output pins
T_ERROR_ID_E dio_pin_state_write(T_DIO_PORT_ID_E port_id, uint8_t pin_number, T_DIO_PIN_STATE_E pin_state);

// read input or output current pin state
T_ERROR_ID_E dio_pin_state_read(T_DIO_PORT_ID_E port_id, uint8_t pin_number, T_DIO_PIN_STATE_E* p_pin_state);

// toggle current output pin state
T_ERROR_ID_E dio_pin_state_toggle(T_DIO_PORT_ID_E port_id, uint8_t pin_number);


#endif /* DIO_H_ */