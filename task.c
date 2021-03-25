/*
 * task.c
 *
 * Created: 3/6/2021 8:53:47 PM
 *  Author: Asus
 */ 


#include "shrine.h"
#include "task.h"

typedef struct 
{
	ListHandle msg_list;
}System;



//typedef struct
//{
	//ListHandle msg
//}Task;

System system;

void TaskInitSystem()
{
	system.msg_list = ListCreate(sizeof(Message));
}

TaskHandle TaskCreate(TaskHandlerFunc, uint8_t priority)
{
	
}

void TaskMessageSubscribe(TaskHandle task, Message msg)
{
	
}

void TaskSystemRun()
{

}
