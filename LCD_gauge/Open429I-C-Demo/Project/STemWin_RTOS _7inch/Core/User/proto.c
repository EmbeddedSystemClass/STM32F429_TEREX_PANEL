#include "proto.h"

//#include "watchdog.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"
#include "stm32f4xx_usart.h"
#include "misc.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

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
#define USART_PANEL_BUF_LEN 	64 

#define USART_PANEL_BAUDRATE		115200

#define CRC_LEN				2 
//--------------------------------------------------------------------
uint8_t    RecieveBuf[USART_PANEL_BUF_LEN];
uint8_t		 recieve_count=0;
uint8_t  	 symbol=0xFF;
//-----------------------------------------------------------------------------------
xSemaphoreHandle xProtoSemaphore;

void ProtoBufHandling(void);

uint16_t CRC_Check(uint8_t *buf, uint16_t len);

void ProtoTask( void *pvParameters );//
//----------------------------------------------------------------------------------
void USART_PANEL_IRQHandler(void)
{
 	static portBASE_TYPE xHigherPriorityTaskWoken;
 	xHigherPriorityTaskWoken = pdFALSE;


 	if(USART_GetITStatus(USART_PANEL, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART_PANEL, USART_IT_RXNE);
		symbol=(uint16_t)(USART_PANEL->DR & (uint16_t)0x01FF);

		if(recieve_count>(USART_PANEL_BUF_LEN-1))
		{
			recieve_count=0x0;
			return;
		}
	}

 	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}
//------------------------------------------------------------------------------
void Proto_Init(uint8_t init_type) //
{
		GPIO_InitTypeDef GPIO_InitStruct; 
		USART_InitTypeDef USART_InitStruct;
		NVIC_InitTypeDef NVIC_InitStructure; 

		RCC_APB1PeriphClockCmd(RCC_USART_PANEL, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_USART_PANEL_GPIO, ENABLE);


		GPIO_InitStruct.GPIO_Pin = USART_PANEL_TXD | USART_PANEL_RXD; 
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF; 			
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;		
		GPIO_InitStruct.GPIO_OType = GPIO_OType_PP;			
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_UP;			
		GPIO_Init(USART_PANEL_GPIO, &GPIO_InitStruct);				

		GPIO_PinAFConfig(USART_PANEL_GPIO, USART_PANEL_TXD_PIN_SOURCE, GPIO_AF_USART_PANEL); //
		GPIO_PinAFConfig(USART_PANEL_GPIO, USART_PANEL_RXD_PIN_SOURCE, GPIO_AF_USART_PANEL);

		USART_InitStruct.USART_BaudRate = USART_PANEL_BAUDRATE;				
		USART_InitStruct.USART_WordLength = USART_WordLength_8b;
		USART_InitStruct.USART_StopBits = USART_StopBits_1;		
		USART_InitStruct.USART_Parity = USART_Parity_No;		
		USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; 
		USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; 
		USART_Init(USART_PANEL, &USART_InitStruct);					

		USART_ClearFlag(USART_PANEL, USART_FLAG_CTS | USART_FLAG_LBD  | USART_FLAG_TC  | USART_FLAG_RXNE );


		USART_ITConfig(USART_PANEL, USART_IT_TC, ENABLE);
		USART_ITConfig(USART_PANEL, USART_IT_RXNE , ENABLE);

		USART_Cmd(USART_PANEL, ENABLE);

		NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

		   /* Enabling interrupt from USART */
		NVIC_InitStructure.NVIC_IRQChannel = USART_PANEL_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 14;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_EnableIRQ(USART_PANEL_IRQn);						 

		recieve_count=0x0;

		vSemaphoreCreateBinary( xProtoSemaphore );
		xTaskCreate(ProtoTask,(signed char*)"PROTO",256,NULL, tskIDLE_PRIORITY + 1, NULL);

		return;
}
//-----------------------------------------------------------------------------------
void ProtoTask( void *pvParameters )
{
	uint8_t   crc_n;
	//task_watches[PROTO_TASK].task_status=TASK_IDLE;
	while(1)
	{
		if( xProtoSemaphore != NULL )
		{
			if( xSemaphoreTake( xProtoSemaphore, ( portTickType ) portMAX_DELAY ) == pdTRUE )
			{
						crc_n=RecieveBuf[recieve_count-1];
				
					  if((CRC_Check(RecieveBuf,(recieve_count-CRC_LEN))==crc_n))
						{
							recieve_count=0;
							USART_ITConfig(USART_PANEL, USART_IT_RXNE , ENABLE);
						}
						else
						{
							USART_ITConfig(USART_PANEL, USART_IT_RXNE , ENABLE);
						}
			}
		}
	}
}
//-----------------------crc_n------------------------------------------------------------
uint16_t CRC_Check(uint8_t *buf, uint16_t len)
{
  uint16_t crc = 0xFFFF;
 
  for (int pos = 0; pos < len; pos++) 
	{
    crc ^= (uint16_t)buf[pos];          
 
    for (int i = 8; i != 0; i--) 
		{   
      if ((crc & 0x0001) != 0) 
			{     
        crc >>= 1;                    
        crc ^= 0xA001;
      }
      else
			{				
        crc >>= 1; 
			}				
    }
  }
  return crc;  
}