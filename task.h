/*
 * task.h
 *
 * Created: 3/6/2021 8:53:35 PM
 *  Author: Asus
 */ 


#ifndef TASK_H_
#define TASK_H_


#include "shrine.h"
#include "msg.h"


typedef ShrineSysCode (*TaskHandlerFunc)(MessageId msg, void * data);


typedef void * TaskHandle;
typedef uint8_t TaskPriority;

void TaskInitSystem();

TaskHandle TaskCreate(TaskHandlerFunc func, TaskPriority priority, const char * name);
void TaskMessageSubscribe(TaskHandle task, Message msg);
void TaskMessageUnsubscribe(TaskHandle task, Message msg);

TaskHandle TaskHandleGet(const char * name);
const char * TaskNameGet(TaskHandle task);


void TaskSystemRun();

#endif /* TASK_H_ */