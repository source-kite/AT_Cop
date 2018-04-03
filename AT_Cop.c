/**
  ******************************************************************************
  * @file    AT_Cop.c
  * @author  HCL
  * @version V1.0.0
  * @date    19-May-2018
  * @brief   AT command processor.
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
#include "AT_Cop.h"
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/


/* Private constants ---------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
static AT_Object* AT_Cop_DicQuery( AT_ProcessorHandle *h_at_processor, char *p_at_str )
{
  char ch;
  uint32_t hash;
  uint32_t str_length;
  AT_Object *p_at_object;

  str_length = strlen( p_at_str );

  do
  {
    ch = p_at_str[ str_length ];
    p_at_str[ str_length ] = '\0';

    hash = BKDR_Hash( (uint8_t*)p_at_str, str_length, AT_HASH_SEED ) % AT_HASH_MAX;
    p_at_object = OWLL_Query( &h_at_processor->hash_base[ hash ], p_at_str, (OWLL_ValueCompare)strcmp );

    p_at_str[ str_length ] = ch;


  } while( ( NULL == p_at_object)
          && (str_length --)
  );

  return p_at_object;
}

static AT_Object* AT_Cop_DicQueryStrict( AT_ProcessorHandle *h_at_processor, char *p_at_str )
{
  uint32_t hash;

  hash = BKDR_Hash( (uint8_t*)p_at_str, strlen( p_at_str ), AT_HASH_SEED ) % AT_HASH_MAX;

  return OWLL_Query( &h_at_processor->hash_base[ hash ], p_at_str, (OWLL_ValueCompare)strcmp );
}


static AT_Object* AT_Cop_DicInsert( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Object* p_value )
{
  uint32_t hash;

  hash = BKDR_Hash( (uint8_t*)p_at_str, strlen( p_at_str ), AT_HASH_SEED ) % AT_HASH_MAX;

  return OWLL_Insert( &h_at_processor->hash_base[ hash ], p_at_str, p_value, (OWLL_ValueCompare)strcmp );
}

/**
  ******************************************************************************
  * @Func: AT_Cop_BuildDic
  * @Desc: Build the dictionary by at objects
  * @Para: h_at_processor: Pointer of a at processor
  *        at_object_list: The list of at objects
  *        list_length: the length of objects
  * @Ret:  Not NULL means this operation is successful.
  ******************************************************************************
  */
static AT_ProcessorHandle* AT_Cop_BuildDic( AT_ProcessorHandle *h_at_processor, AT_Object at_object_list[], int list_length )
{
  if( (NULL == h_at_processor)
      || (NULL == at_object_list)
      || (0 == list_length )
  )
  {
    return NULL;
  }
  else
  {
    h_at_processor->at_object_list = at_object_list;
    h_at_processor->at_object_list_length = list_length;

    memset( &h_at_processor->hash_base, 0, sizeof( h_at_processor->hash_base ) );

    for( int i = 0; i < h_at_processor->at_object_list_length; i ++ )
    {
      AT_Cop_DicInsert( h_at_processor, h_at_processor->at_object_list[ i ].p_at_str, (void*)&h_at_processor->at_object_list[ i ] );
    }
    return h_at_processor;
  }
}

/**
  ******************************************************************************
  * @Func: AT_Cop_PreParser
  * @Desc: Split data flow as at string.
  * @Para: h_at_processor: Pointer of a at processor
  *        p_at_str: The buffer which will used to store a at string.
  * @Ret:  Not NULL means this operation is successful.
  ******************************************************************************
  */
static char*  AT_Cop_PreParser( AT_ProcessorHandle *h_at_processor, char* p_at_str )
{
  char byte_data;
  int str_length;
  int loop_queue_ret;

  /* Recognition divide character and drop therm */
  str_length = 0;
  while(  (AT_STR_SIZE >  str_length)
          && (0 == (loop_queue_ret = LoopQueue_Peek( &h_at_processor->rx_buffer_queue, (uint8_t*)&byte_data, str_length ))) )
  {
    if( ('\r' != byte_data)
        && ('\n' != byte_data)
    )
    {
      LoopQueue_Drop( &h_at_processor->rx_buffer_queue, str_length );
      break;
    }
    else
    {
      str_length ++;
    }
  }

  if( AT_STR_SIZE >  str_length )
  {
    if( 0 != loop_queue_ret )
    {
      return NULL;
    }
  }
  else
  {
    LoopQueue_Drop( &h_at_processor->rx_buffer_queue, AT_STR_SIZE );
    return NULL;
  }

  /* Recognition AT cmd character and save therm. */
  str_length = 0;
  while(  (AT_STR_SIZE > str_length)
          && (0 == (loop_queue_ret = LoopQueue_Peek( &h_at_processor->rx_buffer_queue, (uint8_t*)&byte_data, str_length )))
  )
  {
    if( ('\r' == byte_data)
        || ('\n' == byte_data)
    )
    {
      p_at_str[ str_length ] = '\0';
      LoopQueue_Drop( &h_at_processor->rx_buffer_queue, str_length );
      break;
    }
    else
    {
      p_at_str[ str_length ] = byte_data;
      str_length ++;
    }
  }
  
  if( AT_STR_SIZE > str_length )
  {
    if( 0 != loop_queue_ret )
    {
      return NULL;
    }
    else
    {
      return p_at_str;
    }
  }
  else
  {
    LoopQueue_Drop( &h_at_processor->rx_buffer_queue, AT_STR_SIZE );
    return NULL;
  }
}

