/**
  ******************************************************************************
  * @file    OWLL.c
  * @author  HCL
  * @version V1.0.0
  * @date    2018-03-23
  * @brief   NONE
  ******************************************************************************
  @verbatim
  *
  @endverbatim
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "OWLL.h"

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/


/* Private constants ---------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Exported variables --------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
/**
  ******************************************************************************
  * @Func: OWLL_Query
  * @Desc: Query a node in a one way linked list
  * @Para: p_head: Pointer of list head node
  *        p_key:  Pointer of the key
  *        p_func_cmp: Pointer of the compare function
  * @Ret:  Not NULL means the pointer of value which the key to
  ******************************************************************************
  */
void* OWLL_Query( OWLL_Node *p_head, void *p_key, OWLL_ValueCompare p_func_cmp )
{
  if( (NULL == p_head)
      || (NULL == p_head->p_key)
      || (NULL == p_key)
      || (NULL == p_func_cmp)
  )
  {
    return NULL;
  }
  else
  {
    OWLL_Node *p_iterator;

    p_iterator = p_head;

    while(  (NULL != p_iterator)
            && (0 != p_func_cmp( p_iterator->p_key, p_key )) )
    {
      p_iterator = p_iterator->p_next;
    }

    return (NULL != p_iterator)? p_iterator->p_value: NULL;
  }
}

/**
  ******************************************************************************
  * @Func: OWLL_Insert
  * @Desc: Insert a node in a one way linked list
  * @Para: p_head: Pointer of list head node
  *        p_key:  Pointer of the key
  *        p_value:  Pointer of the value
  *        p_func_cmp: Pointer of the compare function
  * @Ret:  Not NULL means this operation is successful.
  ******************************************************************************
  */
void* OWLL_Insert( OWLL_Node *p_head, void *p_key, void *p_value, OWLL_ValueCompare p_func_cmp )
{
  if( (NULL == p_head)
      || ( NULL == p_key)
      || ( NULL == p_value)
  )
  {
    return NULL;
  }
  else
  {
    if( NULL != OWLL_Query( p_head, p_key, p_func_cmp ) )
    {
      return NULL;
    }
    else
    {
      if( NULL == p_head->p_key )
      {
        p_head->p_key = p_key;
        p_head->p_value = p_value;
        p_head->p_next = NULL;

        return p_head;
      }
      else
      {
        OWLL_Node *p_iterator;

        p_iterator = p_head;

        /* Search the last node. */
        while( NULL != p_iterator->p_next )
        {
          p_iterator = p_iterator->p_next;
        }

        /* Create a new node. */
        p_iterator->p_next = (OWLL_Node*)malloc( sizeof(OWLL_Node) );

        /* Insert the new node back to the last node. */
        if( NULL == p_iterator->p_next )
        {
          return NULL;
        }
        else
        {
          p_iterator = p_iterator->p_next;

          p_iterator->p_key   = p_key;
          p_iterator->p_value = p_value;
          p_iterator->p_next  = NULL;

          return p_iterator;
        }
      }
    }
  }
}

/**
  ******************************************************************************
  * @Func: OWLL_Scan
  * @Desc: Scan a one way linked list and run the callback
  * @Para: p_head: Pointer of head node
  *        p_callback: The callback function
  * @Ret:  NONE
  ******************************************************************************
  */
void OWLL_Scan( OWLL_Node *p_head, void p_callback( void* ) )
{
  if( (NULL != p_head)
      && (NULL != p_head->p_key)
      && (NULL != p_callback )
  )
  {
    OWLL_Node *p_iterator;

    p_iterator = p_head;

    while( NULL != p_iterator )
    {
      p_callback( p_iterator->p_value );
      p_iterator = p_iterator->p_next;
    }
  }
}

/************************ (C) COPYRIGHT NONE *****END OF FILE****/
