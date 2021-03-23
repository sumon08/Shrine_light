/*
 * time.c
 *
 * Created: 3/7/2021 9:38:44 PM
 *  Author: Asus
 */ 


#include "shrine.h"
#include "timer.h"
#include "task.h"

#if (CONFIG_MAX_NUMBER_OF_TIMER < 0x100)
typedef uint8_t TimerId;
#else
typedef uint16_t TimerId;
#endif




typedef struct _Timer
{
	TimerId timer_id;
	uint16_t interval_tick;
	uint16_t aparent_tick;
	TimerType type;
	TimerStatus status;
	TaskHandle * perent_task;
	struct _Timer * pNext;
}Timer;



typedef struct
{
	Timer * pNew;
	Timer * pActive;
	Timer * pExpire;
	Timer * pStopped;
	TimerHardwareInterface * hard;
}TimerManager;

static TimerManager timer_manager;


static void TimerPeriodicHandler()
{
	if (timer_manager.pActive != NULL)
	{
		timer_manager.pActive->aparent_tick --;
		while(timer_manager.pActive->aparent_tick == 0)
		{
			Timer * node = timer_manager.pActive;
			timer_manager.pActive = node->pNext;
			node->pNext = timer_manager.pExpire;
			timer_manager.pExpire = node;
			
		}
	}
}


void TimerInit(TimerHardwareInterface * init)
{
	timer_manager.pNew = 0;
	timer_manager.pActive = NULL;
	timer_manager.pExpire = NULL;
	timer_manager.hard = init;
	if(init != NULL)
		init->tick_init(TimerPeriodicHandler);
}

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
	Timer * tim = (Timer *) handle;
	tim->perent_task = task;
}

void TimerRelease(TimerHandle handle, TaskHandle task)
{
	
}

void TimerDelete(TimerHandle handle)
{
	ShrineFree(handle);
}

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

TimerStatus TimerStart(TimerHandle handle)
{
	Timer * timer = (Timer *)handle;
	timer_manager.hard->tick_disable();
	timer->pNext = timer_manager.pNew;
	timer_manager.pNew = timer; 
	timer_manager.hard->tick_enable();
}

TimerStatus TimerStop(TimerHandle handle)
{
	Timer * timer = (Timer *) handle;
	timer_manager.hard->tick_disable();
	timer->pNext = timer_manager.pStopped;
	timer_manager.pStopped = timer;
	timer_manager.hard->tick_enable();
}


void ExecuteTimerHandler(TimerHandle timer_handle)
{
	
}

void ActivateTimer(Timer * timer)
{
	if (timer->status == SHRINE_TIMER_STATUS_RUNNING)
	{
		return;
	}
	timer->aparent_tick = timer->interval_tick;
	if (timer_manager.pActive == NULL)
	{
		timer_manager.hard->tick_disable();
		timer_manager.pActive = timer;
		timer_manager.hard->tick_enable();
		timer->status = SHRINE_TIMER_STATUS_RUNNING;
	}
	else if(timer_manager.pActive->pNext == NULL)
	{
		timer_manager.hard->tick_disable();
		if(timer_manager.pActive->aparent_tick < timer->aparent_tick)
		{
			timer->aparent_tick -= timer_manager.pActive->aparent_tick;
			timer_manager.pActive->pNext = timer;
			timer->pNext = NULL;
		}
		else
		{
			timer_manager.pActive->aparent_tick -= timer->aparent_tick;
			timer->pNext = timer_manager.pActive;
			timer_manager.pActive = timer;
		}
		timer_manager.hard->tick_enable();
		timer->status = SHRINE_TIMER_STATUS_RUNNING;
	}
	else
	{
		timer_manager.hard->tick_disable();
		if(timer->aparent_tick < timer_manager.pActive)
		{
			timer_manager.pActive->aparent_tick -= timer->aparent_tick;
			timer->pNext = timer_manager.pActive;
			timer_manager.pActive = timer;
			timer_manager.hard->tick_enable();
			timer->status = SHRINE_TIMER_STATUS_RUNNING;
		}
		else
		{
			timer_manager.hard->tick_enable();
			Timer * node = timer_manager.pActive;
			Timer * prev_node = NULL;
			while (1)
			{
				timer->aparent_tick -= node->aparent_tick;
				prev_node = node;
				node = node->pNext;
				if (node->aparent_tick > timer->aparent_tick)
				{
					node->aparent_tick -= timer->aparent_tick;
					timer->pNext = node;
					prev_node->pNext = timer;
					timer->status = SHRINE_TIMER_STATUS_RUNNING;
					return;
				}
				
				if (node->pNext == NULL)
				{
					node->pNext = timer;
					timer->aparent_tick -= node->aparent_tick;
					timer->pNext = NULL;
					timer->status = SHRINE_TIMER_STATUS_RUNNING;
					break;
				}
			}
		}
		
	}
}

void DectivateTimer(Timer * timer)
{
	if (timer->status |= SHRINE_TIMER_STATUS_RUNNING)
	{
		return;
	}
	if (timer == timer_manager.pActive)
	{
		timer_manager.hard->tick_disable();
		timer_manager.pActive = timer->pNext;
		timer_manager.pActive->aparent_tick += timer->aparent_tick;
		timer_manager.hard->tick_enable();
		timer->status = SHRINE_TIMER_STATUS_STOPPED;
	}
	else if(timer_manager.pActive->pNext == timer)
	{
		if(timer->pNext != NULL)
		{
			timer->pNext->aparent_tick += timer->aparent_tick;
			timer_manager.pActive->pNext = timer->pNext;
		}
		else
		{
			timer_manager.pActive->pNext = NULL;
		}
		timer->status = SHRINE_TIMER_STATUS_STOPPED;
	}
	else
	{
		Timer * node = timer_manager.pActive->pNext->pNext;
		Timer * prev_node = timer_manager.pActive->pNext;
		while(1)
		{
			if(node == timer)
			{
				node->pNext->aparent_tick += node->aparent_tick;
				prev_node->pNext = node->pNext;
				timer->status = SHRINE_TIMER_STATUS_STOPPED;
				return;
			}
			prev_node = node;
			node = node->pNext;
			if (node == NULL)
			{
				timer->status = SHRINE_TIMER_STATUS_STOPPED;
				return;
			}
		}
	}
}

void ManageTimer()
{
	while(timer_manager.pExpire != NULL)
	{
		extern void ExecuteTimerHandler(TimerHandle);
		ExecuteTimerHandler(timer_manager.pExpire);
		Timer * timer = (Timer *) timer_manager.pExpire;
		if (timer->type == SHRINE_TIMER_TYPE_REPEAT)
		{
			timer->status = SHRINE_TIMER_STATUS_EXPIRED;
			ActivateTimer(timer);
		}
	}
	
	while(timer_manager.pNew != NULL)
	{
		ActivateTimer(timer_manager.pNew);
		timer_manager.pNew = timer_manager.pNew->pNext;
	}
}
