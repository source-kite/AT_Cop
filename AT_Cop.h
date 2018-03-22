/**
  ******************************************************************************
  * @file    AT_Cop.h
  * @author  HCL
  * @version V1.0.0
  * @date    19-May-2017
  * @brief   AT command processor.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _AT_COP_H
#define _AT_COP_H

/* Includes ------------------------------------------------------------------*/
#include "TrieTree.h"
#include "LoopQueue.h"


/* Exported macro ------------------------------------------------------------*/
#define AT_STR_SIZE     (64)

/* Exported types ------------------------------------------------------------*/

typedef struct AT_ProcessorHandle_Typedef     AT_ProcessorHandle;
typedef struct AT_Object_Typedef              AT_Object;
typedef void  (*AT_Cop_Executor)( AT_ProcessorHandle *, ... );

struct AT_Object_Typedef
{
  char *p_at_str;
  void (*p_parser)  ( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor );
  AT_Cop_Executor p_executor;
};

struct AT_ProcessorHandle_Typedef
{
  TrieTree_Node trie_root;

  AT_Object *at_object_list;
  int at_object_list_length;

  char at_rx_str[ AT_STR_SIZE ];
  LoopQueue rx_buffer_queue;

  char at_tx_str[ AT_STR_SIZE ];
  int (*p_tx_sender)( uint8_t*, uint32_t );

  void (*p_exception_handler)( char * );
};

/* Exported constants prototypes ---------------------------------------------*/

/* Exported variables prototypes ---------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
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
int AT_Cop_Tx( AT_ProcessorHandle *h_at_processor, const char *format, ... );

/**
  ******************************************************************************
  * @Func: AT_Cop_Rx
  * @Desc: Store data.
  * @Para: h_at_processor: Pointer of a at processor
  *        byte_data: data.
  * @Ret:  NONE
  ******************************************************************************
  */
void AT_Cop_Rx( AT_ProcessorHandle *h_at_processor, char byte_data );

/**
  ******************************************************************************
  * @Func: AT_Cop_Processor
  * @Desc: Processor of at data flow.
  * @Para: h_at_processor: Pointer of a at processor
  * @Ret:  NONE
  ******************************************************************************
  */
void AT_Cop_Processor( AT_ProcessorHandle *h_at_processor );

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
AT_Object* AT_Cop_UpdateExecutor( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor );

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
  *        p_exception_handler: exception handler
  * @Ret:  Not NULL means this operation is successful
  ******************************************************************************
  */
AT_ProcessorHandle* AT_Cop_Init(  AT_ProcessorHandle *h_at_processor,
                                  AT_Object at_object_list[],
                                  int list_length,
                                  char *p_rx_buffer,
                                  int rx_buffer_size,
                                  int (*p_tx_sender)( uint8_t *, uint32_t ),
                                  void (*p_exception_handler)( char * ) );
#endif /* _AT_COP_H */

/************************ (C) COPYRIGHT NONE *****END OF FILE****/
