/**
  ******************************************************************************
  * @file    TrieTree.c
  * @author  HCL
  * @version V1.0.0
  * @date    13-May-2018
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
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "TrieTree.h"

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
  * @Func: TrieTree_ResetNode
  * @Desc: Reset trie node to empty state
  * @Para: p_trie_node: Pointer of trie node
  * @Ret:  Not NULL means this operation is successful.
  ******************************************************************************
  */
TrieTree_Node* TrieTree_ResetNode( TrieTree_Node *p_trie_node )
{
  if( NULL != p_trie_node )
  {
    memset( p_trie_node, 0x00, sizeof(TrieTree_Node) );
  }
  return p_trie_node;
}

/**
  ******************************************************************************
  * @Func: TrieTree_Insert
  * @Desc: Insert a node into trie tree.
  * @Para: p_trie_node: Pointer of trie node
  *        key_str: The string which will be stored
  *        p_value: The Pointer of value which the string mapping to
  * @Ret:  Not NULL means this operation is successful.
  ******************************************************************************
  */
void* TrieTree_Insert( TrieTree_Node *p_trie_node, char *key_str, void* p_value )
{
  if( (NULL == p_trie_node)
      || (NULL == key_str)
      || (NULL == p_value)
  )
  {
    return NULL;
  }
  else if( '\0' == *key_str )
  {
    p_trie_node->p_next_node[ 0 ] = p_value;
    return p_value;
  }
  else
  {
    if( NULL == p_trie_node->p_next_node[ (int)*key_str ] )
    {
      TrieTree_Node *p_new_node = NULL;

      p_new_node = (TrieTree_Node*)malloc( sizeof(TrieTree_Node) );

      if( NULL == p_new_node )
      {
        return NULL;
      }
      else
      {
        TrieTree_ResetNode( p_new_node );

        p_trie_node->p_next_node[ (int)*key_str ] = p_new_node;
        p_new_node = NULL;
      }
    }
    return TrieTree_Insert( p_trie_node->p_next_node[ (int)*key_str ], key_str+1, p_value );
  }
}

/**
  ******************************************************************************
  * @Func: TrieTree_Query
  * @Desc: Query a node is it in the trie tree
  * @Para: p_trie_node: Pointer of trie node
  *        key_str: The string which will be query
  * @Ret:  Not NULL means the pointer of value which the string mapping to
  ******************************************************************************
  */
void* TrieTree_Query( TrieTree_Node *p_trie_node, char *key_str )
{
  if( NULL == p_trie_node )
  {
    return NULL;
  }
  else if('\0' == *key_str )
  {
    return p_trie_node->p_next_node[0];
  }
  else
  {
    void* answer;

    answer = TrieTree_Query( p_trie_node->p_next_node[ (int)*key_str ], key_str+1 );

    return (NULL != answer)? answer: p_trie_node->p_next_node[0];
  }
}

/**
  ******************************************************************************
  * @Func: TrieTree_Scan
  * @Desc: Scan a trie tree and run the callback
  * @Para: p_trie_node: Pointer of trie node
  *        p_callback: The callback function
  * @Ret:  NONE
  ******************************************************************************
  */
void TrieTree_Scan( TrieTree_Node *p_trie_node, void p_callback( void* ) )
{
  if( (NULL == p_trie_node)
      || (NULL == p_callback)
  )
  {
    return;
  }
  else if( NULL != p_trie_node->p_next_node[0] )
  {
    p_callback( p_trie_node->p_next_node[0] );
  }
  else
  {
    for( int i = 0; i < 256; i ++ )
    {
      if( NULL != p_trie_node->p_next_node[ i ] )
      {
        TrieTree_Scan( p_trie_node->p_next_node[ i ], p_callback );
      }
    }
  }
}

/************************ (C) COPYRIGHT NONE *****END OF FILE****/
