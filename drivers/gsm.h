#ifndef __gsm_h__
#define __gsm_h__

/* define uart functions */
#define modem_out(ptr) 		uart3_print(ptr)
#define modem_readline()	uart3_readline()
#define modem_getc()		uart3_getc()
#define modem_putc(c)		uart3_putc(c)
#define modem_flush_rx()	uart3_flushrx()

/* modem response line types */
#define __LINE_BLANK 		0
#define __LINE_DATA			1
#define __LINE_ERROR 		2
#define __LINE_OTHER		3
#define __LINE_START_RDY	4
#define __LINE_START_CRDY	5
#define __LINE_START_OTHER	6

/* MODEM ERRORS */
#define __MODEM_LINE_STR_ERROR 	-1
#define __MODEM_LINE_NOT_BLANK	-2
#define __MODEM_LINE_NOT_DATA	-3
#define __MODEM_LINE_NOT_OTHER	-4
#define __MODEM_LINE_NOT_OK		-5
#define __MODEM_LINE_TIMEOUT	-6

typedef struct 
{
	uint8_t rssi;
	char 	* ipstate;
	char 	* apn;
	char 	* opr;
	char 	* ip;
	char 	* httpdata;
}Modem_Type_t;

/* modem data struct */
extern Modem_Type_t modem;

/* process */
extern int8_t gsm_process_response(char *, uint16_t);

/* query */
extern int8_t gsm_ping_modem(void);
extern int8_t gsm_get_ipstatus(Modem_Type_t *);
extern int8_t gsm_get_rssi(Modem_Type_t *);
extern int8_t gsm_get_accesspoint(Modem_Type_t *);
extern int8_t gsm_set_accesspoint(Modem_Type_t *);
extern int8_t gsm_get_operator_name(Modem_Type_t *);

/* TCP IP */
extern int8_t gsm_get_ip_address(Modem_Type_t *);
extern int8_t gsm_tcp_start(Modem_Type_t *, char *, char *);
extern int8_t gsm_tcp_close(Modem_Type_t *);
extern int8_t gsm_tcp_send(char);

/* HTTP */
extern uint8_t	gsm_http_head(Modem_Type_t *, char *, char *);
extern uint8_t	gsm_http_get(Modem_Type_t *, char *, char *);
extern uint8_t	gsm_http_delete(Modem_Type_t *, char *, char *);
extern uint8_t	gsm_http_post(Modem_Type_t *, char *, char *, char *);
extern uint8_t	gsm_http_put(Modem_Type_t *, char *, char *, char *);

/* SMS */
extern uint8_t	gsm_send_sms(Modem_Type_t *, char *, char *);



#endif