/*
 * timer.c
 *
 * Created: 06/11/2022 22:38:19
 *  Author: Mohamed Khalil
 */ 

#include "timer.h"

// TODO: base timer calculation on the system freq. Currently I assume 1 MHZ 
//uint32_t g_system_freq;

void timer_init(uint8_t system_freq_in_MHz, T_TIMER_ID_E timer_id, T_TIMER_MODE_E timer_mode)
{
	// TODO: base timer calculation on the system freq. Currently I assume 1 MHZ 
	// It is not a problem if the same value initialized with each timer.
	//g_system_freq = system_freq_in_MHz << 20;
	
	switch (timer_id)
	{
		case TIMER_ID_0:
		// TODO switch on timer modes enum and choose timer mode and interrupt flags properly
		
		// normal mode
		REG_TCCR0 = 0;
		
		// initialize timer count by 0
		REG_TCNT0 = 0;
		
		break;
		
		// TODO: complete other timers initialization
		case TIMER_ID_1:
		break;
		case TIMER_ID_2:
		break;
		default:
		break;	
	
		
	}
	
	
	
}

void timer_delay (T_TIMER_ID_E timer_id, uint16_t timer_delay_in_ms)
{
	// TODO: base timer calculation on the system freq. Currently I assume 1 MHZ 
	
	uint16_t timer_full_cycles;
	uint8_t timer_remaining_cycles;
	
	if (timer_delay_in_ms == 0)
		return;
	
	// how many full cycles of 256 ms we have
	timer_full_cycles = timer_delay_in_ms / 256;
	timer_remaining_cycles = timer_delay_in_ms % 256; 
	

	if(timer_full_cycles != 0)
	{
		// 1024 pre-scaling
		REG_TCCR0 = 5;
			
		while (timer_full_cycles != 0)
		{
			while (read_bit_8_bit_field(REG_TIFR, 0) == 0)
			{
				// wait;
			}
			
			REG_TIFR |= (1<< 0);
			
			timer_full_cycles --;
		}
		
		REG_TCCR0 = 0;

	}
	
	if(timer_remaining_cycles != 0)
	{
		REG_TCNT0 = 256 - timer_remaining_cycles;
		
		// 1024 pre-scaling
		REG_TCCR0 = 5;
		
		while (read_bit_8_bit_field(REG_TIFR, 0) == 0)
		{
			// wait;
		}
		
		REG_TIFR |= (1<< 0);
		REG_TCCR0 = 0;
	}

}