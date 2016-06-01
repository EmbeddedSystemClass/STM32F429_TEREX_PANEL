#include "GUI.h"
#include <stdint.h>
#include "automotivePanel.h"
#include "global_includes.h"

extern GUI_BITMAP bmpicto_H19;
extern  GUI_LOGPALETTE _Palpicto_H19;
	
extern GUI_BITMAP bmpicto_H20;
extern  GUI_LOGPALETTE _Palpicto_H20;
	
extern GUI_BITMAP bmpicto_H21;
extern  GUI_LOGPALETTE _Palpicto_H21;
	
extern GUI_BITMAP bmpicto_H24;
extern  GUI_LOGPALETTE _Palpicto_H24;	
	
extern GUI_BITMAP bmpicto_H35;
extern  GUI_LOGPALETTE _Palpicto_H35;		
	
extern GUI_BITMAP bmpicto_H36;
extern  GUI_LOGPALETTE _Palpicto_H36;	

extern GUI_BITMAP bmpicto_H37;
extern  GUI_LOGPALETTE _Palpicto_H37;

extern GUI_BITMAP bmpicto_H38;
extern  GUI_LOGPALETTE _Palpicto_H38;

extern GUI_BITMAP bmpicto_H39;
extern  GUI_LOGPALETTE _Palpicto_H39;	

extern GUI_BITMAP bmpicto_H40;
extern  GUI_LOGPALETTE _Palpicto_H40;	
	
extern  GUI_COLOR _Colorspicto_gray[];
extern  GUI_COLOR _Colorspicto_red[];

#define MAG         3
#define NUM_SCALES  3

typedef enum
{
	SCALE_TAHOMETER=0,
	SCALE_FUEL=1,
	SCALE_TEMPERATURE=2,
}enScale;


#define TAHOMETERSCALE_ANGLE_MIN	270
#define TAHOMETERSCALE_ANGLE_MAX	90
#define TAHOMETERSCALE_VALUE_MIN	0
#define TAHOMETERSCALE_VALUE_MAX	2500

#define FUELSCALE_ANGLE_MIN	270
#define FUELSCALE_ANGLE_MAX	198
#define FUELSCALE_VALUE_MIN	0
#define FUELSCALE_VALUE_MAX	100

#define TEMPERATURESCALE_ANGLE_MIN	270
#define TEMPERATURESCALE_ANGLE_MAX	198
#define TEMPERATURESCALE_VALUE_MIN	0
#define TEMPERATURESCALE_VALUE_MAX	120

void Set_TahometerScale_Value(float val);
void Set_FuelScale_Value(float val);
void Set_TemperatureScale_Value(float val);


#define AutomotivePanel_Task_PRIO    ( tskIDLE_PRIORITY  + 9 )
#define AutomotivePanel_Task_STACK   ( 3048 )
xTaskHandle                   				AutomotivePanel_Task_Handle;
static void AutomotivePanel_Task(void * pvParameters);

//#define FONT_GEAR &GUI_FontRounded22


#define DEG2RAD      (3.1415926f / 180)


#include "tahometerScale.c"
#include "fuelScale.c"
#include "temperatureScale.c"
//#include "picto.c"
/*********************************************************************
*
*       static data, shape of polygons
*
**********************************************************************
*/

#define TAHOMETERSCALE_NEEDLE_LEN_VISIO	175
#define TAHOMETERSCALE_NEEDLE_CENTER_TO_VISIO 15	// расстояние от центра вращения до видимой части
#define TAHOMETERSCALE_NEEDLE_LEN_ALL	TAHOMETERSCALE_NEEDLE_LEN_VISIO + TAHOMETERSCALE_NEEDLE_CENTER_TO_VISIO		//общая длина стрелки

static GUI_POINT _aNeedle_0[] = { //tahometer needle
  { MAG * ( 0), MAG * (  0 + TAHOMETERSCALE_NEEDLE_LEN_ALL)},
  { MAG * (-3), MAG * (-15 + TAHOMETERSCALE_NEEDLE_LEN_ALL)},
  { MAG * (-3), MAG * (-TAHOMETERSCALE_NEEDLE_LEN_VISIO + TAHOMETERSCALE_NEEDLE_LEN_ALL)},
  { MAG * ( 3), MAG * (-TAHOMETERSCALE_NEEDLE_LEN_VISIO + TAHOMETERSCALE_NEEDLE_LEN_ALL)},
  { MAG * ( 3), MAG * (-15 + TAHOMETERSCALE_NEEDLE_LEN_ALL)},
};


