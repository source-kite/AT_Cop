#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AT_Cop_UserApp.h"
#include "TrieTree.h"

char str_list[ 6 ][15] = {
  "AT+OK",
  "AT+HELLO",
  "AT+SCAN",
  "AT+OL",
  "AT+OLX",
  "AT+O",
};

void MyPrint( void *p_value )
{
  printf( "%s\n", p_value );
}

AT_ProcessorHandle *h_at_processor;


void AT_HELLO_Executor( AT_ProcessorHandle * h_at_processor, char *p_at_str, char *hello_str )
{
  printf( "%s\n", hello_str );
}

void AT_SCAN_Executor( AT_ProcessorHandle * h_at_processor, char *p_at_str, char *mac_str )
{
  printf( "%s\n", mac_str );
}

void AT_OK_Executor( AT_ProcessorHandle * h_at_processor, char *p_at_str )
{
  printf( "%s\n", p_at_str );
}

void AT_TEST_Executor( AT_ProcessorHandle * h_at_processor, char *para1, uint8_t para2, char *para3 )
{
  printf( "%s\n", para1 );


  printf( "%d\n", para2 );

}

void C_AT_SCAN_Executor( AT_ProcessorHandle *h_at_processor, uint32_t no, uint8_t mac[12], int32_t rssi )
{
  printf( "no: %u\n", no );

  printf( "mac: ", no );

  for( int i = 0; i < 12; i ++ )
  {
    putchar( mac[i] );
  }
  putchar( '\n' );

  printf( "rssi: %d\n", rssi );
}

void C_AT_CONN_Executor( AT_ProcessorHandle *h_at_processor, uint32_t no, uint8_t mac[12] )
{
  printf( "no: %u\n", no );

  printf( "mac: ", no );

  for( int i = 0; i < 12; i ++ )
  {
    putchar( mac[i] );
  }
  putchar( '\n' );
}

void C_AT_CONN_ERR_Executor( AT_ProcessorHandle *h_at_processor, char* p_reason_str )
{
  printf( "ErrorReason: %s\n", p_reason_str );
}

void C_AT_DISCONN_Executor( AT_ProcessorHandle *h_at_processor, uint32_t no, uint8_t mac[12] )
{
  printf( "no: %u\n", no );

  printf( "mac: ", no );

  for( int i = 0; i < 12; i ++ )
  {
    putchar( mac[i] );
  }
  putchar( '\n' );
}

void C_AT_DISCONN_ERR_Executor( AT_ProcessorHandle *h_at_processor, uint32_t error_code )
{
  printf( "ErrorCode: 0x%08X\n", error_code );
}

void C_AT_GeneralErrorExecutor( AT_ProcessorHandle *h_at_processor, char *p_at_str )
{
  printf( "%s\n", p_at_str );
}

int main()
{
  uint8_t raw_buffer[ 200 ];
  int length;
  uint8_t byte_data;

  h_at_processor = AT_Cop_UserApp_Init();
  freopen( "in.txt", "r", stdin );

  freopen( "out.txt", "w", stdout );

  length = 0;
  while( scanf( "%c", &byte_data ) == 1 )
  {
    raw_buffer[ length ++ ] = byte_data;
  }

  AT_Cop_UpdateExecutor( h_at_processor, "AT+OK",         (AT_Cop_Executor)AT_OK_Executor );
  AT_Cop_UpdateExecutor( h_at_processor, "AT+HELLO",      (AT_Cop_Executor)AT_HELLO_Executor );
  AT_Cop_UpdateExecutor( h_at_processor, "AT+SCAN",       (AT_Cop_Executor)AT_SCAN_Executor );
  AT_Cop_UpdateExecutor( h_at_processor, "AT+TEST",       (AT_Cop_Executor)AT_TEST_Executor );
  AT_Cop_UpdateExecutor( h_at_processor, "+SCAN=",        (AT_Cop_Executor)C_AT_SCAN_Executor );
  AT_Cop_UpdateExecutor( h_at_processor, "+SCAN=ERR",     (AT_Cop_Executor)C_AT_GeneralErrorExecutor );
  AT_Cop_UpdateExecutor( h_at_processor, "+CONN=",        (AT_Cop_Executor)C_AT_CONN_Executor );
  AT_Cop_UpdateExecutor( h_at_processor, "+CONN=ERR",     (AT_Cop_Executor)C_AT_CONN_ERR_Executor );
  AT_Cop_UpdateExecutor( h_at_processor, "+DISCONN=",     (AT_Cop_Executor)C_AT_DISCONN_Executor );
  AT_Cop_UpdateExecutor( h_at_processor, "+DISCONN=ERR",  (AT_Cop_Executor)C_AT_DISCONN_ERR_Executor );

  for( int i = 0; i < length; i ++ )
  {
    AT_Cop_Rx( h_at_processor, raw_buffer[ i ] );
  }
  AT_Cop_Processor( h_at_processor );

//  AT_Cop_Tx( h_at_processor, "+++" );

  return 0;
}
