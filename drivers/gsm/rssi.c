#include "stdint.h"
#include "stdlib.h"
#include "uart.h"
#include "misc.h"
#include "lcd.h"
#include "delay.h"
#include "gsm.h"
#include "system_LPC17xx.h"
#include "LPC17xx.h"
#include "stdio.h"
#include "syscalls.h"
#include "string.h"
#include "config.h"

/** @brief 		Send AT+CSQ to modem and get the signal strength stores result in struct
 *  @param 		Modem_Type_t
 *  @return 	int8_t
 */
int8_t gsm_get_rssi(void)
{
	uint16_t len, resp;

	/* write AT+CIPSTATUS to modem */
	modem_out("AT+CSQ\r");

	/* read 1st line it should be blank */
	len 	= modem_readline();
	resp 	= process_response(uart3_fifo.line,len);

	/* check for blank if not return error */
	if(resp != __LINE_BLANK)
	{
		modem_flush_rx();
		return __MODEM_LINE_NOT_BLANK;
	}

	/* read 2nd line it should be contain data */
	len 	= modem_readline();
	resp 	= process_response(uart3_fifo.line,len);

	/* check whether response is data? */
	if(resp != __LINE_DATA)
	{
		modem_flush_rx();
		return __MODEM_LINE_NOT_DATA;
	}

	char * __next;
	char * __index = index(uart3_fifo.line, ':');

	/* check for result and returns error */
	if(__index == NULL)
	{
		modem_flush_rx();
		return __MODEM_LINE_CS_ERROR;
	}

	/* +2 for removing :<space> */
	__index += 2;

	int8_t rssi = strtol(__index, &__next, 10);

	if(rssi == -1)
	{
		modem_flush_rx();
		return __MODEM_LINE_PARSE_ERROR;
	}

	modem.rssi = rssi;

	/* read 3rd line it should be blank */
	len 	= modem_readline();
	resp 	= process_response(uart3_fifo.line,len);

	// check whether blank line
	if(resp != __LINE_BLANK)
	{
		modem_flush_rx();
		return __MODEM_LINE_NOT_BLANK;
	}


	/* read 3rd line it should be 'OK' */
	len 	= modem_readline();
	resp 	= process_response(uart3_fifo.line,len);

	/* check for __OTHER */
	if(resp != __LINE_OTHER)
	{
		modem_flush_rx();
		return __MODEM_LINE_NOT_OTHER;
	}

	/* check for 'OK' */
	if(strstr(uart3_fifo.line, "OK"))
	{
		modem_flush_rx();
		return __LINE_PARSE_SUCCESS;
	}

	modem_flush_rx();
	return __MODEM_LINE_NOT_OK;
}