#define FUELSCALE_NEEDLE_LEN_VISIO	100
#define FUELSCALE_NEEDLE_CENTER_TO_VISIO 50	// расстояние от центра вращения до видимой части
#define FUELSCALE_NEEDLE_LEN_ALL	FUELSCALE_NEEDLE_LEN_VISIO + FUELSCALE_NEEDLE_CENTER_TO_VISIO		//общая длина стрелки
static GUI_POINT _aNeedle_1[] = { //other needles
  { MAG * ( 0), MAG * (  0 + FUELSCALE_NEEDLE_LEN_ALL)},
  { MAG * (-3), MAG * (-15 + FUELSCALE_NEEDLE_LEN_ALL)},
  { MAG * (-3), MAG * (-FUELSCALE_NEEDLE_LEN_VISIO + FUELSCALE_NEEDLE_LEN_ALL)},
  { MAG * ( 3), MAG * (-FUELSCALE_NEEDLE_LEN_VISIO + FUELSCALE_NEEDLE_LEN_ALL)},
  { MAG * ( 3), MAG * (-15 + FUELSCALE_NEEDLE_LEN_ALL)},
};


#define TEMPERATURESCALE_NEEDLE_LEN_VISIO	100
#define TEMPERATURESCALE_NEEDLE_CENTER_TO_VISIO 50	// расстояние от центра вращения до видимой части
#define TEMPERATURESCALE_NEEDLE_LEN_ALL	TEMPERATURESCALE_NEEDLE_LEN_VISIO + TEMPERATURESCALE_NEEDLE_CENTER_TO_VISIO		//общая длина стрелки
static GUI_POINT _aNeedle_2[] = { //other needles
  { MAG * ( 0), MAG * (  0 + TEMPERATURESCALE_NEEDLE_LEN_ALL)},
  { MAG * (-3), MAG * (-15 + TEMPERATURESCALE_NEEDLE_LEN_ALL)},
  { MAG * (-3), MAG * (-TEMPERATURESCALE_NEEDLE_LEN_VISIO + TEMPERATURESCALE_NEEDLE_LEN_ALL)},
  { MAG * ( 3), MAG * (-TEMPERATURESCALE_NEEDLE_LEN_VISIO + TEMPERATURESCALE_NEEDLE_LEN_ALL)},
  { MAG * ( 3), MAG * (-15 + TEMPERATURESCALE_NEEDLE_LEN_ALL)},
};


/*********************************************************************
*
*       Structure containing information for drawing routine
*
**********************************************************************
*/
typedef struct {
  GUI_AUTODEV_INFO AutoDevInfo; // Information about what has to be displayed
  GUI_POINT        aPoints[7];  // Polygon data
  float            Angle;
} PARAM;

typedef struct {
  GUI_POINT * pPolygon;
  int         NumPoints;
} NEEDLE;

static int _OldGear = 0;

static NEEDLE _aNeedle[NUM_SCALES] = { 
  { _aNeedle_0, GUI_COUNTOF(_aNeedle_0) },
  { _aNeedle_1, GUI_COUNTOF(_aNeedle_1) },
	{ _aNeedle_2, GUI_COUNTOF(_aNeedle_2) },
};

GUI_AUTODEV aAutoDev [NUM_SCALES];               // Object for banding memory device
PARAM       aParam   [NUM_SCALES] = {0};           // Parameters for drawing routine

/*********************************************************************
*
*       _GetAngle_0
*/
#define ANGLE_0 270
#define ANGLE_100 90

#define SPEED_1_TO	0.075
#define SPEED_1_FROM	0.3
#define TIME_1_TO	(unsigned short)((ANGLE_0- ANGLE_100) / SPEED_1_TO)
#define TIME_1_FROM	(unsigned short)((ANGLE_0- ANGLE_100) / SPEED_1_FROM)
#define TIME_1_1	(0 + TIME_1_TO)
#define TIME_1_2	(TIME_1_1 + TIME_1_FROM)

#define SPEED_2_TO	0.0375
#define SPEED_2_FROM	0.3
#define TIME_2_TO	(unsigned short)((ANGLE_0- ANGLE_100) / SPEED_2_TO)
#define TIME_2_FROM	(unsigned short)((ANGLE_0- ANGLE_100) / SPEED_2_FROM)
#define TIME_2_1	(TIME_1_2 + TIME_2_TO)
#define TIME_2_2	(TIME_2_1 + TIME_2_FROM)

