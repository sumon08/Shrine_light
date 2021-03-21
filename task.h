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


typedef ShrineSysCode (*TaskHandlerFunc)(Message msg, void * data);
typedef void * TaskHandle;

TaskHandle TaskCreate(TaskHandlerFunc, uint8_t priority);

#endif /* TASK_H_ */