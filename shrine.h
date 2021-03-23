/*
 * shrine.h
 *
 * Created: 3/7/2021 8:57:15 PM
 *  Author: Asus
 */ 


#ifndef SHRINE_H_
#define SHRINE_H_

#include <stddef.h>
#include "config.h"



#ifndef NULL
#define NULL 0
#endif


typedef enum 
{
	SHRINE_SYSCODE_OK,
	SHRINE_SYSCODE_ERROR,
	SHRINE_SYSCODE_UNKNOWN,
}ShrineSysCode;





void *	ShrineMalloc(size_t size);
void	ShrineFree(void * ptr);



#endif /* SHRINE_H_ */