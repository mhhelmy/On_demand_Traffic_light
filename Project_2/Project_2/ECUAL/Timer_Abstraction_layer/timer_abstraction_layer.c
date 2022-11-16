/*
 * timer_abstraction_layer.c
 *
 * Created: 11/11/2022 21:15:02
 *  Author: mhhel
 */ 

#include "timer_abstraction_layer.h"

uint8_t g_available_timer_db[TIMER_ID_MAX]={0};
  
T_ERROR_ID_E timer_al_init(uint8_t system_freq_in_MHz, T_TIMER_ID_E timer_id, T_TIMER_MODE_E timer_mode)
{
  timer_init(system_freq_in_MHz, timer_id, timer_mode);
  // mark this timer as availble
  g_available_timer_db[timer_id] = 1;
  
  return ERROR_ID_NO_ERROR;
  
}

  
T_ERROR_ID_E timer_al_delay(uint16_t timer_delay_in_ms)
{
  uint8_t i;
  
  for (i = 0; i< TIMER_ID_MAX; i++)
  {
    // find an available timer
    if (g_available_timer_db[i] == 1)
    {
      //available timer found, acquire it
       g_available_timer_db[i] = 0;
       break;
    }
  }
  
  if(i == TIMER_ID_MAX)
  {
    // no timer found in the availble timers list
    return ERROR_ID_INSUFFECIENT_RESOURCES;
  }
  timer_delay((T_TIMER_ID_E)i,timer_delay_in_ms);
  
  // return the timer to the availble timers list
  g_available_timer_db[i] = 1;

  return ERROR_ID_NO_ERROR;
}