/*
 * button.h
 *
 * Created: 05/11/2022 00:44:56
 *  Author: Mohamed Khalil
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#include "../../Utilities/basetypes.h"
#include "../../Utilities/error_handler.h"
#include "../../MCAL/DIO/dio.h"

/************************************************************************/
/* Types                                      */
/************************************************************************/


typedef enum _BUTTON_STATE
{
	BUTTON_STATE_RELEASED = 0,
	BUTTON_STATE_PRESSED = 1
} T_BUTTON_STATE_E;


/************************************************************************/
/* Functions declarations                      */
/************************************************************************/
// initialize the button in the beginning of the program
T_ERROR_ID_E button_init(T_DIO_PORT_ID_E port_id, uint8_t pin_number);

// read the button state
T_ERROR_ID_E button_get_state(T_DIO_PORT_ID_E port_id, uint8_t pin_number, T_BUTTON_STATE_E* p_button_state );





#endif /* BUTTON_H_ */
