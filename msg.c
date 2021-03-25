/*
 * message.c
 *
 * Created: 3/25/2021 12:05:40 PM
 *  Author: Asus
 */ 


#include "shrine.h"
#include "msg.h"
#include "list.h"


typedef struct
{
	uint8_t msg_id;
	void * msg_data;
	ListHandle subscriber;
}Msg;





Message MessageCreate(MessageId id, void * message_data)
{
	Msg * msg = ShrineMalloc(sizeof(Msg));
	msg->msg_id = id;
	msg->msg_data = message_data;
	return msg;
}
void MessageDelete(Message msg)
{
	
}


void MessageSetId(Message msg, MessageId id)
{
	
}
MessageId MessageGetId(Message msg)
{
	
}

void MessageSetData(Message msg, void * data)
{
	
}
void * MessageData(Message msg)
{
	
}

