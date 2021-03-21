/*
 * time.c
 *
 * Created: 3/7/2021 9:38:44 PM
 *  Author: Asus
 */ 


#include "shrine.h"
#include "timer.h"

#if (CONFIG_MAX_NUMBER_OF_TIMER < 0x100)
typedef uint8_t TimerId;
#else
typedef uint16_t TimerId;
#endif


typedef struct
{
	TimerId timer_id;
	uint16_t interval_tick;
	TimerType type;
	TimerStatus status;
}Timer;

TimerHandle TimerCreate(TimerType type, TimerTick interval)
{
	static TimerId timer_id = 0; 
	Timer * timer = ShrineMalloc(sizeof(Timer));
	timer->interval_tick = interval;
	timer->status = SHRINE_TIMER_STATUS_UNKNOWN;
	timer->timer_id = timer_id++;
}

void TimerRegister(TimerHandle handle, TaskHandle task)
{

}

void TimerRelease(TimerHandle handle, TaskHandle task)
{
	
}

void TimerDelete(TimerHandle handle)
{
	
}

//void TimerStatusSet(TimerHandle handle, TimerStatus status)
//{
	//Timer * timer = (Timer*)handle;
	//timer->status;
//}

void TimerIntervalSet(TimerHandle handle, TimerTick tick)
{
	Timer * timer = (Timer*)handle;
	timer->interval_tick = tick;
}

void TimerTypeSet(TimerHandle handle, TimerType type)
{
	Timer * timer = (Timer*)handle;
	timer->type = type;
}

TimerStatus TimerStatusGet(TimerHandle handle)
{
	Timer * timer = (Timer*)handle;
	return timer->status;
}

TimerTick TimerIntervalGet(TimerHandle handle)
{
	Timer * timer = (Timer*)handle;
	return timer->interval_tick;
}

TimerType TimerTypeGet(TimerHandle handle)
{
	Timer * timer = (Timer*)handle;
	return timer->type;
}

