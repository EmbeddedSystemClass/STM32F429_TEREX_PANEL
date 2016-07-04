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
#include "proto.h"

int main(void)
{ 

    
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
		Proto_Init();

  vTaskStartScheduler();
	while(1)
	{
	}
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



/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
