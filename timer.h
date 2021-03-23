/*
 * timer.h
 *
 * Created: 3/7/2021 9:38:15 PM
 *  Author: Asus
 */ 


#ifndef TIMER_H_
#define TIMER_H_


#include "task.h"



typedef void *		TimerHandle;
typedef uint16_t	TimerTick;




typedef void (*TimerHandlerHardware)();

typedef void (*TimerEnableTick)();
typedef void (*TimerDisableTick)();
typedef void (*TimerHardwareInit)(TimerHandlerHardware hard_timer);

typedef struct
{
	TimerEnableTick		tick_enable;
	TimerDisableTick	tick_disable;
	TimerHardwareInit	tick_init;
}TimerHardwareInterface;

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


void TimerInit(TimerHardwareInterface * init);


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

TimerStatus TimerStart(TimerHandle handle);
TimerStatus TimerStop(TimerHandle handle);


#endif /* TIMER_H_ */