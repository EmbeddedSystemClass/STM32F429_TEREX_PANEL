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

#define USART_PANEL 					USART1
#define GPIO_AF_USART_PANEL 	GPIO_AF_USART1
#define USART_PANEL_IRQn			USART1_IRQn
#define RCC_USART_PANEL 			RCC_APB2Periph_USART1
#define USART_PANEL_IRQHandler  USART1_IRQHandler

#define RCC_USART_PANEL_GPIO 	RCC_AHB1Periph_GPIOA

#define USART_PANEL_GPIO 	GPIOA

#define USART_PANEL_TXD	GPIO_Pin_9
#define USART_PANEL_RXD	GPIO_Pin_10

#define USART_PANEL_TXD_PIN_SOURCE GPIO_PinSource9
#define USART_PANEL_RXD_PIN_SOURCE GPIO_PinSource10
#define USART_PANEL_BUF_LEN 	64 

#define USART_PANEL_BAUDRATE		115200

#define CRC_LEN				2 

#define START_SYMBOL		0x55

#define USART_PANEL_FRAME_LEN	19

//-------------------------------------------------------------------
typedef enum
{
		RECEIVE_STATE_WAIT=0,
		RECEIVE_STATE_REC,
		RECEIVE_STATE_HANDLING
}enReceiveState;

static enReceiveState ReceiveState=RECEIVE_STATE_WAIT;
//--------------------------------------------------------------------
uint8_t    RecieveBuf[USART_PANEL_BUF_LEN];
uint8_t		 receive_count=0;
uint8_t  	 symbol=0xFF;
//stProtocolData *ProtocolData;

 xQueueHandle ProtocolDataQueue;
//-----------------------------------------------------------------------------------
xSemaphoreHandle xProtoSemaphore;

void ProtoBufHandling(void);

uint16_t CRC_Check(uint8_t *buf, uint16_t len);

void ProtoTask( void *pvParameters );//
//----------------------------------------------------------------------------------
void USART_PANEL_IRQHandler(void)
{
 	if(USART_GetITStatus(USART_PANEL, USART_IT_RXNE) != RESET)
	{
		USART_ClearITPendingBit(USART_PANEL, USART_IT_RXNE);
		symbol=USART_PANEL->DR;
		TIM_SetCounter(TIM2, 0);
		TIM_Cmd(TIM2, ENABLE);
		
		if(receive_count>(USART_PANEL_BUF_LEN-1))
		{
			receive_count=0x0;
		}
		else
		{
				switch(ReceiveState)
				{
						case RECEIVE_STATE_WAIT:
						{
								ReceiveState=RECEIVE_STATE_REC;
								receive_count=0x0;								
						}
						break;
						
						case RECEIVE_STATE_REC:
						{
							//	RecieveBuf[receive_count]=symbol;
						}
						break;
						
						default:
						{
						}
						break;
				}
				RecieveBuf[receive_count]=symbol;
				receive_count++;
		}
	}
}
//------------------------------------------------------------------------------
void Proto_Init(void) //
{
		GPIO_InitTypeDef GPIO_InitStruct; 
		USART_InitTypeDef USART_InitStruct;
		NVIC_InitTypeDef NVIC_InitStructure; 
		TIM_TimeBaseInitTypeDef timerInitStructure; 	
 
    
	
		vSemaphoreCreateBinary( xProtoSemaphore );
	  ProtocolDataQueue = xQueueCreate( 2, sizeof( stProtocolData ) );

		RCC_APB2PeriphClockCmd(RCC_USART_PANEL, ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_USART_PANEL_GPIO, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

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
		USART_InitStruct.USART_Mode = USART_Mode_Rx; 
		USART_Init(USART_PANEL, &USART_InitStruct);					

		USART_ClearFlag(USART_PANEL,  USART_FLAG_RXNE );



		NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4 );

		NVIC_InitStructure.NVIC_IRQChannel = USART_PANEL_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = configLIBRARY_LOWEST_INTERRUPT_PRIORITY-2;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

	  NVIC_EnableIRQ(USART_PANEL_IRQn);			
		
	  USART_ITConfig(USART_PANEL, USART_IT_RXNE , ENABLE);
	  USART_Cmd(USART_PANEL, ENABLE);		

		receive_count=0x0;
		
		//----------------------------------------

    timerInitStructure.TIM_Prescaler = 1;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 10000;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timerInitStructure);
		
		 	
		TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = configLIBRARY_LOWEST_INTERRUPT_PRIORITY-1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		NVIC_EnableIRQ(TIM2_IRQn);	
   // TIM_Cmd(TIM2, ENABLE);
		//----------------------------------------

	
		xTaskCreate(ProtoTask,(signed char*)"PROTO",128,NULL, tskIDLE_PRIORITY , NULL);

		return;
}
//-----------------------------------------------------------------------------------
void TIM2_IRQHandler()
{
		static portBASE_TYPE xHigherPriorityTaskWoken;
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)
    {
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
			TIM_Cmd(TIM2, DISABLE);
			ReceiveState=RECEIVE_STATE_WAIT;
			
			xHigherPriorityTaskWoken = pdFALSE;
			xSemaphoreGiveFromISR( xProtoSemaphore, &xHigherPriorityTaskWoken );
			portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );			
    }
}
//-----------------------------------------------------------------------------------
void ProtoTask( void *pvParameters )
{
	uint16_t   crc_n, crc_real;
	
	while(1)
	{
		if( xProtoSemaphore != NULL )
		{
			if( xSemaphoreTake( xProtoSemaphore, ( portTickType ) portMAX_DELAY ) == pdTRUE )
			{
						crc_n=*(uint16_t*)&RecieveBuf[receive_count-CRC_LEN];
						crc_real=CRC_Check(RecieveBuf,(receive_count-CRC_LEN));
				
					  if((crc_real==crc_n) && (receive_count==USART_PANEL_FRAME_LEN))
						{
								xQueueSend( ProtocolDataQueue, ( void * )(&RecieveBuf[1]), ( portTickType ) 0 );
						}
						USART_ITConfig(USART_PANEL, USART_IT_RXNE , ENABLE);
			}
		}
		vTaskDelay(1);
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