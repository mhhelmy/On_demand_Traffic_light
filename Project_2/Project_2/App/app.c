/*
 * App.c
 *
 * Created: 05/11/2022 01:06:41
 *  Author: Mohamed Khalil
 */ 
#include "app.h"


// Global defines
const T_DIO_PORT_ID_E CROSS_WALK_BUTTON_PORT_ID = DIO_PORT_ID_D;
const uint8_t CROSS_WALK_BUTTON_PIN_ID = 2;

const T_DIO_PORT_ID_E CROSS_WALK_LIGHT_GREEN_PORT_ID = DIO_PORT_ID_B;
const uint8_t CROSS_WALK_LIGHT_GREEN_PIN_ID = 0;

const T_DIO_PORT_ID_E CROSS_WALK_LIGHT_YELLOW_PORT_ID = DIO_PORT_ID_B;
const uint8_t CROSS_WALK_LIGHT_YELLOW_PIN_ID = 1;

const T_DIO_PORT_ID_E CROSS_WALK_LIGHT_RED_PORT_ID = DIO_PORT_ID_B;
const uint8_t CROSS_WALK_LIGHT_RED_PIN_ID = 2;

const T_DIO_PORT_ID_E CAR_TRAFFIC_LIGHT_GREEN_PORT_ID = DIO_PORT_ID_A;
const uint8_t CAR_TRAFFIC_LIGHT_GREEN_PIN_ID = 0;

const T_DIO_PORT_ID_E CAR_TRAFFIC_LIGHT_YELLOW_PORT_ID = DIO_PORT_ID_A;
const uint8_t CAR_TRAFFIC_LIGHT_YELLOW_PIN_ID = 1;

const T_DIO_PORT_ID_E CAR_TRAFFIC_LIGHT_RED_PORT_ID = DIO_PORT_ID_A;
const uint8_t CAR_TRAFFIC_LIGHT_RED_PIN_ID = 2;

// defines the timer delay value
const uint8_t TIMER_DELAY_INTERVAL_IN_MS = 250;

// How many delays needed per traffic light phase ==> here it is 50 as we need 5 seconds time per phase
const uint8_t TRAFFIC_LIGHT_DELAYS_COUNT = 20 ;

// defines the systmed frequency
const uint8_t SYSTEM_FREQ_IN_MHZ = 1;


// Global variables
T_SYSTEM_MODE_E g_system_mode;

// Car traffic light state
T_CAR_TRAFFIC_LIGHT_STATE_E g_car_traffic_light_state;

// Car traffic light state when interrupted
T_CAR_TRAFFIC_LIGHT_STATE_E g_car_traffic_light_state_at_interrupt;

// flag indicates that the button has been pressed
uint8_t is_button_pressed;

//Local  functions declarations
static void run_car_traffic_light_green_phase();
static void run_car_traffic_light_yellow_to_red_phase();
static void run_car_traffic_light_red_phase();
static void run_car_traffic_light_yellow_to_green_phase();



/************************************************************************/
/* Functions definitions                        */
/************************************************************************/
// init function for the application
void app_init(void)
{   
	// init button
	button_init(CROSS_WALK_BUTTON_PORT_ID, CROSS_WALK_BUTTON_PIN_ID);
  is_button_pressed = FALSE;
	
	// init cross walk LEDs
	led_init(CROSS_WALK_LIGHT_RED_PORT_ID, CROSS_WALK_LIGHT_RED_PIN_ID);
	led_init(CROSS_WALK_LIGHT_YELLOW_PORT_ID, CROSS_WALK_LIGHT_YELLOW_PIN_ID);
	led_init(CROSS_WALK_LIGHT_GREEN_PORT_ID, CROSS_WALK_LIGHT_GREEN_PIN_ID);
	
	
	// init CAR traffic LEDs
	led_init(CAR_TRAFFIC_LIGHT_RED_PORT_ID, CAR_TRAFFIC_LIGHT_RED_PIN_ID);
	led_init(CAR_TRAFFIC_LIGHT_YELLOW_PORT_ID, CAR_TRAFFIC_LIGHT_YELLOW_PIN_ID);
	led_init(CAR_TRAFFIC_LIGHT_GREEN_PORT_ID, CAR_TRAFFIC_LIGHT_GREEN_PIN_ID);
	
	// init timer 0
	timer_al_init(SYSTEM_FREQ_IN_MHZ,TIMER_ID_0, TIMER_MODE_DELAY);
	
	// initialize the system mode to Normal
	g_system_mode = SYSTEM_MODE_NORMAL;
	
	// enable global interrupts
	sei();
	
	// choose the external interrupt to sense on the rising edge by setting first 2 bits
	REG_MCUCR |= 3;
	
	// Enable external interrupt
	set_bit_8_bit_field(P_REG_GICR, 6);
	
}

