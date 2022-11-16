/*
 * led.h
 *
 * Created: 05/11/2022 00:27:38
 *  Author: mhhel
 */ 


#ifndef LED_H_
#define LED_H_

#include "../../Utilities/basetypes.h"
#include "../../MCAL/DIO/dio.h"

typedef enum _LED_STATE 
{
	LED_STATE_OFF = 0,
	LED_STATE_ON = 1
} T_LED_STATE_E;

// initialize the led in the beginning of the program
T_ERROR_ID_E led_init(T_DIO_PORT_ID_E port_id, uint8_t pin_number);

// light up the led
T_ERROR_ID_E led_on(T_DIO_PORT_ID_E port_id, uint8_t pin_number);

// shut the led light off
T_ERROR_ID_E led_off(T_DIO_PORT_ID_E port_id, uint8_t pin_number);

// toggle the led light
T_ERROR_ID_E led_toggle(T_DIO_PORT_ID_E port_id, uint8_t pin_number);

// check if the led on or off
T_ERROR_ID_E led_get_state(T_DIO_PORT_ID_E port_id, uint8_t pin_number, T_LED_STATE_E* p_led_state );







#endif /* LED_H_ */