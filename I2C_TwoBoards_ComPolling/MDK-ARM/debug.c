#include "debug.h"
#include "main.h"

#include "stdio.h"
#include "string.h"
#include "stdarg.h"

#define DEBUG_BUFFER_SIZE 256

static void debug_send(int8_t *string, uint16_t len, uint32_t timeout);

static UART_HandleTypeDef UartHandle;
static int8_t debug_buffer[DEBUG_BUFFER_SIZE];

static void debug_send(int8_t *string, uint16_t size, uint32_t timeout)
{
	HAL_UART_Transmit(&UartHandle,(uint8_t *)&debug_buffer[0], size, timeout);
	
	return;
}

void debug_init(void)
{
	UartHandle.Instance          = USARTx;
  
  UartHandle.Init.BaudRate     = 115200;
  UartHandle.Init.WordLength   = UART_WORDLENGTH_8B;
  UartHandle.Init.StopBits     = UART_STOPBITS_1;
  UartHandle.Init.Parity       = UART_PARITY_NONE;
  UartHandle.Init.HwFlowCtl    = UART_HWCONTROL_NONE;
  UartHandle.Init.Mode         = UART_MODE_TX_RX;
  UartHandle.Init.OverSampling = UART_OVERSAMPLING_16;
    
  if(HAL_UART_Init(&UartHandle) != HAL_OK)
	{
		while(1)
		{
			__NOP();
		}
	}
	
	return;
}

void debug_print(char *format, ...)
{
	va_list va_args;
	uint16_t len;
	memset(&debug_buffer[0], 0, DEBUG_BUFFER_SIZE);
	
	va_start(va_args, format);
	len = vsnprintf((char *)&debug_buffer[0], DEBUG_BUFFER_SIZE, format, va_args);
	va_end(va_args);
	
	debug_send(&debug_buffer[0], len, 10);
	
	return;
}

void debug_print_bytes(const char *format, ...)
{
	
	return;
}
