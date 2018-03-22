#include "LoopQueue.h"

static int _LoopQueue_Next_Cycle_Index( LoopQueue *p_loop_queue, int index )
{
	return (index+1) % p_loop_queue->quantity;
}


int LoopQueue_OffsetIndex( LoopQueue *p_loop_queue, int index, int offset )
{
  offset %= p_loop_queue->quantity;
  if( offset < 0 )
  {
    offset += p_loop_queue->quantity;
  }
	return (index+offset) % p_loop_queue->quantity;
}

int LoopQueue_Init( LoopQueue *p_loop_queue, uint8_t *p_array, int quantity, int size )
{
	if( p_loop_queue != NULL )
	{
		if( p_array != NULL )
		{
			if( quantity > 0 )
			{
				if( size > 0 )
				{
					p_loop_queue->p_array = p_array;
					p_loop_queue->quantity = quantity;
					p_loop_queue->size = size;

					p_loop_queue->head = 0;
					p_loop_queue->rear = 0;

					return 0;
				}
				else
				{
					return 4;
				}
			}
			else
			{
				return 3;
			}
		}
		else
		{
			return 2;
		}
	}
	else
	{
		return 1;
	}
}

int LoopQueue_DeInit( LoopQueue *p_loop_queue )
{
	if( p_loop_queue != NULL )
	{
		p_loop_queue->p_array = NULL;
		p_loop_queue->quantity = 0;
		p_loop_queue->size = 0;

		p_loop_queue->head = 0;
		p_loop_queue->rear = 0;
		return 0;
	}
	else
	{
		return 1;
	}
}

int LoopQueue_Clear( LoopQueue *p_loop_queue )
{
	if( p_loop_queue != NULL )
	{
		p_loop_queue->head = 0;
		p_loop_queue->rear = 0;
		return 0;
	}
	else
	{
		return 1;
	}
}

int LoopQueue_Push( LoopQueue *p_loop_queue, uint8_t *element )
{
	if( p_loop_queue != NULL )
	{
		int next_rear;

		next_rear = _LoopQueue_Next_Cycle_Index( p_loop_queue, p_loop_queue->rear );
		if( next_rear != p_loop_queue->head)
		{
			memcpy( (void*)&(p_loop_queue->p_array[ p_loop_queue->rear*p_loop_queue->size ]), (void*)element, p_loop_queue->size );
			p_loop_queue->rear = next_rear;

			return 0;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		return 1;
	}
}

int LoopQueue_Force_Push( LoopQueue *p_loop_queue, uint8_t *element )
{
	if( p_loop_queue != NULL )
	{
		int next_rear;

		next_rear = _LoopQueue_Next_Cycle_Index( p_loop_queue, p_loop_queue->rear );
		if( next_rear != p_loop_queue->head)
		{

			memcpy( (void*)&(p_loop_queue->p_array[ p_loop_queue->rear*p_loop_queue->size ]), (void*)element, p_loop_queue->size );
			p_loop_queue->rear = next_rear;
		}
		else
		{
			memcpy( (void*)&(p_loop_queue->p_array[ p_loop_queue->rear*p_loop_queue->size ]), (void*)element, p_loop_queue->size );
			p_loop_queue->rear = next_rear;
			p_loop_queue->head = _LoopQueue_Next_Cycle_Index( p_loop_queue, p_loop_queue->head );
		}
		return 0;
	}
	else
	{
		return 1;
	}
}

int LoopQueue_Pop( LoopQueue *p_loop_queue, uint8_t *element )
{
	if( p_loop_queue != NULL )
	{
		if( p_loop_queue->head != p_loop_queue->rear )
		{
			memcpy( (void*)element, (void*)&(p_loop_queue->p_array[ p_loop_queue->head*p_loop_queue->size ]), p_loop_queue->size );
			p_loop_queue->head = _LoopQueue_Next_Cycle_Index( p_loop_queue, p_loop_queue->head );

			return 0;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		return 1;
	}
}

int LoopQueue_GetLength( LoopQueue *p_loop_queue )
{
	if( p_loop_queue != NULL )
	{
		if( p_loop_queue->rear >= p_loop_queue->head )
		{
			return p_loop_queue->rear-p_loop_queue->head;
		}
		else
		{
			return p_loop_queue->rear+p_loop_queue->quantity - p_loop_queue->head;
		}
	}
	else
	{
		return 0;
	}
}

int LoopQueue_Peek( LoopQueue *p_loop_queue, uint8_t *element, int offset )
{
	if( p_loop_queue != NULL )
	{
	  if( ( offset >= 0 )
        && ( LoopQueue_GetLength( p_loop_queue ) > offset )
    )
  	{
      int offset_index;

      offset_index = LoopQueue_OffsetIndex( p_loop_queue, p_loop_queue->head, offset );
			memcpy( (void*)element, (void*)&(p_loop_queue->p_array[ offset_index*p_loop_queue->size ]), p_loop_queue->size );

			return 0;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		return 1;
	}
}


int LoopQueue_Drop( LoopQueue *p_loop_queue, int length )
{
	if( p_loop_queue != NULL )
	{
	  if( ( length > 0 )
        && ( LoopQueue_GetLength( p_loop_queue ) >= length )
    )
  	{
      p_loop_queue->head = LoopQueue_OffsetIndex( p_loop_queue, p_loop_queue->head, length );
			return 0;
		}
		else
		{
			return 2;
		}
	}
	else
	{
		return 1;
	}
}