#define SPEED_3_TO	0.03
#define SPEED_3_FROM	0.3
#define TIME_3_TO	(unsigned short)((ANGLE_0- ANGLE_100) / SPEED_3_TO)
#define TIME_3_FROM	(unsigned short)((ANGLE_0- ANGLE_100) / SPEED_3_FROM)
#define TIME_3_1	(TIME_2_2 + TIME_3_TO)
#define TIME_3_2	(TIME_3_1 + TIME_3_FROM)

#define SPEED_4_TO	0.01
#define SPEED_4_FROM	0.3
#define TIME_4_TO	(unsigned short)((ANGLE_0- ANGLE_100) / SPEED_4_TO)
#define TIME_4_FROM	(unsigned short)((ANGLE_0- ANGLE_100) / SPEED_4_FROM)
#define TIME_4_1	(TIME_3_2 + TIME_4_TO)
#define TIME_4_2	(TIME_4_1 + TIME_4_FROM)

static float _GetAngle_0(int tDiff) {
  // Gear 1
  if ((tDiff >= 0)    && (tDiff <  TIME_1_1)) {                return ANGLE_0 - SPEED_1_TO  *  tDiff;         }
  if ((tDiff >= TIME_1_1) && (tDiff <  TIME_1_2)) {                return ANGLE_100 + SPEED_1_FROM    * (tDiff - TIME_1_1); }
  // Gear 2
  if ((tDiff >= TIME_1_2) && (tDiff <  TIME_2_1)) { /*_WriteGear(2);*/ return ANGLE_0 - SPEED_2_TO * (tDiff - TIME_1_2); }
  if ((tDiff >= TIME_2_1) && (tDiff <  TIME_2_2)) {                return ANGLE_100 + SPEED_2_FROM    * (tDiff - TIME_2_1); }
  // Gear 3
  if ((tDiff >= TIME_2_2) && (tDiff <  TIME_3_1)) { /*_WriteGear(3);*/ return ANGLE_0 - SPEED_3_TO   * (tDiff - TIME_2_2); }
  if ((tDiff >= TIME_3_1) && (tDiff <  TIME_3_2)) {                return ANGLE_100 + SPEED_3_FROM    * (tDiff - TIME_3_1); }
  // Gear 4
  if ((tDiff >= TIME_3_2) && (tDiff <  TIME_4_1)) { /*_WriteGear(4);*/ return ANGLE_0 - SPEED_4_TO  * (tDiff - TIME_3_2); }
  if ((tDiff >= TIME_4_1) && (tDiff <  TIME_4_2)) {                return ANGLE_100 + SPEED_4_FROM    * (tDiff - TIME_4_1); }
  // Gear 5
//  if ((tDiff >= TIME_4_2) && (tDiff < 15000)) { _WriteGear(5); return ANGLE_0 - 0.0035 * (tDiff - TIME_4_2); }
  return ANGLE_100;
}

/*********************************************************************
*
*       _GetAngle_1
*/

static float _GetRPM(int tDiff) {

  if ((tDiff >= 0) && (tDiff < 15000)) 
	{
			return ((float)tDiff/15000*2500);
  }
  return 2500;
}

static float _GetFuel(int tDiff) {

  if ((tDiff >= 0) && (tDiff < 15000)) 
	{
			return 100- ((float)tDiff/15000*100);
  }
  return 0;
}

static float _GetTemperature(int tDiff) {

  if ((tDiff >= 0) && (tDiff < 15000)) 
	{
			return ((float)tDiff/15000*120);
  }
  return 120;
}

/*********************************************************************/
#define TAHOMETERSCALE_POS_X					(xSize - bmtahometerScale.XSize)	
#define TAHOMETERSCALE_POS_Y					(0)	
#define TAHOMETERSCALE_NEEDLE_POS_X		(xSize -(bmtahometerScale.XSize>>1)-12)
#define TAHOMETERSCALE_NEEDLE_POS_Y		(bmtahometerScale.YSize-68)

