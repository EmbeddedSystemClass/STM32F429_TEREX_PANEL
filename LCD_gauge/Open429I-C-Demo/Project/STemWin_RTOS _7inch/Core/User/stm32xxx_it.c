#include "global_includes.h"

extern __IO uint32_t TS_Pressed;
extern uint32_t demo_mode;

__IO uint32_t ButtonPressed = 0x00;
//extern uint32_t USBD_OTG_ISR_Handler (USB_OTG_CORE_HANDLE *pdev);
extern __IO uint32_t PeriodValue;
extern __IO uint32_t CaptureNumber;
uint16_t tmpCC4[2] = {0, 0};
/* Private function prototypes -----------------------------------------------*/
//extern void USB_OTG_BSP_TimerIRQ (void);
extern void xPortSysTickHandler( void );
extern void LTDC_ISR_Handler(void);
extern void DMA2D_ISR_Handler(void);
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*             Cortex-M Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {}
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
static __IO uint32_t TimingDelay;	
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}
	
void SysTick_Handler(void)
{
  xPortSysTickHandler();
}

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
void EXTI0_IRQHandler(void)
{ 
  ButtonPressed = 0x01;
  
  EXTI_ClearITPendingBit(USER_BUTTON_EXTI_LINE);
}
/**
  * @brief  TIM2_IRQHandler
  *         This function handles Timer2 Handler.
  * @param  None
  * @retval None
  */



/**
  * @brief  This function handles OTG_HS Handler.
  * @param  None
  * @retval None
  */
//void OTG_HS_IRQHandler(void)
//{
//  if(demo_mode == 0)
//  {
//    USBH_OTG_ISR_Handler (&USB_OTG_Core);
//  }
//  else
//  {
//    USBD_OTG_ISR_Handler (&USB_OTG_dev);
//  }
//}

/**
  * @brief  This function handles TIM5 global interrupt request.
  * @param  None
  * @retval None
  */
void TIM5_IRQHandler(void)
{
  if (TIM_GetITStatus(TIM5, TIM_IT_CC4) != RESET)
  {    
    /* Get the Input Capture value */
    tmpCC4[CaptureNumber++] = TIM_GetCapture4(TIM5);
   
    /* Clear CC4 Interrupt pending bit */
    TIM_ClearITPendingBit(TIM5, TIM_IT_CC4);

    if (CaptureNumber >= 2)
    {
      /* Compute the period length */
      PeriodValue = (uint16_t)(0xFFFF - tmpCC4[0] + tmpCC4[1] + 1);
    }
  }
}

/**
  * @brief  This function handles DMA2 Stream1 global interrupt request.
  * @param  None
  * @retval None
  */

void DMA2_Stream1_IRQHandler(void)
{
}

/**
  * @brief  This function handles LTDC global interrupt request.
  * @param  None
  * @retval None
  */
void LTDC_IRQHandler(void)
{
  LTDC_ISR_Handler();
}

/**
  * @brief  This function handles DMA2D global interrupt request.
  * @param  None
  * @retval None
  */
void DMA2D_IRQHandler(void)
{
  DMA2D_ISR_Handler();
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
