#ifndef __LOOP_QUEUE_H
#define __LOOP_QUEUE_H

#include <stdint.h>
#include <string.h>

typedef struct{
	int size;					// element size by byte
	int quantity; 		// total number of elements
	int head;					// loop queue first element index
	int rear;					// loop queue last element index
	uint8_t *p_array;	// loop queue context pointer
} LoopQueue;

int LoopQueue_GetLength( LoopQueue *p_loop_queue );

int LoopQueue_Pop( LoopQueue *p_loop_queue, uint8_t *element );

int LoopQueue_Force_Push( LoopQueue *p_loop_queue, uint8_t *element );

int LoopQueue_Push( LoopQueue *p_loop_queue, uint8_t *element );

int LoopQueue_Clear( LoopQueue *p_loop_queue );

int LoopQueue_DeInit( LoopQueue *p_loop_queue );

int LoopQueue_Init( LoopQueue *p_loop_queue, uint8_t *p_array, int quantity, int size );

int LoopQueue_Peek( LoopQueue *p_loop_queue, uint8_t *element, int offset );

int LoopQueue_OffsetIndex( LoopQueue *p_loop_queue, int index, int offset );

int LoopQueue_Drop( LoopQueue *p_loop_queue, int length );

#endif // __LOOP_QUEUE_H
