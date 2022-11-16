/*
 * dio.c
 *
 * Created: 04/11/2022 23:38:53
 *  Author: Mohamed Khalil
 */ 
#include "dio.h"

/************************************************************************/
/* Functions definitions                        */
/************************************************************************/

// initialize the micro controller pin to be in or out
T_ERROR_ID_E dio_pin_direction_init(T_DIO_PORT_ID_E port_id, uint8_t pin_number, T_DIO_PIN_DIRECTION_E pin_direction)
{
	T_ERROR_ID_E error_id = ERROR_ID_NO_ERROR;
  
  // validate the input
  if (pin_number >= MAX_NUM_PINS_PER_PORT)
  {
    return ERROR_ID_INVALID_INPUT_ARGUMENT;
  }
  
  // switch over ports to initialize pin direction
	switch (port_id)
	{
	  case DIO_PORT_ID_A:
		
		if (pin_direction == DIO_PIN_DIRECTION_INPUT)
		{
			reset_bit_8_bit_field(P_REG_DDRA, pin_number);
		}
		else if (pin_direction == DIO_PIN_DIRECTION_OUTPUT)
		{
			set_bit_8_bit_field(P_REG_DDRA, pin_number);
		}
		else
		{
			error_id = ERROR_ID_INVALID_INPUT_ARGUMENT;
		}
		break;
		 
		case DIO_PORT_ID_B:
		 		
		if (pin_direction == DIO_PIN_DIRECTION_INPUT)
		{
			reset_bit_8_bit_field(P_REG_DDRB, pin_number);
		}
		else if (pin_direction == DIO_PIN_DIRECTION_OUTPUT)
		{
			set_bit_8_bit_field(P_REG_DDRB, pin_number);
		}
		else
		{
			error_id = ERROR_ID_INVALID_INPUT_ARGUMENT;
		}
		break;
		
		case DIO_PORT_ID_C:
		
		if (pin_direction == DIO_PIN_DIRECTION_INPUT)
		{
			reset_bit_8_bit_field(P_REG_DDRC, pin_number);
		}
		else if (pin_direction == DIO_PIN_DIRECTION_OUTPUT)
		{
			set_bit_8_bit_field(P_REG_DDRC, pin_number);
		}
		else
		{
			error_id = ERROR_ID_INVALID_INPUT_ARGUMENT;
		}
		break;
		
		
		case DIO_PORT_ID_D:
		
		if (pin_direction == DIO_PIN_DIRECTION_INPUT)
		{
			reset_bit_8_bit_field(P_REG_DDRD, pin_number);
		}
		else if (pin_direction == DIO_PIN_DIRECTION_OUTPUT)
		{
			set_bit_8_bit_field(P_REG_DDRD, pin_number);
		}
		else
		{
			error_id = ERROR_ID_INVALID_INPUT_ARGUMENT;
		}
		break;
		 
		default:
			error_id = ERROR_ID_INVALID_INPUT_ARGUMENT;
		break;	
	}
	
	return error_id;

}

// write a new pin state to output pins
T_ERROR_ID_E dio_pin_state_write(T_DIO_PORT_ID_E port_id, uint8_t pin_number, T_DIO_PIN_STATE_E pin_state)
{
	T_ERROR_ID_E error_id = ERROR_ID_NO_ERROR;
  
  // validate the input
  if (pin_number >= MAX_NUM_PINS_PER_PORT)
  {
    return ERROR_ID_INVALID_INPUT_ARGUMENT;
  }
  
  // switch over ports to write over the pin
	switch (port_id)
	{
		case DIO_PORT_ID_A:
		
		if (pin_state == DIO_PIN_STATE_LOW)
		{
			reset_bit_8_bit_field(P_REG_PORTA, pin_number);
		}
		else if (pin_state == DIO_PIN_STATE_HIGH)
		{
			set_bit_8_bit_field(P_REG_PORTA, pin_number);
		}
		else
		{
			error_id = ERROR_ID_INVALID_INPUT_ARGUMENT;
		}
		break;
		
		case DIO_PORT_ID_B:
		
		if (pin_state == DIO_PIN_STATE_LOW)
		{
			reset_bit_8_bit_field(P_REG_PORTB, pin_number);
		}
		else if (pin_state == DIO_PIN_STATE_HIGH)
		{
			set_bit_8_bit_field(P_REG_PORTB, pin_number);
		}
		else
		{
			error_id = ERROR_ID_INVALID_INPUT_ARGUMENT;
		}
		break;
		
		case DIO_PORT_ID_C:
		
		if (pin_state == DIO_PIN_STATE_LOW)
		{
			reset_bit_8_bit_field(P_REG_PORTC, pin_number);
		}
		else if (pin_state == DIO_PIN_STATE_HIGH)
		{
			set_bit_8_bit_field(P_REG_PORTC, pin_number);
		}
		else
		{
			error_id = ERROR_ID_INVALID_INPUT_ARGUMENT;
		}
		break;
		
		
		case DIO_PORT_ID_D:
		
		if (pin_state == DIO_PIN_STATE_LOW)
		{
			reset_bit_8_bit_field(P_REG_PORTD, pin_number);
		}
		else if (pin_state == DIO_PIN_STATE_HIGH)
		{
			set_bit_8_bit_field(P_REG_PORTD, pin_number);
		}
		else
		{
			error_id = ERROR_ID_INVALID_INPUT_ARGUMENT;
		}
		break;
		
		default:
		error_id = ERROR_ID_INVALID_INPUT_ARGUMENT;
		break;
	}
	
	return error_id;

}


