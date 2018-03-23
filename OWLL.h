/**
  ******************************************************************************
  * @file    OWLL.h
  * @author  HCL
  * @version V1.0.0
  * @date    2018-03-23
  * @brief   NONE
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _OWLL_H
#define _OWLL_H

/* Includes ------------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/

typedef struct _OWLL_Node   OWLL_Node;
typedef int (*OWLL_ValueCompare)( const void* p_key_str, const void* p_str );

struct _OWLL_Node{    // One Way Linked List
  void *p_key;
  void *p_value;
  OWLL_Node *p_next;
};

/* Exported constants prototypes ---------------------------------------------*/

/* Exported variables prototypes ---------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
/**
  ******************************************************************************
  * @Func: OWLL_Scan
  * @Desc: Scan a one way linked list and run the callback
  * @Para: p_head: Pointer of head node
  *        p_callback: The callback function
  * @Ret:  NONE
  ******************************************************************************
  */
void OWLL_Scan( OWLL_Node *p_head, void p_callback( void* ) );

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
void* OWLL_Insert( OWLL_Node *p_head, void *p_key, void *p_value, OWLL_ValueCompare p_func_cmp );
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
void* OWLL_Query( OWLL_Node *p_head, void *p_key, OWLL_ValueCompare p_func_cmp );

#endif /* _OWLL_H */

/************************ (C) COPYRIGHT NONE *****END OF FILE****/