/**
  ******************************************************************************
  * @Func: AT_Cop_Parser
  * @Desc: Parse a at string.
  * @Para: h_at_processor: Pointer of a at processor
  *        p_at_str: The buffer of a at string.
  * @Ret:  Not NULL means this operation is successful.
  ******************************************************************************
  */
static AT_Object* AT_Cop_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str )
{
  AT_Object *p_at_object;

  p_at_object = AT_Cop_DicQuery( h_at_processor, p_at_str );

  if( NULL != p_at_object )
  {
    if( NULL != p_at_object->p_parser )
    {
      if( 1 == p_at_object->p_parser( h_at_processor, p_at_str, p_at_object->p_executor ) )
      {
        if( NULL != h_at_processor->p_success_handler )
        {
          h_at_processor->p_success_handler( p_at_str );
        }
      }
      else
      {
        if( NULL != h_at_processor->p_exception_handler )
        {
          h_at_processor->p_exception_handler( p_at_str );
        }
      }
    }
  }
  else
  {
    if( NULL != h_at_processor->p_exception_handler )
    {
      h_at_processor->p_exception_handler( p_at_str );
    }
  }
  return p_at_object;
}

/* Functions -----------------------------------------------------------------*/
/**
  ******************************************************************************
  * @Func: AT_Cop_Init
  * @Desc: Initial a at processor.
  * @Para: h_at_processor: Pointer of a at processor
  *        at_object_list: The list of at objects
  *        list_length: the length of objects
  *        p_rx_buffer: The buffer of rx data
  *        rx_buffer_size: The size of rx buffer
  *        p_tx_sender: data transmiter
  * @Ret:  Not NULL means this operation is successful
  ******************************************************************************
  */
AT_ProcessorHandle* AT_Cop_Init(  AT_ProcessorHandle *h_at_processor,
                                  AT_Object at_object_list[],
                                  int list_length,
                                  char *p_rx_buffer,
                                  int rx_buffer_size,
                                  int (*p_tx_sender)( uint8_t *, uint32_t ) )
{
  if( NULL != AT_Cop_BuildDic( h_at_processor, at_object_list, list_length ) )
  {
    if( 0 == LoopQueue_Init( &h_at_processor->rx_buffer_queue, (uint8_t*)p_rx_buffer, rx_buffer_size, 1 ) )
    {
      if( NULL != p_tx_sender )
      {
        h_at_processor->p_tx_sender = p_tx_sender;
        h_at_processor->p_success_handler = NULL;
        h_at_processor->p_exception_handler = NULL;

        return h_at_processor;
      }
    }
  }

  return NULL;
}

/**
  ******************************************************************************
  * @Func: AT_Cop_UpdateParser
  * @Desc: Update a at object's executor
  * @Para: h_at_processor: Pointer of a at processor
  *        p_at_str: The buffer of a at string.
  *        p_executor: The executor
  * @Ret:  Not NULL means this operation is successful.
  ******************************************************************************
  */
AT_Object* AT_Cop_UpdateExecutor( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor )
{
  AT_Object *p_at_object;

  p_at_object = AT_Cop_DicQueryStrict( h_at_processor, p_at_str );

  if( NULL == p_at_object )
  {
    return NULL;
  }
  else
  {
    p_at_object->p_executor = p_executor;
    return p_at_object;
  }
}

/**
  ******************************************************************************
  * @Func: AT_Cop_Processor
  * @Desc: Processor of at data flow.
  * @Para: h_at_processor: Pointer of a at processor
  * @Ret:  NONE
  ******************************************************************************
  */
void AT_Cop_Processor( AT_ProcessorHandle *h_at_processor )
{
  while( NULL != AT_Cop_PreParser( h_at_processor, h_at_processor->at_rx_str ) )
  {
    AT_Cop_Parser( h_at_processor, h_at_processor->at_rx_str );
  }
}

/**
  ******************************************************************************
  * @Func: AT_Cop_Rx
  * @Desc: Store data.
  * @Para: h_at_processor: Pointer of a at processor
  *        byte_data: data.
  * @Ret:  NONE
  ******************************************************************************
  */
void AT_Cop_Rx( AT_ProcessorHandle *h_at_processor, char byte_data )
{
  if( NULL != h_at_processor )
  {
    LoopQueue_Push( &h_at_processor->rx_buffer_queue, (uint8_t*)&byte_data );
  }
}

/**
  ******************************************************************************
  * @Func: AT_Cop_Tx
  * @Desc: Transmit data with AT format.
  * @Para: h_at_processor: Pointer of a at processor
  *        format: data format
  *        ...: variable parameters
  * @Ret:  length of data transmit out.
  ******************************************************************************
  */
int AT_Cop_Tx( AT_ProcessorHandle *h_at_processor, const char *format, ... )
{
  int length;

  if( (NULL != h_at_processor)
      && (NULL != h_at_processor->p_tx_sender)
  )
  {
    va_list args;

    va_start( args, format );

    length = vsnprintf( h_at_processor->at_tx_str, AT_STR_SIZE, format, args );

    va_end( args );

    if( (length > 0)
        && (length < AT_STR_SIZE)
    )
    {
      length = h_at_processor->p_tx_sender( (uint8_t*)h_at_processor->at_tx_str, length );
    }
  }
  else
  {
    length = 0;
  }
  return length;
}

/************************ (C) COPYRIGHT NONE *****END OF FILE****/
