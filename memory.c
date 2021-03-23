/*
 * memory.c
 *
 * Created: 3/9/2021 10:45:06 AM
 *  Author: Asus
 */ 


#include <stdint.h>
#include "shrine.h"
#include <stddef.h>

static uint8_t heap[CONFIG_SHRINE_HEAP_SIZE];

uint16_t pNextPosition = 0;

void * ShrineMalloc(size_t size)
{
	if ((pNextPosition + size) >= CONFIG_SHRINE_HEAP_SIZE )
	{
		return NULL;
	}
	void * ret = heap[pNextPosition];
	pNextPosition += size;
	return ret;
}

void ShrineFree(void * ptr)
{
	//nothing
}