// read input or output current pin state
T_ERROR_ID_E dio_pin_state_read(T_DIO_PORT_ID_E port_id, uint8_t pin_number, T_DIO_PIN_STATE_E* p_pin_state)
{
  uint8_t raw_pin_state;
	T_ERROR_ID_E error_id = ERROR_ID_NO_ERROR;
  
  // validate the input
  if (pin_number >= MAX_NUM_PINS_PER_PORT)
  {
    return ERROR_ID_INVALID_INPUT_ARGUMENT;
  }
  
  
  // switch over ports to read the pin state
		switch (port_id)
		{
			case DIO_PORT_ID_A:
			
			raw_pin_state = read_bit_8_bit_field(REG_PINA, pin_number);
			if(raw_pin_state == 0)
			{
				*p_pin_state = DIO_PIN_STATE_LOW;
			}
			else
			{
				*p_pin_state = DIO_PIN_STATE_HIGH;
			}
			break;
			case DIO_PORT_ID_B:
			
			raw_pin_state = read_bit_8_bit_field(REG_PINB, pin_number);
			if(raw_pin_state == 0)
			{
				*p_pin_state = DIO_PIN_STATE_LOW;
			}
			else
			{
				*p_pin_state = DIO_PIN_STATE_HIGH;
			}
			break;
			case DIO_PORT_ID_C:
			raw_pin_state = read_bit_8_bit_field(REG_PINC, pin_number);
			if(raw_pin_state == 0)
			{
				*p_pin_state = DIO_PIN_STATE_LOW;
			}
			else
			{
				*p_pin_state = DIO_PIN_STATE_HIGH;
			}
			break;
			case DIO_PORT_ID_D:
			raw_pin_state = read_bit_8_bit_field(REG_PIND, pin_number);
			if(raw_pin_state == 0)
			{
				*p_pin_state = DIO_PIN_STATE_LOW;
			}
			else
			{
				*p_pin_state = DIO_PIN_STATE_HIGH;
			}
			break;
			default:
			error_id = ERROR_ID_INVALID_INPUT_ARGUMENT;
			break;
		}
	
	return error_id;
	
}

// toggle current output pin state
T_ERROR_ID_E dio_pin_state_toggle(T_DIO_PORT_ID_E port_id, uint8_t pin_number)
{
	T_ERROR_ID_E error_id = ERROR_ID_NO_ERROR;

  // validate the input
  if (pin_number >= MAX_NUM_PINS_PER_PORT)
  {
    return ERROR_ID_INVALID_INPUT_ARGUMENT;
  }
  
  // switch over the Ports and Pins to toogle the requested pin
	switch (port_id)
	{
		case DIO_PORT_ID_A:
		
		toggle_bit_8_bit_field(P_REG_PORTA, pin_number);
		
		break;
		
		case DIO_PORT_ID_B:
		
		toggle_bit_8_bit_field(P_REG_PORTB, pin_number);
		
		break;
		case DIO_PORT_ID_C:
		
		toggle_bit_8_bit_field(P_REG_PORTC, pin_number);
		
		break;
		
		case DIO_PORT_ID_D:
		
		toggle_bit_8_bit_field(P_REG_PORTD, pin_number);
		
		break;
		default:
		error_id = ERROR_ID_INVALID_INPUT_ARGUMENT;
		break;
	}
	
	return error_id;

}