static void _Draw_TahometerScale(void * p) {
  PARAM * pParam = (PARAM *)p;
  int     xSize;

  xSize = LCD_GetXSize();
  //
  // Fixed background
  //
  if (pParam->AutoDevInfo.DrawFixed) {
    GUI_ClearRect (TAHOMETERSCALE_POS_X ,TAHOMETERSCALE_POS_Y, TAHOMETERSCALE_POS_X + bmtahometerScale.XSize - 1,TAHOMETERSCALE_POS_Y+ bmtahometerScale.YSize - 1);
    GUI_DrawBitmap(&bmtahometerScale, TAHOMETERSCALE_POS_X , TAHOMETERSCALE_POS_Y);
  }
  //
  // Moving needle
  //
  GUI_SetColor(GUI_WHITE);
  GUI_AA_FillPolygon(pParam->aPoints, GUI_COUNTOF(_aNeedle_0),  MAG*TAHOMETERSCALE_NEEDLE_POS_X,  MAG*TAHOMETERSCALE_NEEDLE_POS_Y);

}

/*********************************************************************/

#define FUELSCALE_POS_X					(250)	
#define FUELSCALE_POS_Y					(ySize-bmfuelScale.YSize)	
#define FUELSCALE_NEEDLE_POS_X	(FUELSCALE_POS_X+200)
#define FUELSCALE_NEEDLE_POS_Y	(ySize-25)

static void _Draw_FuelScale(void * p) {
  PARAM * pParam = (PARAM *)p;
  int     xSize, ySize;

  xSize = LCD_GetXSize();
	ySize = LCD_GetYSize();
  // Fixed background
  if (pParam->AutoDevInfo.DrawFixed) {
    GUI_ClearRect (FUELSCALE_POS_X, FUELSCALE_POS_Y,/*FUELSCALE_POS_X+ bmfuelScale.XSize - 1*/FUELSCALE_NEEDLE_POS_X+5,FUELSCALE_POS_Y+ bmfuelScale.YSize - 1);
    GUI_DrawBitmap(&bmfuelScale, FUELSCALE_POS_X, FUELSCALE_POS_Y);
  }
  // Moving needle
  GUI_SetColor(GUI_WHITE);
  GUI_AA_FillPolygon(pParam->aPoints, GUI_COUNTOF(_aNeedle_1),  MAG * FUELSCALE_NEEDLE_POS_X,  MAG * FUELSCALE_NEEDLE_POS_Y);
}

/*********************************************************************/
#define TEMPERATURESCALE_POS_X	(570)	
#define TEMPERATURESCALE_POS_Y	(ySize-bmtemperatureScale.YSize)	
#define TEMPERATURESCALE_NEEDLE_POS_X	(TEMPERATURESCALE_POS_X+200)
#define TEMPERATURESCALE_NEEDLE_POS_Y	(ySize-25)

static void _Draw_TemperatureScale(void * p) {
  PARAM * pParam = (PARAM *)p;
  int     xSize, ySize;

  xSize = LCD_GetXSize();
	ySize = LCD_GetYSize();
  // Fixed background
  if (pParam->AutoDevInfo.DrawFixed) {
    GUI_ClearRect (TEMPERATURESCALE_POS_X,TEMPERATURESCALE_POS_Y, /*TEMPERATURESCALE_POS_X + bmtemperatureScale.XSize - 1*/TEMPERATURESCALE_NEEDLE_POS_X+5, TEMPERATURESCALE_POS_Y + bmtemperatureScale.YSize - 1);
    GUI_DrawBitmap(&bmtemperatureScale, TEMPERATURESCALE_POS_X , TEMPERATURESCALE_POS_Y);
  }
  // Moving needle
  GUI_SetColor(GUI_WHITE);
  GUI_AA_FillPolygon(pParam->aPoints, GUI_COUNTOF(_aNeedle_2), MAG * TEMPERATURESCALE_NEEDLE_POS_X, MAG * TEMPERATURESCALE_NEEDLE_POS_Y);

}

/*********************************************************************/
void (* _pfDraw[NUM_SCALES])(void * p) = {
  _Draw_TahometerScale,
  _Draw_FuelScale,
	_Draw_TemperatureScale
};


/*********************************************************************/

void Set_TahometerScale_Value(float val)
{
	if(val<TAHOMETERSCALE_VALUE_MIN)
	{
			val=TAHOMETERSCALE_VALUE_MIN;
	}
	
	if(val>TAHOMETERSCALE_VALUE_MAX)
	{
			val=TAHOMETERSCALE_VALUE_MAX;
	}
	
	aParam[SCALE_TAHOMETER].Angle = ((val-TAHOMETERSCALE_VALUE_MIN)/(TAHOMETERSCALE_VALUE_MAX-TAHOMETERSCALE_VALUE_MIN)*(TAHOMETERSCALE_ANGLE_MAX-TAHOMETERSCALE_ANGLE_MIN)+TAHOMETERSCALE_ANGLE_MIN)*DEG2RAD;
}

