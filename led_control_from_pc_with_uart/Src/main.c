/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdint.h>
#include "stm32f407xx.h"
#include "gpio.h"
#include "usart.h"
#include "string.h"

//UART USB A2->Tx A3->Rx pins

int main(){

	GPIO_Handle_t txPin={GPIOA,{GPIO_PIN_NO_2,GPIO_MODE_ALTERNATE,GPIO_SPEED_MEDIUM,GPIO_OTYPE_PP,GPIO_NO_PUPD,GPIO_AF7}};
	GPIO_Handle_t rxPin={GPIOA,{GPIO_PIN_NO_3,GPIO_MODE_ALTERNATE,GPIO_SPEED_MEDIUM,GPIO_OTYPE_PP,GPIO_NO_PUPD,GPIO_AF7}};
	gpio_init(&txPin);
	gpio_init(&rxPin);

	USART_Handle_t usart1_handle;
	usart1_handle.pUsartX=USART2;
	usart1_handle.usart_Config.mode=USART_MODE_BOTH_RXTX;
	usart1_handle.usart_Config.word_lengt=USART_WORDLEN_8BITS;
	usart1_handle.usart_Config.stop_bit=USART_STOPBITS_1;
	usart1_handle.usart_Config.parity_control=USART_PARITY_NO;
	usart1_handle.usart_Config.hwflowcontrol=USART_HW_FLOW_CONTROL_NO;
	usart_init(&usart1_handle);

	char firstMsg[]="Communication Start.\n";
	usart_send_data(&usart1_handle, (uint8_t*)firstMsg, strlen(firstMsg));


	GPIO_Handle_t Gpio_pd_blue={GPIOD,{GPIO_PIN_NO_15,GPIO_MODE_OUT,GPIO_SPEED_MEDIUM,GPIO_OTYPE_PP,GPIO_NO_PUPD}};
	gpio_init(&Gpio_pd_blue);

	char ledON[] = "\rLed On\n";
	char ledOFF[] = "\rLed Off\n";
	char ch;

	while(1){
		ch=usart_read_char();
		if(ch=='b'){
			gpio_toggleto_output_pin(GPIOD, GPIO_PIN_NO_15);
			if(gpio_read_input_pin(GPIOD, GPIO_PIN_NO_15))
				usart_send_data(&usart1_handle, (uint8_t*)ledON, strlen(ledON) );
			else
				usart_send_data(&usart1_handle, (uint8_t*)ledOFF, strlen(ledOFF) );
		}//if
	}//while
}//main
