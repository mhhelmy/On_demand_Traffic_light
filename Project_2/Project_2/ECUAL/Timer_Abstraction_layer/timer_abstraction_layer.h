/*
 * timer_abstraction_layer.h
 *
 * Created: 11/11/2022 21:14:40
 *  Author: mhhel
 */ 


#ifndef TIMER_ABSTRACTION_LAYER_H_
#define TIMER_ABSTRACTION_LAYER_H_

#include "../../Utilities/error_handler.h"
#include "../../Utilities/basetypes.h"
#include "../../MCAL/timer/timer.h"

T_ERROR_ID_E timer_al_init(uint8_t system_freq_in_MHz, T_TIMER_ID_E timer_id, T_TIMER_MODE_E timer_mode);

T_ERROR_ID_E timer_al_delay(uint16_t timer_delay_in_ms);




#endif /* TIMER_ABSTRACTION_LAYER_H_ */