static void run_car_traffic_light_green_phase()
{
	uint8_t Traffic_light_delay_counter = TRAFFIC_LIGHT_DELAYS_COUNT;

  // init car traffic light state
	g_car_traffic_light_state = CAR_TRAFFIC_LIGHT_STATE_GREEN;
  
	if(g_system_mode == SYSTEM_MODE_NORMAL)
  {
    // in Normal mode activate  the green light and red pedestrian light
	  led_on(CAR_TRAFFIC_LIGHT_GREEN_PORT_ID, CAR_TRAFFIC_LIGHT_GREEN_PIN_ID);
    led_on(CROSS_WALK_LIGHT_RED_PORT_ID, CROSS_WALK_LIGHT_RED_PIN_ID);
  }
  else
  {
    // clean up the flag anyway as it is not needed here
    is_button_pressed = FALSE;
  }
	
  // delay loop
	while (Traffic_light_delay_counter-- != 0)
	{
    // if system state changed durinf the loop we immedietly break to give pedestrians priority
		if(g_system_mode == SYSTEM_MODE_PEDESTRIAN_CROSSING)
		{
      // clean up the flag anyway as it is not needed here
      is_button_pressed = FALSE;   
      break;
		}
		
    timer_al_delay(TIMER_DELAY_INTERVAL_IN_MS);
    
	}
  
  // Exit the green light state
	led_off(CAR_TRAFFIC_LIGHT_GREEN_PORT_ID, CAR_TRAFFIC_LIGHT_GREEN_PIN_ID);
	led_off(CROSS_WALK_LIGHT_RED_PORT_ID, CROSS_WALK_LIGHT_RED_PIN_ID);
	
}

