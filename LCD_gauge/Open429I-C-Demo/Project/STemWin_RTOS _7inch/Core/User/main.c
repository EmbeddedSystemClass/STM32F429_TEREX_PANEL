/**
  ******************************************************************************
  * @file    main.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    11-November-2013
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp.h"
#include "timers.h"
#include <stddef.h>
#include "automotivePanel.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
//#define Background_Task_PRIO    ( tskIDLE_PRIORITY  + 10 )
//#define Background_Task_STACK   ( 512 )

//#define Demo_Task_PRIO          ( tskIDLE_PRIORITY  + 9 )
//#define Demo_Task_STACK         ( 3048 )

///* Private macro -------------------------------------------------------------*/
///* Private variables ---------------------------------------------------------*/
//xTaskHandle                   Task_Handle;
//xTaskHandle                   Demo_Handle;
xTimerHandle                  TouchScreenTimer;

uint32_t demo_mode = 0;

//extern WM_HWIN  ALARM_hWin;

/* Private function prototypes -----------------------------------------------*/
//static void Background_Task(void * pvParameters);
//static void Demo_Task(void * pvParameters);
static void vTimerCallback( xTimerHandle pxTimer );
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */ 
int main(void)
{ 
  uint32_t ticks = 0;
    
  /* Initialize the BSP layer */
  LowLevel_Init();
	
  /* Init the STemWin GUI Library */
  GUI_Init();
	GUI_SelectLayer(0);
  GUI_SetBkColor(GUI_BLACK);
  GUI_SelectLayer(1);
  GUI_Clear();
  GUI_SetBkColor(GUI_BLACK); 
	AutomotivePanel_Init();

  vTaskStartScheduler();
	while(1)
	{
	}
}


/**
  * @brief  Timer callback
  * @param  pxTimer 
  * @retval None
  */
static void vTimerCallback( xTimerHandle pxTimer )
{

}

/**
  * @brief  Error callback function
  * @param  None
  * @retval None
  */
void vApplicationMallocFailedHook( void )
{
  while (1)
  {}
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *   where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {}
}
#endif

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
