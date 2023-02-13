/*
 * usart.c
 *
 *      Author: Baris Cakir
 */

#include "usart.h"

static void usart_perip_clock_en(USART_RegDef_t * pUsartx){

	if(pUsartx==USART1)
		USART1_CLOCK_ENABLE();
	else if(pUsartx==USART2)
		USART2_CLOCK_ENABLE();
	else if(pUsartx==USART3)
		USART3_CLOCK_ENABLE();
	else if(pUsartx==USART4)
		USART4_CLOCK_ENABLE();
	else if(pUsartx==USART5)
		USART5_CLOCK_ENABLE();
	else if(pUsartx==USART6)
		USART6_CLOCK_ENABLE();
}

uint8_t usart_get_flag_state(USART_RegDef_t* pUsartx,uint8_t state_flag){

	if(pUsartx->SR & state_flag) //(1u<<5)
		return SET;
	return RESET;
}


void usart_init(USART_Handle_t * pUsart_handle){

	//usart clock enable
	usart_perip_clock_en(pUsart_handle->pUsartX);

	//mode
	if(pUsart_handle->usart_Config.mode == USART_MODE_ONLY_TX){
		pUsart_handle->pUsartX->CR1 |= (1u<<3);
	}
	else if(pUsart_handle->usart_Config.mode == USART_MODE_ONLY_RX){
		pUsart_handle->pUsartX->CR1 |= (1u<<2);
	}
	else if(pUsart_handle->usart_Config.mode == USART_MODE_BOTH_RXTX){
		pUsart_handle->pUsartX->CR1 |= (1u<<2);
		pUsart_handle->pUsartX->CR1 |= (1u<<3);
	}

	//word len
	pUsart_handle->pUsartX->CR1 |= (pUsart_handle->usart_Config.word_lengt<<12);

	//stop bit
	pUsart_handle->pUsartX->CR2 |= (pUsart_handle->usart_Config.stop_bit<<12);

	//parity
	if(pUsart_handle->usart_Config.parity_control == USART_PARITY_NO){
		pUsart_handle->pUsartX->CR1 &= ~(1u<<10);
	}
	else{
		pUsart_handle->pUsartX->CR1 |= (1u<<10);

		if(pUsart_handle->usart_Config.parity_control == USART_PARITY_EVEN){
			pUsart_handle->pUsartX->CR1 |= (1u<<2);
		}
		else if(pUsart_handle->usart_Config.parity_control == USART_PARITY_ODD){
			pUsart_handle->pUsartX->CR1 &= ~(1u<<9);
			pUsart_handle->pUsartX->CR1 |= (1u<<9);
		}
	}

	//hw control
	if(pUsart_handle->usart_Config.hwflowcontrol == USART_HW_FLOW_CONTROL_NO){
		pUsart_handle->pUsartX->CR3 &= ~(1u<<8);
		pUsart_handle->pUsartX->CR3 &= ~(1u<<9);
	}
	else if(pUsart_handle->usart_Config.hwflowcontrol == USART_HW_FLOW_CONTROL_CTS){
		pUsart_handle->pUsartX->CR3 &= ~(1u<<8);
		pUsart_handle->pUsartX->CR3 |= (1u<<9);
	}
	else if(pUsart_handle->usart_Config.hwflowcontrol == USART_HW_FLOW_CONTROL_RTS){
		pUsart_handle->pUsartX->CR3 |= (1u<<8);
		pUsart_handle->pUsartX->CR3 &= ~(1u<<9);
	}
	else if(pUsart_handle->usart_Config.hwflowcontrol == USART_HW_FLOW_CONTROL_CTS_RTS){
		pUsart_handle->pUsartX->CR3 |= (1u<<8);
		pUsart_handle->pUsartX->CR3 |=  (1u<<9);
	}

	//baudrate
	pUsart_handle->pUsartX->BBR = 0x683; //9600 baudrate

	pUsart_handle->pUsartX->CR1 |= (1u<<13);//usart enable with ue bit.
}

void usart_send_data(USART_Handle_t * pUsart_handle, uint8_t *pTxBuffer, uint32_t len){

	for(uint32_t i=0; i<len;i++){
		while(!(usart_get_flag_state(pUsart_handle->pUsartX, USART_FLAG_TXE)))
			;
		pUsart_handle->pUsartX->DR = (*pTxBuffer);
		++pTxBuffer;
	}
}

void usart_receive_data(USART_Handle_t * pUsart_handle, uint8_t *pRxBuffer, uint32_t len){

	for(uint32_t i=0; i<len;i++){
		while(!(usart_get_flag_state(pUsart_handle->pUsartX, USART_FLAG_RXNE)))
			;
		* pRxBuffer = pUsart_handle->pUsartX->DR & (uint8_t)0xFF;
		++pRxBuffer;
	}

}

char usart_read_char(){

	while(!(usart_get_flag_state(USART2, USART_FLAG_RXNE)))
		;
	return USART2->DR;
}