static void run_car_traffic_light_yellow_to_red_phase()
{
	uint8_t Traffic_light_delay_counter = TRAFFIC_LIGHT_DELAYS_COUNT;
	
  // init car traffic light state
	g_car_traffic_light_state = CAR_TRAFFIC_LIGHT_STATE_YELLOW_TO_RED;
	
	led_on(CAR_TRAFFIC_LIGHT_YELLOW_PORT_ID, CAR_TRAFFIC_LIGHT_YELLOW_PIN_ID);  
  
	if(g_system_mode == SYSTEM_MODE_NORMAL)
  {
    // in Normal mode the pedestrian lights are always red
    led_on(CROSS_WALK_LIGHT_RED_PORT_ID, CROSS_WALK_LIGHT_RED_PIN_ID);
  }
  else
	{
    // in pedestrian crossing mode we blink yellow
  	led_on(CROSS_WALK_LIGHT_YELLOW_PORT_ID, CROSS_WALK_LIGHT_YELLOW_PIN_ID);
    is_button_pressed = FALSE;
	}
	
  // delay loop
	while (Traffic_light_delay_counter-- != 0)
	{
		timer_al_delay(TIMER_DELAY_INTERVAL_IN_MS);
    
    if (is_button_pressed == TRUE)
    {
      // reset the counter so we start the yellow phase again
      Traffic_light_delay_counter = TRAFFIC_LIGHT_DELAYS_COUNT;
      
      // start the initial phase for both yellow lights
      led_on(CROSS_WALK_LIGHT_YELLOW_PORT_ID, CROSS_WALK_LIGHT_YELLOW_PIN_ID);
      led_on(CAR_TRAFFIC_LIGHT_YELLOW_PORT_ID, CAR_TRAFFIC_LIGHT_YELLOW_PIN_ID);
      is_button_pressed = FALSE;
    }
    
		led_toggle(CAR_TRAFFIC_LIGHT_YELLOW_PORT_ID, CAR_TRAFFIC_LIGHT_YELLOW_PIN_ID);
		if(g_system_mode == SYSTEM_MODE_PEDESTRIAN_CROSSING)
		{
			led_toggle(CROSS_WALK_LIGHT_YELLOW_PORT_ID, CROSS_WALK_LIGHT_YELLOW_PIN_ID);
		}
		
	}
	
  // exit the yellow to red state
	led_off(CAR_TRAFFIC_LIGHT_YELLOW_PORT_ID, CAR_TRAFFIC_LIGHT_YELLOW_PIN_ID);
	led_off(CROSS_WALK_LIGHT_YELLOW_PORT_ID, CROSS_WALK_LIGHT_YELLOW_PIN_ID);
  led_off(CROSS_WALK_LIGHT_RED_PORT_ID, CROSS_WALK_LIGHT_RED_PIN_ID);
	
	
}
static void run_car_traffic_light_red_phase()
{
	// loop counter
	uint8_t Traffic_light_delay_counter = TRAFFIC_LIGHT_DELAYS_COUNT;
	
  // init car traffic light state
	g_car_traffic_light_state = CAR_TRAFFIC_LIGHT_STATE_RED;
	
	led_on(CAR_TRAFFIC_LIGHT_RED_PORT_ID, CAR_TRAFFIC_LIGHT_RED_PIN_ID);
			
	if(g_system_mode == SYSTEM_MODE_NORMAL)
  {
    // in Normal mode the cross walk light is always red
     led_on(CROSS_WALK_LIGHT_RED_PORT_ID, CROSS_WALK_LIGHT_RED_PIN_ID);
  }
  else
	{
    // in pedestrian crossing mode the cross walk light should be green
		led_on(CROSS_WALK_LIGHT_GREEN_PORT_ID, CROSS_WALK_LIGHT_GREEN_PIN_ID);
    
    is_button_pressed = FALSE;
	}
	
  // delay loop
	while (Traffic_light_delay_counter-- != 0)
	{
		timer_al_delay(TIMER_DELAY_INTERVAL_IN_MS);
    
    /*if the Pedestrian pressed the button we turn the pedestrian light green immedielty and
     give the pedesterian enough time to cross the street */
    if(is_button_pressed == TRUE)
    {
      // reset the red light timer to give the pedestrians enough time
      Traffic_light_delay_counter = TRAFFIC_LIGHT_DELAYS_COUNT;
      
      led_on(CROSS_WALK_LIGHT_GREEN_PORT_ID, CROSS_WALK_LIGHT_GREEN_PIN_ID);
      led_off(CROSS_WALK_LIGHT_RED_PORT_ID, CROSS_WALK_LIGHT_RED_PIN_ID);
      
      is_button_pressed = FALSE;
    }
	}
			
  // exit the red light state
	led_off(CAR_TRAFFIC_LIGHT_RED_PORT_ID, CAR_TRAFFIC_LIGHT_RED_PIN_ID);
			
	led_off(CROSS_WALK_LIGHT_GREEN_PORT_ID, CROSS_WALK_LIGHT_GREEN_PIN_ID);
  
  led_off(CROSS_WALK_LIGHT_RED_PORT_ID, CROSS_WALK_LIGHT_RED_PIN_ID);
		
}
static void run_car_traffic_light_yellow_to_green_phase()
{
	uint8_t Traffic_light_delay_counter = TRAFFIC_LIGHT_DELAYS_COUNT;
	
  // init car traffic light state
	g_car_traffic_light_state = CAR_TRAFFIC_LIGHT_STATE_YELLOW_TO_GREEN;
	
	led_on(CAR_TRAFFIC_LIGHT_YELLOW_PORT_ID, CAR_TRAFFIC_LIGHT_YELLOW_PIN_ID);
	led_on(CROSS_WALK_LIGHT_RED_PORT_ID, CROSS_WALK_LIGHT_RED_PIN_ID);
  
	if(g_system_mode == SYSTEM_MODE_PEDESTRIAN_CROSSING)
	{
    // In Pedestrian crossing mode the Pedestrian yello led blinks
		led_on(CROSS_WALK_LIGHT_YELLOW_PORT_ID, CROSS_WALK_LIGHT_YELLOW_PIN_ID);
	}
	
  // delay loop
	while (Traffic_light_delay_counter-- != 0)
	{
    
    if(is_button_pressed == TRUE)
    {
      break;      
    }
    
		timer_al_delay( TIMER_DELAY_INTERVAL_IN_MS);
		led_toggle(CAR_TRAFFIC_LIGHT_YELLOW_PORT_ID, CAR_TRAFFIC_LIGHT_YELLOW_PIN_ID);
		
		if(g_system_mode == SYSTEM_MODE_PEDESTRIAN_CROSSING)
		{
			led_toggle(CROSS_WALK_LIGHT_YELLOW_PORT_ID, CROSS_WALK_LIGHT_YELLOW_PIN_ID);
		}
	}
	
  // exit the yellow to green light state
	led_off(CAR_TRAFFIC_LIGHT_YELLOW_PORT_ID, CAR_TRAFFIC_LIGHT_YELLOW_PIN_ID);
	led_off(CROSS_WALK_LIGHT_YELLOW_PORT_ID, CROSS_WALK_LIGHT_YELLOW_PIN_ID);
  led_off(CROSS_WALK_LIGHT_RED_PORT_ID, CROSS_WALK_LIGHT_RED_PIN_ID);

  if(g_system_mode == SYSTEM_MODE_PEDESTRIAN_CROSSING) 
  {
    if ((g_car_traffic_light_state_at_interrupt == CAR_TRAFFIC_LIGHT_STATE_GREEN) || 
    (g_car_traffic_light_state_at_interrupt == CAR_TRAFFIC_LIGHT_STATE_YELLOW_TO_RED) ||
    (g_car_traffic_light_state_at_interrupt == CAR_TRAFFIC_LIGHT_STATE_RED)
    )
    { 
   	  // We have finished the Pedestrian mode handling now. We can return to Normal mode
   	  g_system_mode = SYSTEM_MODE_NORMAL;
    	
    }
    
    if(g_car_traffic_light_state_at_interrupt == CAR_TRAFFIC_LIGHT_STATE_YELLOW_TO_GREEN && is_button_pressed == FALSE)
    {
       // We have finished the Pedestrian mode handling now. We can return to Normal mode
       g_system_mode = SYSTEM_MODE_NORMAL;
    }
    
  }
	
}

// app run function
void app_run(void)
{

	while (1)
	{
		// run the traffic lights states in order
		run_car_traffic_light_green_phase();
		
		run_car_traffic_light_yellow_to_red_phase();
		
		run_car_traffic_light_red_phase();
		
		run_car_traffic_light_yellow_to_green_phase();
		
	}

}


ISR(EXT_INT_0)
{
	// Protect agains long pressing and multiple button presses
	if(g_system_mode != SYSTEM_MODE_PEDESTRIAN_CROSSING)
	{
		// set the state at the interrupt to current traffic light state
		g_car_traffic_light_state_at_interrupt = g_car_traffic_light_state;
    
    // saving that the button has been pressed
    is_button_pressed = TRUE;
  
		// set the system state to pedestrian crossing mode
		g_system_mode = SYSTEM_MODE_PEDESTRIAN_CROSSING;
	}
}
