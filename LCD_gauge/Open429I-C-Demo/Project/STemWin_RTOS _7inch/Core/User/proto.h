#ifndef PROTO_H
#define PROTO_H
#include "stm32f4xx.h"

void Proto_Init(uint8_t init_type);


#define USART_PANEL 					USART3
#define GPIO_AF_USART_PANEL 	GPIO_AF_USART3
#define USART_PANEL_IRQn			USART3_IRQn
#define RCC_USART_PANEL 			RCC_APB1Periph_USART3
#define USART_PANEL_IRQHandler  USART3_IRQHandler

#define RCC_USART_PANEL_GPIO 	RCC_AHB1Periph_GPIOB

#define USART_PANEL_GPIO 	GPIOB

#define USART_PANEL_TXD	GPIO_Pin_10
#define USART_PANEL_RXD	GPIO_Pin_11

#define USART_PANEL_TXD_PIN_SOURCE GPIO_PinSource10
#define USART_PANEL_RXD_PIN_SOURCE GPIO_PinSource11


#define CHANNEL_NUMBER	1

#define DEVICE_NAME_LENGTH_SYM	20//
#define DEVICE_VER_LENGTH_SYM 0x8
#define DEVICE_DESC_MAX_LENGTH_SYM 40

//--------------------------------------------------------------------------------
#define MAX_LENGTH_REC_BUF 	256 //максимальная длина буфера приема
#define MIN_LENGTH_REC_BUF	5 //

#define MAX_LENGTH_TR_BUF  	256 //макс. длина буфера передачи
#define CRC_LEN				1 //длина CRC


 //------------------------------------------------------------------------------
#endif
