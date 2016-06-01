/**
  ******************************************************************************
  * @file    bsp.c
  * @author  MCD Application Team
  * @version V1.0.1
  * @date    11-November-2013
  * @brief   bsp
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
#include "rtc.h"




uint32_t LowLevel_Init (void)
{
   
  /* Initialize the SDRAM */
  SDRAM_Init();
	
    /* LCD initialization */
  LCD_Init();
  
  /* LCD Layer initialization */
  LCD_LayerInit();
    
  /* Enable the LTDC */
  LTDC_Cmd(ENABLE);
	LCD_SetLayer(LCD_FOREGROUND_LAYER);
	

  RTC_Configuration();
  

  
  /* Enable the CRC Module */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);  
  
  return 0;
}


