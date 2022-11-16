/*
 * led.c
 *
 * Created: 05/11/2022 00:27:26
 * Author: Mohamed Khalil
 */ 

#include "led.h"


// initialize all lamps to the 0 state
T_LED_STATE_E g_led_state_db [DIO_PORT_ID_MAX][MAX_NUM_PINS_PER_PORT] = {0};


/************************************************************************/
/* Functions definitions                        */
/************************************************************************/
// initialize the led in the beginning of the program
T_ERROR_ID_E led_init(T_DIO_PORT_ID_E port_id, uint8_t pin_number)
{
  g_led_state_db[port_id][pin_number] = LED_STATE_OFF;
	return dio_pin_direction_init(port_id, pin_number, DIO_PIN_DIRECTION_OUTPUT);
}

// light up the led
T_ERROR_ID_E led_on(T_DIO_PORT_ID_E port_id, uint8_t pin_number)
{
  if(g_led_state_db[port_id][pin_number] != LED_STATE_ON)
  {
    g_led_state_db[port_id][pin_number] = LED_STATE_ON;
	  return dio_pin_state_write(port_id,pin_number,DIO_PIN_STATE_HIGH);
  }    
  return ERROR_ID_NO_ERROR;  
}

// shut the led light off
T_ERROR_ID_E led_off(T_DIO_PORT_ID_E port_id, uint8_t pin_number)
{
  if(g_led_state_db[port_id][pin_number] != LED_STATE_OFF)
  {
    g_led_state_db[port_id][pin_number] = LED_STATE_OFF;
	  return dio_pin_state_write(port_id,pin_number,DIO_PIN_STATE_LOW);
  }
  return ERROR_ID_NO_ERROR;
}

// toggle the led light
T_ERROR_ID_E led_toggle(T_DIO_PORT_ID_E port_id, uint8_t pin_number)
{
  // toggle the pin state
  if (g_led_state_db[port_id][pin_number] == LED_STATE_OFF)
  {
    g_led_state_db[port_id][pin_number] = LED_STATE_ON;
  }
  else
  {
    g_led_state_db[port_id][pin_number] = LED_STATE_OFF;
  }
  
	return dio_pin_state_toggle(port_id,pin_number);
}

// check if the led on or off
T_ERROR_ID_E led_get_state(T_DIO_PORT_ID_E port_id, uint8_t pin_number, T_LED_STATE_E* p_led_state )
{ 
  *p_led_state = g_led_state_db[port_id][pin_number];
	
	return ERROR_ID_NO_ERROR;
}