void Set_FuelScale_Value(float val)
{
	if(val<FUELSCALE_VALUE_MIN)
	{
			val=FUELSCALE_VALUE_MIN;
	}
	
	if(val>FUELSCALE_VALUE_MAX)
	{
			val=FUELSCALE_VALUE_MAX;
	}
	
	aParam[SCALE_FUEL].Angle = ((val-FUELSCALE_VALUE_MIN)/(FUELSCALE_VALUE_MAX-FUELSCALE_VALUE_MIN)*(FUELSCALE_ANGLE_MAX-FUELSCALE_ANGLE_MIN)+FUELSCALE_ANGLE_MIN)*DEG2RAD;
}

void Set_TemperatureScale_Value(float val)
{
	if(val<TEMPERATURESCALE_VALUE_MIN)
	{
			val=TEMPERATURESCALE_VALUE_MIN;
	}
	
	if(val>TEMPERATURESCALE_VALUE_MAX)
	{
			val=TEMPERATURESCALE_VALUE_MAX;
	}
	
	aParam[SCALE_TEMPERATURE].Angle = ((val-TEMPERATURESCALE_VALUE_MIN)/(TEMPERATURESCALE_VALUE_MAX-TEMPERATURESCALE_VALUE_MIN)*(TEMPERATURESCALE_ANGLE_MAX-TEMPERATURESCALE_ANGLE_MIN)+TEMPERATURESCALE_ANGLE_MIN)*DEG2RAD;
}


void Set_Pictogram_State(enPictogram pictogram, enPictoState state)
{
	switch(pictogram)
	{
		case PICTO_H19:
		{
			if(state==PICTO_STATE_OFF)
			{
					_Palpicto_H19.pPalEntries =&_Colorspicto_gray[0];
			}
			else
			{
					_Palpicto_H19.pPalEntries =&_Colorspicto_red[0];
			}
			GUI_DrawBitmap(&bmpicto_H19, 120 ,  20);
		}
		break;
		
		case PICTO_H20:
		{
			if(state==PICTO_STATE_OFF)
			{
					_Palpicto_H20.pPalEntries =&_Colorspicto_gray[0];
			}
			else
			{
					_Palpicto_H20.pPalEntries =&_Colorspicto_red[0];
			}
			GUI_DrawBitmap(&bmpicto_H20, 90 , 120);
		}
		break;
		
		case PICTO_H21:
		{
				if(state==PICTO_STATE_OFF)
				{
						_Palpicto_H21.pPalEntries =&_Colorspicto_gray[0];
				}
				else
				{
						_Palpicto_H21.pPalEntries =&_Colorspicto_red[0];
				}
				GUI_DrawBitmap(&bmpicto_H21, 60 , 220);

		}
		break;
		
		case PICTO_H24:
		{
			
				if(state==PICTO_STATE_OFF)
				{
						_Palpicto_H24.pPalEntries =&_Colorspicto_gray[0];
				}
				else
				{
						_Palpicto_H24.pPalEntries =&_Colorspicto_red[0];
				}
				GUI_DrawBitmap(&bmpicto_H24, 30 , 320);
		}
		break;
		
		case PICTO_H35:
		{
				if(state==PICTO_STATE_OFF)
				{
						_Palpicto_H35.pPalEntries =&_Colorspicto_gray[0];
				}
				else
				{
						_Palpicto_H35.pPalEntries =&_Colorspicto_red[0];
				}
				GUI_DrawBitmap(&bmpicto_H35, 10 , 420);
		}
		break;
		
		case PICTO_H36:
		{
				if(state==PICTO_STATE_OFF)
				{
						_Palpicto_H36.pPalEntries =&_Colorspicto_gray[0];
				}
				else
				{
						_Palpicto_H36.pPalEntries =&_Colorspicto_red[0];
				}
				GUI_DrawBitmap(&bmpicto_H36, 220,  20);
		}
		break;	

		case PICTO_H37:
		{
				if(state==PICTO_STATE_OFF)
				{
						_Palpicto_H37.pPalEntries =&_Colorspicto_gray[0];
				}
				else
				{
						_Palpicto_H37.pPalEntries =&_Colorspicto_red[0];
				}	
				GUI_DrawBitmap(&bmpicto_H37, 190, 120);
		}
		break;	

		case PICTO_H38:
		{
				if(state==PICTO_STATE_OFF)
				{
						_Palpicto_H38.pPalEntries =&_Colorspicto_gray[0];
				}
				else
				{
						_Palpicto_H38.pPalEntries =&_Colorspicto_red[0];
				}
				GUI_DrawBitmap(&bmpicto_H38, 160, 220);
		}
		break;	

		case PICTO_H39:
		{
				if(state==PICTO_STATE_OFF)
				{
						_Palpicto_H39.pPalEntries =&_Colorspicto_gray[0];
				}
				else
				{
						_Palpicto_H39.pPalEntries =&_Colorspicto_red[0];
				}
				GUI_DrawBitmap(&bmpicto_H39, 130, 320);
		}
		break;	

		case PICTO_H40:
		{
				if(state==PICTO_STATE_OFF)
				{
						_Palpicto_H40.pPalEntries =&_Colorspicto_gray[0];
				}
				else
				{
						_Palpicto_H40.pPalEntries =&_Colorspicto_red[0];
				}	
				GUI_DrawBitmap(&bmpicto_H40, 110, 420);
		}
		break;				
	}
}


