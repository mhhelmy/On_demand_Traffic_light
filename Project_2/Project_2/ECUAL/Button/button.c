/*
 * button.c
 *
 * Created: 05/11/2022 00:45:12
 *  Author: Mohamed Khalil
 */ 

#include "button.h"

/************************************************************************/
/* Functions definitions                        */
/************************************************************************/

// initialize the button in the beginning of the program
T_ERROR_ID_E button_init(T_DIO_PORT_ID_E port_id, uint8_t pin_number)
{
	return dio_pin_direction_init(port_id, pin_number, DIO_PIN_DIRECTION_INPUT);
}

// read the button state
T_ERROR_ID_E button_get_state(T_DIO_PORT_ID_E port_id, uint8_t pin_number, T_BUTTON_STATE_E* p_button_state )
{
	T_ERROR_ID_E error_id;
	
	T_DIO_PIN_STATE_E dio_pin_state = 0;
	
	error_id = dio_pin_state_read(port_id, pin_number, &dio_pin_state);
	if (dio_pin_state == DIO_PIN_STATE_LOW)
	{
		*p_button_state = BUTTON_STATE_RELEASED;
	}
	else
	{
		*p_button_state = BUTTON_STATE_PRESSED;
	}
	
	return error_id;
}
