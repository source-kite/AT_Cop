/**
  ******************************************************************************
  * @file    AT_Cop_GY_BLE260.c
  * @author  HCL
  * @version V1.0.0
  * @date    2018-22-03
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
#include "AT_Cop_GY_BLE260.h"
#include <stdlib.h>

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/


/* Private constants ---------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
static void S_AT_OK_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor );
static void S_AT_HELLO_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor );
static void S_AT_SCAN_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor );
static void C_AT_SCAN_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor );
static void C_AT_CONN_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor );
static void C_AT_DISCONN_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor );
static void C_AT_DISCONN_ERR_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor );
static void C_AT_CONN_ERR_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor );
static void C_AT_SCAN_ERR_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor );

/* Exported variables --------------------------------------------------------*/
AT_Object at_gy_ble260_object_list[ ] = {
  { "AT+OK",          S_AT_OK_Parser,             NULL, },
  { "AT+HELLO",       S_AT_HELLO_Parser,          NULL, },
  { "AT+SCAN",        S_AT_SCAN_Parser,           NULL, },
  { "+SCAN=",         C_AT_SCAN_Parser,           NULL, },
  { "+SCAN=ERR",      C_AT_SCAN_ERR_Parser,       NULL, },
  { "+DISCONN=",      C_AT_DISCONN_Parser,        NULL, },
  { "+DISCONN=ERR",   C_AT_DISCONN_ERR_Parser,    NULL, },
  { "+CONN=",         C_AT_CONN_Parser,           NULL, },
  { "+CONN=ERR",      C_AT_CONN_ERR_Parser,       NULL, },
};
int at_gy_ble260_object_list_length = sizeof(at_gy_ble260_object_list)/sizeof(AT_Object);


/* Functions -----------------------------------------------------------------*/
void C_AT_DISCONN_ERR_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor )
{
  int error_code;
  char*     p_locator;

  p_locator = p_at_str;

  /* Parse error code field. */
  if( NULL == (p_locator = strchr( p_locator, ',' )) )
  {
    if( NULL != h_at_processor->p_exception_handler )
    {
      h_at_processor->p_exception_handler( p_at_str );
    }
    return ;
  }
  else
  {
    p_locator += 1;
    error_code = atoi( p_locator );
  }

  if( NULL != p_executor )
  {
    p_executor( h_at_processor, error_code );
  }
}

void C_AT_DISCONN_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor )
{
  int32_t   no;
  uint8_t   mac[12];
  char*     p_locator;

  p_locator = p_at_str;

  /* Parse number field. */
  if( NULL == (p_locator = strchr( p_locator, '=' )) )
  {
    if( NULL != h_at_processor->p_exception_handler )
    {
      h_at_processor->p_exception_handler( p_at_str );
    }
    return ;
  }
  else
  {
    p_locator += 1;
    no = atoi( p_locator );
  }

  /* Parse mac field. */
  if( NULL == (p_locator = strchr( p_locator, ',' )) )
  {
    if( NULL != h_at_processor->p_exception_handler )
    {
      h_at_processor->p_exception_handler( p_at_str );
    }
    return ;
  }
  else
  {
    p_locator += 1;
    memcpy( mac, p_locator, 12 );
  }

  /* Parse parameters specified in this command and call executor. */
  if( NULL != p_executor )
  {
    p_executor( h_at_processor, no, mac );
  }
}

void C_AT_CONN_ERR_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor )
{
  char*     p_locator;
  char*     p_reason_str;

  p_locator = p_at_str;

  /* Parse number field. */
  if( NULL == (p_locator = strchr( p_locator, ',' )) )
  {
    if( NULL != h_at_processor->p_exception_handler )
    {
      h_at_processor->p_exception_handler( p_at_str );
    }
    return ;
  }
  else
  {
    p_locator += 1;
    p_reason_str = p_locator;
  }

  /* Parse parameters specified in this command and call executor. */
  if( NULL != p_executor )
  {
    p_executor( h_at_processor, p_reason_str );
  }
}

void C_AT_CONN_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor )
{
  int32_t   no;
  uint8_t   mac[12];
  char*     p_locator;

  p_locator = p_at_str;

  /* Parse number field. */
  if( NULL == (p_locator = strchr( p_locator, '=' )) )
  {
    if( NULL != h_at_processor->p_exception_handler )
    {
      h_at_processor->p_exception_handler( p_at_str );
    }
    return ;
  }
  else
  {
    p_locator += 1;
    no = atoi( p_locator );
  }

  /* Parse mac field. */
  if( NULL == (p_locator = strchr( p_locator, ',' )) )
  {
    if( NULL != h_at_processor->p_exception_handler )
    {
      h_at_processor->p_exception_handler( p_at_str );
    }
    return ;
  }
  else
  {
    p_locator += 1;
    memcpy( mac, p_locator, 12 );
  }

  /* Parse parameters specified in this command and call executor. */
  if( NULL != p_executor )
  {
    p_executor( h_at_processor, no, mac );
  }
}


void C_AT_SCAN_ERR_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor )
{
  if( NULL != p_executor )
  {
    p_executor( h_at_processor, p_at_str );
  }
}

void C_AT_SCAN_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor )
{
  int32_t   no;
  uint8_t   mac[12];
  int       rssi;
  char*     p_locator;

  p_locator = p_at_str;

  /* Parse number field. */
  if( NULL == (p_locator = strchr( p_locator, '=' )) )
  {
    if( NULL != h_at_processor->p_exception_handler )
    {
      h_at_processor->p_exception_handler( p_at_str );
    }
    return ;
  }
  else
  {
    p_locator += 1;
    no = atoi( p_locator );
  }

  /* Parse mac field. */
  if( NULL == (p_locator = strchr( p_locator, ',' )) )
  {
    if( NULL != h_at_processor->p_exception_handler )
    {
      h_at_processor->p_exception_handler( p_at_str );
    }
    return ;
  }
  else
  {
    p_locator += 1;
    memcpy( mac, p_locator, 12 );
  }

  /* Parse rssi field. */
  if( NULL == (p_locator = strchr( p_locator, ',' )) )
  {
    if( NULL != h_at_processor->p_exception_handler )
    {
      h_at_processor->p_exception_handler( p_at_str );
    }
    return ;
  }
  else
  {
    p_locator += 1;
    rssi = atoi( p_locator );
  }

  /* Parse parameters specified in this command and call executor. */
  if( NULL != p_executor )
  {
    p_executor( h_at_processor, no, mac, rssi );
  }
}

void S_AT_OK_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor )
{
  /* Parse parameters specified in this command and call executor. */
  if( NULL != p_executor )
  {
    p_executor( h_at_processor, p_at_str );
  }
}

void S_AT_HELLO_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor )
{
  /* Parse parameters specified in this command and call executor. */
  if( NULL != p_executor )
  {
    p_executor( h_at_processor, p_at_str, "Hello world." );
  }
}

void S_AT_SCAN_Parser( AT_ProcessorHandle *h_at_processor, char *p_at_str, AT_Cop_Executor p_executor )
{
  /* Parse parameters specified in this command and call executor. */
  if( NULL != p_executor )
  {
    p_executor( h_at_processor, p_at_str, "FECDEF" );
  }
}

/************************ (C) COPYRIGHT NONE *****END OF FILE****/
