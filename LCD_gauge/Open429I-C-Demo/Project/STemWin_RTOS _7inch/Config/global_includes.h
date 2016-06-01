#ifndef __GLOBAL_INCLUDES_H__
#define __GLOBAL_INCLUDES_H__

/* Includes ------------------------------------------------------------------*/
#include "global_conf.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "stm32f429i_lib.h"
#include "stm32f429i_lcd_lib.h"
#include "stm32f429i_ioe_lib.h"
#include "stm32f429i_sdram_lib.h"


#include "GUI.h"
#include "DIALOG.h"

#define LOBYTE(x)  ((uint8_t)(x & 0x00FF))
#define HIBYTE(x)  ((uint8_t)((x & 0xFF00) >>8)) 

#endif /* __GLOBAL_INCLUDES_H__ */

