/*
 * buffer_functions.c
 *
 *  Created on: 11-Nov-2019
 *      Author: Abhijeet
 */
#include "buffer_functions.h"
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fsl_debug_console.h>
uint8_t rw;

enum Error_status result;
/* Function to create buffer */
// Pass a storage buffer and size
enum Error_status create_buffer(uint16_t *buffer_t,user_n *user_t,uint16_t *size)
{
	if(*size>0)
	{
		buffer_t = (uint16_t *)malloc(*size*sizeof(uint8_t));
		if(buffer_t!=NULL)
		{
			result = SUCCESS;
			user_t->buffer = buffer_t;
			user_t->head = buffer_t;
			user_t->tail = buffer_t;
			user_t->maxlen = *size;
		}
		else
		{

			result = FAILURE;
		}
	}
	else
	{

		result = FAILURE;
	}

	return result;
}

/* Reallocate Buffer */
// Function called when original buffer becomes full

enum Error_status overflow_handler(uint16_t *buffer_rt,user_n *user_t,uint16_t size)
{
	size = size + 10;
	if(size>0)
	{
		buffer_rt = (uint16_t *)realloc(buffer_rt,(unsigned int)size*sizeof(uint8_t));
		PRINTF("\n\rrealloc address = %p\n\r",buffer_rt);

		if(buffer_rt!=NULL) //checks if null
		{
			result = SUCCESS;
			user_t->buffer = buffer_rt;
			// Head+last position

			user_t->head = buffer_rt;
			user_t->tail = buffer_rt;
			user_t->maxlen = size;
			PRINTF("\n\rmaxlen = %d\n\r",user_t->maxlen);
			PRINTF("user_t.head = %p\n\r",user_t->head);
			PRINTF("\n\rlast value = %p\n\r",(user_t->buffer + (user_t->maxlen-1)));
		}
		else
		{

			result = FAILURE;
		}
	}
	else
	{
		PRINTF("\n\rEnter size greater than 0\n\r");
		result = FAILURE;
	}

	return result;
}




/*Buffer full Function*/
// Checks if buffer is full

bool buffer_full(user_n *user_t)
{

	return user_t->full;
}



/*Buffer Empty Function*/
// Checks if buffer is empty
// Returns a false when empty

bool buffer_empty(user_n *user_t)
{

	return ((!user_t->full) && (user_t->head==user_t->tail));
}

/* Dummy write to buffer (using SCANF) */
// Write to the head address and advance the head location
// If the buffer is full we need to advance our tail pointer as well as head
// increment head while writing


/* Reset Buffer */
// Set the structure elements to 0
// put head==tail
void buffer_reset(user_n *user_t)
{
	user_t->head = user_t->buffer;
	user_t->tail = user_t->buffer;
	user_t->full = false;

}

/* Destroy Buffer */
// call free on the buffer address
void buffer_destroy(user_n *user_t)
{
	free(user_t->buffer); user_t->buffer=NULL;

}


/* Advance Pointer */
// PASS TAIL and HEAD
void advance_pointer(user_n *user_t)
{
	if(user_t->full)
	{
		user_t->tail++;
		if(user_t->tail == ((user_t->buffer+user_t->maxlen)-1))
		{
			user_t->tail = 0;
		}
	}


	user_t->head++;
	if(user_t->head == ((user_t->buffer+user_t->maxlen)))
	{

		user_t->head = user_t->buffer;
	}


	if(user_t->head==user_t->tail)
		user_t->full=true;
}

/* Retreat Pointer */
// PASS TAIL
void retreat_pointer(user_n *user_t)
{
	user_t->full = false;
	user_t->tail++;
	if(user_t->tail == ((user_t->buffer+user_t->maxlen)))
	{
		user_t->tail = user_t->buffer;
	}
}


int character_count(user_n *user_t)
{
	// rw == 1 while writing
	// rw == 0 while reading
	if(rw == 1)
	{
		user_t->count++;
	}
	else if(rw == 0)
	{
		user_t->count--;
	}

	return user_t->count;
}





int buffer_read(user_n *user_t)
{

	uint8_t readdata = *(user_t->tail);
	retreat_pointer(user_t);

	rw = 0;
	character_count(user_t);
	if(buffer_full(user_t))
	{
		//PRINTF("\n\rBUFFER IS FULL!\n\r");
	}
	if(buffer_empty(user_t))
	{

		return FAILURE;
	}
	return readdata;
}

/* Write to buffer */
// Write to the head address and advance the head location
// If the buffer is full we need to advance our tail pointer as well as head
// increment head while writing
void buffer_write(user_n *user_t, uint8_t writedata, uint16_t size)
{

	buffer_full(user_t);
	*(user_t->head) = writedata;

	advance_pointer(user_t);

	rw = 1;
	character_count(user_t);

}





