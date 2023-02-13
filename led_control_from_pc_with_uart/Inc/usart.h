/*
 * usart.h
 *
 *      Author: Baris Cakir
 */

#ifndef USART_H_
#define USART_H_

#include "stm32f407xx.h"
#define SET 	1
#define RESET 	0

enum{
	USART_CR1_SBK,
	USART_CR1_RWU,
	USART_CR1_RE,
	USART_CR1_TE,
	USART_CR1_IDLEIE,
	USART_CR1_RXENIE,
	USART_CR1_TCIE,
	USART_CR1_TXEIE,
	USART_CR1_PEIE,
	USART_CR1_PS,
	USART_CR1_PCE,
	USART_CR1_WAKE,
	USART_CR1_M,
	USART_CR1_UE,

};

#define USART_MODE_ONLY_TX				0
#define USART_MODE_ONLY_RX				1
#define USART_MODE_BOTH_RXTX			2

#define USART_WORDLEN_8BITS				0
#define USART_WORDLEN_9BITS				1

#define USART_STOPBITS_05				1
#define USART_STOPBITS_1				0
#define USART_STOPBITS_15				3
#define USART_STOPBITS_2				2

#define USART_PARITY_NO					0
#define USART_PARITY_EVEN				1
#define USART_PARITY_ODD				2

#define USART_HW_FLOW_CONTROL_NO		0
#define USART_HW_FLOW_CONTROL_CTS		1
#define USART_HW_FLOW_CONTROL_RTS		2
#define USART_HW_FLOW_CONTROL_CTS_RTS	3

#define USART_FLAG_TXE		(1<<7)
#define USART_FLAG_RXNE		(1<<5)
#define USART_FLAG_TC		(1<<6)

typedef struct{
	uint8_t 	mode;
	uint8_t 	word_lengt;
	uint8_t 	stop_bit;
	uint16_t 	baudrate;
	uint8_t 	parity_control;
	uint8_t		hwflowcontrol;

}USART_Config_t;

typedef struct{
	USART_RegDef_t * pUsartX;
	USART_Config_t usart_Config;
}USART_Handle_t;

void usart_init(USART_Handle_t * pUsart_handle);
void usart_send_data(USART_Handle_t * pUsart_handle, uint8_t *pTxBuffer, uint32_t len);
void usart_receive_data(USART_Handle_t * pUsart_handle, uint8_t *pRxBuffer, uint32_t len);
char usart_read_char();

#endif /* USART_H_ */
