/*
 * msg.h
 *
 * Created: 3/6/2021 11:51:56 PM
 *  Author: Asus
 */ 


#ifndef MSG_H_
#define MSG_H_

#include <stdint.h>
#include "list.h"

#define SHRINE_MESSAGE_NOPE						0x00
#define SHRINE_MESSAGE_TIMER					0x01
#define SHRINE_MESSAGE_MEMORY					0x02
#define SHRINE_MESSAGE_USART					0x03
#define SHRINE_MESSAGE_SPI						0x04
#define SHRINE_MESSAGE_TWI						0x05
#define SHRINE_MESSAGE_UNKNOWN					0x06


typedef uint8_t MessageId;

typedef void * Message;




void InitMsgService();

Message MessageCreate(MessageId id, void * message_data);
void MessageDelete(Message msg);


void MessageSetId(Message msg, MessageId id);
MessageId MessageGetId(Message msg);

void MessageSetData(Message msg, void * data);
void * MessageData(Message msg);

#endif /* MSG_H_ */