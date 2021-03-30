/*
 * task.c
 *
 * Created: 3/6/2021 8:53:47 PM
 *  Author: Asus
 */ 


#include "config.h"
#include "shrine.h"
#include "task.h"
#include "list.h"
#include "msg.h"
#include "timer.h"

typedef struct 
{
	ListHandle msg_list;
	ListHandle task_list;
	ListHandle published_msg;
}System;



typedef struct
{
	char * name[CONFIG_MAX_NAME_LENGTH];
	TaskHandlerFunc task_func;
	TaskPriority priority;	 
}Task;



typedef struct
{
	uint8_t msg_id;
	ListHandle subscriber;
}Msg;

typedef struct
{
	Msg * perent;
	void * message_data;
}MessageNode;





System system;

void TaskInitSystem()
{
	system.msg_list = ListCreate(sizeof(Message));
	system.task_list = ListCreate(sizeof(TaskHandle));
	system.published_msg = ListCreate(sizeof(MessageNode));
}

TaskHandle TaskCreate(TaskHandlerFunc func, TaskPriority priority, const char * name)
{
	Task * task = ShrineMalloc(sizeof(Task));
	task->priority = priority;
	task->task_func = func;
	ListInsert(system.task_list, task);
	return task;
}

void TaskMessageSubscribe(TaskHandle task, Message msg)
{
	Msg * _msg = (Message *)msg;
	ListInsert(_msg->subscriber, task);
}

void TaskMessageUnsubscribe(TaskHandle task, Message msg)
{
	Msg * _msg = (Message *)msg;
	ListItemDelete(_msg->subscriber, task);
}


void ExecuteTimerHandler(TimerHandle timer_handle)
{
	extern TaskHandle TimerGetPerent(TimerHandle);
	
	Task * tsk = TimerGetPerent(timer_handle);
	Msg msg;
	msg.msg_id = SHRINE_MESSAGE_TIMER; 
	tsk->task_func(msg, NULL);
	
}

TaskHandle TaskHandleGet(const char * name)
{
	
}

const char * TaskNameGet(TaskHandle task)
{
	
}

void MessagePublish(Message msg, void * msg_data)
{
	MessageNode node;
	node.message_data = msg_data;
	node.perent = msg;
	ListInsert(system.published_msg, node);
}

void TaskSystemRun()
{
	extern void ManageTimer();
	ManageTimer();
	
	MessageNode node;
	ListStatus status = ListRead(system.published_msg, &node, sizeof(MessageNode));
	
	if(status == LIST_OK)
	{
		Msg * msg = node.perent;
		ListIterator it = ListBegin(msg->subscriber);
		while(it != NULL)
		{
			Task * task = ListData(it);
			task->task_func(msg->msg_id, node.message_data);
			it = ListIterateNext(it);
		}
	}
	
}








Message MessageCreate(MessageId id)
{
	Msg * msg = ShrineMalloc(sizeof(Msg));
	msg->msg_id = id;
	msg->subscriber = ListCreate(sizeof(TaskHandle));
	return msg;
}
void MessageDelete(Message msg)
{
	
}


void MessageSetId(Message msg, MessageId id)
{
	Msg * _msg = (Msg *) msg;
	_msg->msg_id = id;
}
MessageId MessageGetId(Message msg)
{
	Msg * _msg = (Msg *) msg;
	return _msg->msg_id;
}
