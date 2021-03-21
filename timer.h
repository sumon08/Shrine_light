/*
 * timer.h
 *
 * Created: 3/7/2021 9:38:15 PM
 *  Author: Asus
 */ 


#ifndef TIMER_H_
#define TIMER_H_






typedef void *		TimerHandle;
typedef uint16_t	TimerTick;

typedef enum
{
	SHRINE_TIMER_TYPE_NONE,
	SHRINE_TIMER_TYPE_ONCE,
	SHRINE_TIMER_TYPE_REPEAT
}TimerType;

typedef enum
{
	SHRINE_TIMER_STATUS_UNKNOWN,
	SHRINE_TIMER_STATUS_RUNNING,
	SHRINE_TIMER_STATUS_STOPPED,
	SHRINE_TIMER_STATUS_EXPIRED
}TimerStatus;


TimerHandle TimerCreate(TimerType type, TimerTick interval);
void TimerRegister(TimerHandle handle, TaskHandle task);
void TimerRelease(TimerHandle handle, TaskHandle task);
void TimerDelete(TimerHandle handle);


//void TimerStatusSet(TimerHandle handle, TimerStatus status);
void TimerIntervalSet(TimerHandle handle, TimerTick tick);
void TimerTypeSet(TimerHandle handle, TimerType type);

TimerStatus TimerStatusGet(TimerHandle timer);
TimerTick TimerIntervalGet(TimerHandle handle);
TimerType TimerTypeGet(TimerHandle handle);

#endif /* TIMER_H_ */