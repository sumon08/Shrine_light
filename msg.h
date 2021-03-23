/*
 * msg.h
 *
 * Created: 3/6/2021 11:51:56 PM
 *  Author: Asus
 */ 


#ifndef MSG_H_
#define MSG_H_

#include <stdint.h>

#define SHRINE_MESSAGE_NOPE						0x00
#define SHRINE_MESSAGE_TIMER					0x01
#define SHRINE_MESSAGE_MEMORY					0x02
#define SHRINE_MESSAGE_USART					0x03
#define SHRINE_MESSAGE_SPI						0x04
#define SHRINE_MESSAGE_TWI						0x05
#define SHRINE_MESSAGE_UNKNOWN					0x06

typedef struct
{
	uint8_t msg_id;
	void * msg_data;
}Message;




#endif /* MSG_H_ */