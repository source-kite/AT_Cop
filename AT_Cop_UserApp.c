/**
  ******************************************************************************
  * @file    AT_Cop_UserApp.c
  * @author  HCL
  * @version V1.0.0
  * @date    19-May-2018
  * @brief   AT command processor user application.
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
#include "AT_Cop_UserApp.h"
#include "AT_Cop_GY_BLE260.h"
#include <stdio.h>
#include <string.h>

/* Private macros ------------------------------------------------------------*/

/* Private types -------------------------------------------------------------*/


/* Private constants ---------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
static int AT_Cop_Transmiter( uint8_t *p_data, uint32_t size );
void AT_Cop_ExceptionHandler( char *p_at_str );

/* Private variables ---------------------------------------------------------*/
static AT_ProcessorHandle h_at_processor;

static char at_rx_buffer[ 128 ];

/* Exported variables --------------------------------------------------------*/

/* Functions -----------------------------------------------------------------*/
AT_ProcessorHandle* AT_Cop_UserApp_Init( void )
{
  return  AT_Cop_Init( &h_at_processor, at_gy_ble260_object_list, at_gy_ble260_object_list_length, at_rx_buffer, sizeof(at_rx_buffer), AT_Cop_Transmiter, AT_Cop_ExceptionHandler );
}

int AT_Cop_Transmiter( uint8_t *p_data, uint32_t size )
{
  int i;

  for( i = 0; i < size; i ++ )
  {
    putchar( p_data[i] );
  }
  return size;
}

void AT_Cop_ExceptionHandler( char *p_at_str )
{
  printf( "Exception: %s\n", p_at_str );
}

/************************ (C) COPYRIGHT NONE *****END OF FILE****/
