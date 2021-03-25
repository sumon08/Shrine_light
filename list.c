/*
 * list.c
 *
 * Created: 3/25/2021 12:13:49 PM
 *  Author: Asus
 */ 


#include "shrine.h"
#include "list.h"
#include <string.h>


#define LIST_HEADER_SIZE	sizeof(void *)

typedef struct _list_node
{
	struct _list_node * pNext;
	uint8_t data[];
}ListNode;

typedef struct
{
	uint8_t item_size;
	ListNode * pFront;
	ListNode * pBack;
	ListNode * pFree;
	uint16_t item_available;
	uint16_t total_allocated_block;
}List;



ListHandle ListCreate(uint8_t item_size)
{
	List * lst = ShrineMalloc(sizeof(List));
	if (lst == NULL)
	{
		return NULL;
	}
	lst->item_size = item_size;
	lst->item_available = 0;
	lst->total_allocated_block = 0;
	lst->pFront = NULL;
	lst->pBack = NULL;
	lst->pFree = NULL;
	return lst;
}


void ListDelete(ListHandle lst)
{
	List * ls = (List *)lst;
	ListNode * node = ls->pFree;
	
	while(node != NULL)
	{
		ls->pFree = node->pNext;
		ShrineFree(node);
		node = ls->pFree;
	}
	
	node = ls->pFront;
	while(node != NULL)
	{
		ls->pFront = node->pNext;
		ShrineFree(node);
		node = ls->pFront;
	}
	
	ShrineFree(lst);
}

ListStatus ListInsert(ListHandle lst, void * data)
{
	List * ls = (List *) lst;
	
	ListNode * node = NULL;
	if(ls->pFree != NULL)
	{
		node = ls->pFree;
		ls->pFree = NULL;
	}
	else
	{
		node = ShrineMalloc(ls->item_size + LIST_HEADER_SIZE);
		if(node == NULL)
			return LIST_OUT_OF_MEMORY;
		ls->total_allocated_block++;
	}
	
	memcpy(node->data, data, ls->item_size);
	node->pNext = NULL;
	if (ls->item_available == 0)
	{
		ls->pFront = node;
		ls->pBack = node;
	}
	else
	{
		ls->pBack->pNext = node;
	}
	ls->item_available++;
	return LIST_OK;
}
ListStatus ListRead(ListHandle lst, void * buffer, uint8_t buffer_size)
{
	List * ls = (List *)lst; 
	if (ls->item_size != buffer_size)
	{
		return LIST_BUFFER_ERROR;
	}
	
	if(ls->item_available == 0)
		return LIST_EMPTY;
		
	ListNode * node = ls->pFront;
	ls->pFront = node->pNext;
	ls->item_available --;
	//check if list is empty.
	// pFront should be NULL now. if not there is a problem in code. will add exception code later.
	if (ls->item_available == 0)
	{
		ls->pBack = NULL;
	}
	memcpy(buffer, node->data, ls->item_size);
	// put the node on free list for later use.
	node->pNext = ls->pFree;
	ls->pFree = node;
	return LIST_OK;
}

void ListFlush(ListHandle lst)
{
	List * ls = (List *)lst;
	ListNode * node = ls->pFree;
	while(node != NULL)
	{
		ls->pFree = node->pNext;
		ShrineFree(node);
		ls->total_allocated_block --;
		node = ls->pFree;
	}
}




const ListIterator ListBegin(ListHandle lst)
{
	List * ls = (List *) lst;
	return ls->pFront;
}

const ListIterator ListIterateNext(ListIterator lsti)
{
	ListNode * node = (ListNode *) lsti;
	return node->pNext;
}
void * ListData(ListIterator lsti)
{
	ListNode * node = (ListNode *) lsti;
	return node->data;
}