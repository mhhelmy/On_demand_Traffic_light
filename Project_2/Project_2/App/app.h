/*
 * app.h
 *
 * Created: 05/11/2022 01:06:57
 *  Author: Mohamed Khalil
 */ 


#ifndef APP_H_
#define APP_H_
#include "../Utilities/basetypes.h"
#include "../MCAL/DIO/dio.h"
#include "../ECUAL/Button/button.h"
#include "../ECUAL/LED/led.h"
#include "../MCAL/timer/timer.h"
#include "../ECUAL/Timer_Abstraction_layer/timer_abstraction_layer.h"
#include "../Utilities/interrupt.h"

/************************************************************************/
/* Types                                      */
/************************************************************************/

typedef enum _SYSTEM_MODE
{
	SYSTEM_MODE_NORMAL,
	
	SYSTEM_MODE_PEDESTRIAN_CROSSING
} T_SYSTEM_MODE_E;

typedef enum _CAR_TRAFFIC_LIGHT_STATE
{
	CAR_TRAFFIC_LIGHT_STATE_GREEN,
	
	CAR_TRAFFIC_LIGHT_STATE_YELLOW_TO_RED,
	
	CAR_TRAFFIC_LIGHT_STATE_RED,
	
	CAR_TRAFFIC_LIGHT_STATE_YELLOW_TO_GREEN
} T_CAR_TRAFFIC_LIGHT_STATE_E;


/************************************************************************/
/* Functions declarations                      */
/************************************************************************/


// init function for the application
void app_init(void);

// app run function
void app_run(void);


#endif /* APP_H_ */
