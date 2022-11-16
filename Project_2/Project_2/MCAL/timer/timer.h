/*
 * timer.h
 *
 * Created: 06/11/2022 22:38:05
 *  Author: Mohamed Khalil
 */ 


#ifndef TIMER_H_
#define TIMER_H_

#include "../../Utilities/basetypes.h"
#include "../../Utilities/bitwise_operations.h"
#include "../registers.h"


/************************************************************************/
/* Types                                      */
/************************************************************************/
typedef enum _TIMER_ID
{
	TIMER_ID_0,
	TIMER_ID_1,
	TIMER_ID_2,
  TIMER_ID_MAX
} T_TIMER_ID_E ;

typedef enum _TIMER_MODE
{
	TIMER_MODE_DELAY,
	TIMER_MODE_CALLBACK_AT_EXPIRY,
	TIMER_MODE_CTC,
	TIMER_MODE_PWM
} T_TIMER_MODE_E;

/************************************************************************/
/* Functions declarations                      */
/************************************************************************/
void timer_init(uint8_t system_freq_in_MHz, T_TIMER_ID_E timer_id, T_TIMER_MODE_E timer_mode);

void timer_delay (T_TIMER_ID_E timer_id, uint16_t timer_delay_in_ms);



#endif /* TIMER_H_ */
