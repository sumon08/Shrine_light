/*
 * list.h
 *
 * Created: 3/25/2021 12:13:41 PM
 *  Author: Asus
 */ 


#ifndef LIST_H_
#define LIST_H_

#include <stdint.h>

typedef void * ListHandle;
typedef void * ListIterator;


typedef enum
{
	LIST_UNKNOWN,
	LIST_OK,
	LIST_EMPTY,
	LIST_OUT_OF_MEMORY,
	LIST_BUFFER_ERROR
}ListStatus;


/**
 * \brief 
 * 
 * \param item_size
 * 
 * \return ListHandle
 */
ListHandle ListCreate(uint8_t item_size);

/**
 * \brief 
 * Be careful when deleting list. if data is pointer type you must read all item available delete data manually.
 * But for any other data type you can delete list without reading all item.
 * \param lst
 * 
 * \return void
 */
void ListDelete(ListHandle lst);

/**
 * \brief 
 * 
 * \param lst
 * \param data
 * 
 * \return ListStatus
 */
ListStatus ListInsert(ListHandle lst, void * data);


/**
 * \brief 
 * 
 * \param lst
 * \param buffer
 * \param buffer_size
 * 
 * \return ListStatus
 */
ListStatus ListRead(ListHandle lst, void * buffer, uint8_t buffer_size);



/**
 * \brief 
 * 
 * \param lst
 * 
 * \return void
 */
void ListFlush(ListHandle lst);



void ListItemDelete(ListHandle lst, void * list_item);

//API for iteration over list without deleting.

const ListIterator ListBegin(ListHandle lst);
const ListIterator ListIterateNext(ListIterator lsti);
void * ListData(ListIterator lsti);

#endif /* LIST_H_ */