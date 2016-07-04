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
stProtocolData ProtocolData;
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
								TIM_Cmd(TIM2, ENABLE);
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

		receive_count=0x0;
		
		//----------------------------------------
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 
    TIM_TimeBaseInitTypeDef timerInitStructure; 
    timerInitStructure.TIM_Prescaler = 40000;
    timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    timerInitStructure.TIM_Period = 500;
    timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    timerInitStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseInit(TIM2, &timerInitStructure);
		

    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 14;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
		
    TIM_Cmd(TIM2, ENABLE);
		//----------------------------------------

		vSemaphoreCreateBinary( xProtoSemaphore );
		xTaskCreate(ProtoTask,(signed char*)"PROTO",256,NULL, tskIDLE_PRIORITY + 1, NULL);

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
			
			xHigherPriorityTaskWoken = pdFALSE;
			xSemaphoreGiveFromISR( xProtoSemaphore, &xHigherPriorityTaskWoken );
			portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );			
    }
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
						crc_n=RecieveBuf[receive_count-CRC_LEN];
				
					  if((CRC_Check(RecieveBuf,(receive_count-CRC_LEN))==crc_n) && (receive_count==USART_PANEL_FRAME_LEN))
						{
								//ProtocolData.
						}
						USART_ITConfig(USART_PANEL, USART_IT_RXNE , ENABLE);
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