void AutomotivePanel_Init(void)
{
	GUI_AA_EnableHiRes();
  GUI_AA_SetFactor(MAG);
	
	xTaskCreate(AutomotivePanel_Task,
						(signed char const*)"BK_GND",
						AutomotivePanel_Task_STACK,
						NULL,
						AutomotivePanel_Task_PRIO,
						&AutomotivePanel_Task_Handle);
}

static void AutomotivePanel_Task(void * pvParameters)
{
	float       aAngleOld[NUM_SCALES];
  int         atDiff   [NUM_SCALES];
  int         atDiffOld[NUM_SCALES] = {0};
  int         tDiff, t0, t1, tBlinkNext;
  int          i;
  int         ySize;

  tDiff = 0;
  ySize = LCD_GetYSize();
	
	static uint8_t blink_flag=0;


	Set_TahometerScale_Value(0);
	Set_FuelScale_Value(0);
	Set_TemperatureScale_Value(0);	
	
  for (i = 0; i < NUM_SCALES; i++) {

    aAngleOld[i] = -1;

    GUI_MEMDEV_CreateAuto(&aAutoDev[i]);
    GUI_RotatePolygon(aParam[i].aPoints, _aNeedle[i].pPolygon, _aNeedle[i].NumPoints, aParam[i].Angle);
    GUI_MEMDEV_DrawAuto(&aAutoDev[i], &aParam[i].AutoDevInfo, _pfDraw[i], &aParam[i]);
  }
		
	for(i=PICTO_H19;i<=PICTO_H40;i++)
	{
			Set_Pictogram_State(i,PICTO_STATE_OFF);
	}

  t0 = GUI_GetTime();       // Get current time

	tBlinkNext=1000;
	while(1)
	{
				
		if((tDiff = GUI_GetTime() - t0) > TIME_4_2)
		{
			tBlinkNext=1000;
			t0 = GUI_GetTime();       // Get current time
		}
				
		if(tDiff > tBlinkNext)
		{
				tBlinkNext+=1000;
				if(blink_flag)
				{
							Set_Pictogram_State(PICTO_H20,PICTO_STATE_OFF);
				}
				else
				{
							Set_Pictogram_State(PICTO_H20,PICTO_STATE_ON);
				}  
				blink_flag=~blink_flag;			

			}

			
			//Set_TahometerScale_Value(_GetRPM(tDiff));
			aParam[SCALE_TAHOMETER].Angle=_GetAngle_0(tDiff)*DEG2RAD;
			Set_FuelScale_Value(_GetFuel(tDiff));
			Set_TemperatureScale_Value(_GetTemperature(tDiff));
			
			for (i = 0; i < NUM_SCALES; i++) 
			{
				if (aAngleOld[i] != aParam[i].Angle)
				{
					aAngleOld[i] = aParam[i].Angle;
					t1           = GUI_GetTime();
					GUI_RotatePolygon(aParam[i].aPoints, _aNeedle[i].pPolygon, _aNeedle[i].NumPoints, aParam[i].Angle);
					GUI_MEMDEV_DrawAuto(&aAutoDev[i], &aParam[i].AutoDevInfo, _pfDraw[i], &aParam[i]);
					atDiff[i]    = GUI_GetTime() - t1;
				}
			}			
			GUI_Exec();
  }
  
	// Delete GUI_AUTODEV-objects
  
  for (i = 0; i < NUM_SCALES; i++) 
	{
    GUI_MEMDEV_DeleteAuto(&aAutoDev[i]);
  }
}
