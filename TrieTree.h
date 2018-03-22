/**
  ******************************************************************************
  * @file    TrieTree.h
  * @author:
  * http://blog.csdn.net/livelylittlefish/article/details/6410569
  * HCL
  * @version V1.0.0
  * @date    13-May-2018
  * @brief:
  * trie tree test
  * descriptioin: make statistics on every word for its frequency
  * usage: input some strings, each followed by a 'enter' character, and end with '#'
  *
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _TRIE_TREE_H
#define _TRIE_TREE_H

/* Includes ------------------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/

/* Exported types ------------------------------------------------------------*/
typedef struct {
  void *p_next_node [ 256 ];
} TrieTree_Node;

/* Exported constants prototypes ---------------------------------------------*/

/* Exported variables prototypes ---------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/


/**
  ******************************************************************************
  * @Func: TrieTree_Scan
  * @Desc: Scan a trie tree and run the callback
  * @Para: p_trie_node: Pointer of trie node
  *        p_callback: The callback function
  * @Ret:  NONE
  ******************************************************************************
  */
void TrieTree_Scan( TrieTree_Node *p_trie_node, void p_callback( void* ) );

/**
  ******************************************************************************
  * @Func: TrieTree_Query
  * @Desc: Query a node is it in the trie tree
  * @Para: p_trie_node: Pointer of trie node
  *        key_str: The string which will be query
  * @Ret:  Not NULL means the pointer of value which the string mapping to
  ******************************************************************************
  */
void* TrieTree_Query( TrieTree_Node *p_trie_node, char *key_str );

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
void* TrieTree_Insert( TrieTree_Node *p_trie_node, char *key_str, void* p_value );

/**
  ******************************************************************************
  * @Func: TrieTree_ResetNode
  * @Desc: Reset trie node to empty state
  * @Para: p_trie_node: Pointer of trie node
  * @Ret:  Not NULL means this operation is successful.
  ******************************************************************************
  */
TrieTree_Node* TrieTree_ResetNode( TrieTree_Node *p_trie_node );

#endif /* _TRIE_TREE_H */

/************************ (C) COPYRIGHT NONE *****END OF FILE****/
