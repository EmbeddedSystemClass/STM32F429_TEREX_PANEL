#include "GUI.h"
#include <stdint.h>
#include "automotivePanel.h"
#include "global_includes.h"

extern GUI_BITMAP bmpicto_H19;	
extern GUI_BITMAP bmpicto_H20;	
extern GUI_BITMAP bmpicto_H21;	
extern GUI_BITMAP bmpicto_H24;	
extern GUI_BITMAP bmpicto_H35;	
extern GUI_BITMAP bmpicto_H36;
extern GUI_BITMAP bmpicto_H37;
extern GUI_BITMAP bmpicto_H38;
extern GUI_BITMAP bmpicto_H39;
extern GUI_BITMAP bmpicto_H40;
extern GUI_BITMAP bmpicto_H41;
extern GUI_BITMAP bmpicto_H42;	
extern GUI_BITMAP bmpicto_H43;	
extern GUI_BITMAP bmpicto_H44;	
extern GUI_BITMAP bmpicto_H45;	
extern GUI_BITMAP bmpicto_H46;
extern GUI_BITMAP bmpicto_H47;
extern GUI_BITMAP bmpicto_H48;
extern GUI_BITMAP bmpicto_H49;
extern GUI_BITMAP bmpicto_H51;

	
extern  GUI_COLOR _Colorspicto_gray[];
extern  GUI_COLOR _Colorspicto_red[];
extern  GUI_COLOR _Colorspicto_green[];
extern  GUI_COLOR _Colorspicto_blue[];

#define MAG         3
#define NUM_SCALES  4

typedef enum
{
	SCALE_TAHOMETER=0,
	SCALE_FUEL=1,
	SCALE_TEMPERATURE=2,
	SCALE_SPEEDOMETER=3,
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

#define SPEEDOMETERSCALE_ANGLE_MIN	270
#define SPEEDOMETERSCALE_ANGLE_MAX	90
#define SPEEDOMETERSCALE_VALUE_MIN	0
#define SPEEDOMETERSCALE_VALUE_MAX	40

void Set_TahometerScale_Value(float val);
void Set_FuelScale_Value(float val);
void Set_TemperatureScale_Value(float val);
void Set_SpeedometerScale_Value(float val);


/**************Filter******************************/
#define TAHOMETERSCALE_FILTER_TCONST	10
#define TAHOMETERSCALE_WLAG 8

#define FUELSCALE_FILTER_TCONST	10
#define FUELSCALE_WLAG 8

#define TEMPERATURESCALE_FILTER_TCONST	10
#define TEMPERATURESCALE_WLAG 8

#define SPEEDOMETERSCALE_FILTER_TCONST	10
#define SPEEDOMETERSCALE_WLAG 8

typedef  struct
{
		float t_const;
		float wlag;
}
FILTER;

const FILTER TahometerScaleFilter={TAHOMETERSCALE_FILTER_TCONST,TAHOMETERSCALE_WLAG};
const FILTER FuelScaleFilter={FUELSCALE_FILTER_TCONST,FUELSCALE_WLAG};
const FILTER TemperatureScaleFilter={TEMPERATURESCALE_FILTER_TCONST,TEMPERATURESCALE_WLAG};
const FILTER SpeedometerScaleFilter={SPEEDOMETERSCALE_FILTER_TCONST,SPEEDOMETERSCALE_WLAG};

float ScaleFilter(const FILTER *filter, float in);
/***************************************************/

typedef struct {
	GUI_AUTODEV 		 aAutoDev;
  GUI_AUTODEV_INFO AutoDevInfo; // Information about what has to be displayed
  GUI_POINT        aPoints[7];  // Polygon data
  float            Angle;
	float 					 Angle_min;
	float 					 Angle_max;
	float 					 Value;
	float 					 Value_min;
	float 					 Value_max;
	
} PARAM;

typedef struct {
  GUI_POINT * pPolygon;
  int         NumPoints;
} NEEDLE;

typedef struct
{
	GUI_BITMAP *scale;
	GUI_POINT 	scale_pos;
	NEEDLE		 *needle;
	GUI_POINT   needle_pos;	
	PARAM			  param;
	const FILTER *filter;	
	enScaleState state;
} SCALE;

static SCALE scales[NUM_SCALES];
/***************************************************/

typedef struct
{
	GUI_POINT pos;
	GUI_BITMAP *picto;
	GUI_COLOR  *palette_active_state;
	GUI_COLOR  *palette_passive_state;
	enPictoState state;	
}
PICTOGRAM;

#define PICTO_NUM	20
static PICTOGRAM picto[PICTO_NUM];

void Pictogram_Init(void);

/***************************************************/
#define AutomotivePanel_Task_PRIO    ( tskIDLE_PRIORITY  + 9 )
#define AutomotivePanel_Task_STACK   ( 3048 )
xTaskHandle                   				AutomotivePanel_Task_Handle;
static void AutomotivePanel_Task(void * pvParameters);

//#define FONT_GEAR &GUI_FontRounded22

#define DEG2RAD      (3.1415926f / 180)


#include "tahometerScale.c"
#include "speedometerScale.c"
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


#define SPEEDOMETERSCALE_NEEDLE_LEN_VISIO	175
#define SPEEDOMETERSCALE_NEEDLE_CENTER_TO_VISIO 15	// расстояние от центра вращения до видимой части
#define SPEEDOMETERSCALE_NEEDLE_LEN_ALL	SPEEDOMETERSCALE_NEEDLE_LEN_VISIO + SPEEDOMETERSCALE_NEEDLE_CENTER_TO_VISIO		//общая длина стрелки

static GUI_POINT _aNeedle_3[] = { //SPEEDOMETER needle
  { MAG * ( 0), MAG * (  0 + SPEEDOMETERSCALE_NEEDLE_LEN_ALL)},
  { MAG * (-3), MAG * (-15 + SPEEDOMETERSCALE_NEEDLE_LEN_ALL)},
  { MAG * (-3), MAG * (-SPEEDOMETERSCALE_NEEDLE_LEN_VISIO + SPEEDOMETERSCALE_NEEDLE_LEN_ALL)},
  { MAG * ( 3), MAG * (-SPEEDOMETERSCALE_NEEDLE_LEN_VISIO + SPEEDOMETERSCALE_NEEDLE_LEN_ALL)},
  { MAG * ( 3), MAG * (-15 + SPEEDOMETERSCALE_NEEDLE_LEN_ALL)},
};


static int _OldGear = 0;

static NEEDLE _aNeedle[NUM_SCALES] = { 
  { _aNeedle_0, GUI_COUNTOF(_aNeedle_0) },
  { _aNeedle_1, GUI_COUNTOF(_aNeedle_1) },
	{ _aNeedle_2, GUI_COUNTOF(_aNeedle_2) },
	{ _aNeedle_3, GUI_COUNTOF(_aNeedle_3) },
};

//GUI_AUTODEV aAutoDev [NUM_SCALES];               // Object for banding memory device
//PARAM       aParam   [NUM_SCALES] = {0};           // Parameters for drawing routine

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

static float _GetSpeed(int tDiff) {

  if ((tDiff >= 0) && (tDiff < 15000)) 
	{
			return ((float)tDiff/15000*40);
  }
  return 40;
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
#define SPEEDOMETERSCALE_POS_X					(xSize - bmtahometerScale.XSize)	
#define SPEEDOMETERSCALE_POS_Y					(0)	
#define SPEEDOMETERSCALE_NEEDLE_POS_X		(xSize -(bmtahometerScale.XSize>>1)-12)
#define SPEEDOMETERSCALE_NEEDLE_POS_Y		(bmtahometerScale.YSize-68)

static void _Draw_SpeedometerScale(void * p) {
  PARAM * pParam = (PARAM *)p;
  int     xSize;

  xSize = LCD_GetXSize();
  //
  // Fixed background
  //
  if (pParam->AutoDevInfo.DrawFixed) {
    GUI_ClearRect (SPEEDOMETERSCALE_POS_X ,SPEEDOMETERSCALE_POS_Y, SPEEDOMETERSCALE_POS_X + bmtahometerScale.XSize - 1,SPEEDOMETERSCALE_POS_Y+ bmtahometerScale.YSize - 1);
    GUI_DrawBitmap(&bmtahometerScale, SPEEDOMETERSCALE_POS_X , SPEEDOMETERSCALE_POS_Y);
  }
  //
  // Moving needle
  //
  GUI_SetColor(GUI_WHITE);
  GUI_AA_FillPolygon(pParam->aPoints, GUI_COUNTOF(_aNeedle_3),  MAG*SPEEDOMETERSCALE_NEEDLE_POS_X,  MAG*SPEEDOMETERSCALE_NEEDLE_POS_Y);

}

/*********************************************************************/
void (* _pfDraw[NUM_SCALES])(void * p) = {
  _Draw_TahometerScale,
  _Draw_FuelScale,
	_Draw_TemperatureScale,
//	_Draw_SpeedometerScale,
};


/*********************************************************************/

void Set_ScaleValue(enScale scale, float val)
{
	val=ScaleFilter(scales[scale].filter,val);
	
	if(val<scales[scale].param.Value_min)
	{
			val=scales[scale].param.Value_min;
	}
	
	if(val>scales[scale].param.Value_max)
	{
			val=scales[scale].param.Value_max;
	}
	
	scales[scale].param.Angle = ((val-scales[scale].param.Value_min)/(scales[scale].param.Value_max-scales[scale].param.Value_min)*(scales[scale].param.Angle_max-scales[scale].param.Angle_min)+scales[scale].param.Angle_min)*DEG2RAD;
}

//void Set_TahometerScale_Value(float val)
//{
//	val=ScaleFilter(&TahometerScaleFilter,val);
//	if(val<TAHOMETERSCALE_VALUE_MIN)
//	{
//			val=TAHOMETERSCALE_VALUE_MIN;
//	}
//	
//	if(val>TAHOMETERSCALE_VALUE_MAX)
//	{
//			val=TAHOMETERSCALE_VALUE_MAX;
//	}
//	
//	aParam[SCALE_TAHOMETER].Angle = ((val-TAHOMETERSCALE_VALUE_MIN)/(TAHOMETERSCALE_VALUE_MAX-TAHOMETERSCALE_VALUE_MIN)*(TAHOMETERSCALE_ANGLE_MAX-TAHOMETERSCALE_ANGLE_MIN)+TAHOMETERSCALE_ANGLE_MIN)*DEG2RAD;
//}

//void Set_FuelScale_Value(float val)
//{
//	val=ScaleFilter(&FuelScaleFilter,val);
//	if(val<FUELSCALE_VALUE_MIN)
//	{
//			val=FUELSCALE_VALUE_MIN;
//	}
//	
//	if(val>FUELSCALE_VALUE_MAX)
//	{
//			val=FUELSCALE_VALUE_MAX;
//	}
//	
//	aParam[SCALE_FUEL].Angle = ((val-FUELSCALE_VALUE_MIN)/(FUELSCALE_VALUE_MAX-FUELSCALE_VALUE_MIN)*(FUELSCALE_ANGLE_MAX-FUELSCALE_ANGLE_MIN)+FUELSCALE_ANGLE_MIN)*DEG2RAD;
//}

//void Set_TemperatureScale_Value(float val)
//{
//	val=ScaleFilter(&TemperatureScaleFilter,val);
//	if(val<TEMPERATURESCALE_VALUE_MIN)
//	{
//			val=TEMPERATURESCALE_VALUE_MIN;
//	}
//	
//	if(val>TEMPERATURESCALE_VALUE_MAX)
//	{
//			val=TEMPERATURESCALE_VALUE_MAX;
//	}
//	
//	aParam[SCALE_TEMPERATURE].Angle = ((val-TEMPERATURESCALE_VALUE_MIN)/(TEMPERATURESCALE_VALUE_MAX-TEMPERATURESCALE_VALUE_MIN)*(TEMPERATURESCALE_ANGLE_MAX-TEMPERATURESCALE_ANGLE_MIN)+TEMPERATURESCALE_ANGLE_MIN)*DEG2RAD;
//}

//void Set_SpeedometerScale_Value(float val)
//{
//	val=ScaleFilter(&SpeedometerScaleFilter,val);
//	if(val<SPEEDOMETERSCALE_VALUE_MIN)
//	{
//			val=SPEEDOMETERSCALE_VALUE_MIN;
//	}
//	
//	if(val>SPEEDOMETERSCALE_VALUE_MAX)
//	{
//			val=SPEEDOMETERSCALE_VALUE_MAX;
//	}
//	
//	aParam[SCALE_SPEEDOMETER].Angle = ((val-SPEEDOMETERSCALE_VALUE_MIN)/(SPEEDOMETERSCALE_VALUE_MAX-SPEEDOMETERSCALE_VALUE_MIN)*(SPEEDOMETERSCALE_ANGLE_MAX-SPEEDOMETERSCALE_ANGLE_MIN)+SPEEDOMETERSCALE_ANGLE_MIN)*DEG2RAD;
//}


//----------------------------------------------

void Set_Pictogram_State(enPictogram pictogram, enPictoState state)
{
	picto[pictogram].state=state;
	
	if(picto[pictogram].state==PICTO_STATE_OFF)
	{
			picto[pictogram].picto->pPal->pPalEntries=picto[pictogram].palette_passive_state;
	}
	else
	{
			picto[pictogram].picto->pPal->pPalEntries=picto[pictogram].palette_active_state;
	}
	
	GUI_DrawBitmap(picto[pictogram].picto, picto[pictogram].pos.x , picto[pictogram].pos.y );
}



void AutomotivePanel_Init(void)
{
	GUI_AA_EnableHiRes();
  GUI_AA_SetFactor(MAG);
	
	Pictogram_Init();
	
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


//	Set_TahometerScale_Value(0);
//	Set_FuelScale_Value(0);
//	Set_TemperatureScale_Value(0);	
	
	
  for (i = 0; i < NUM_SCALES; i++) 
	{
		aAngleOld[i] = -1;	 
		Set_ScaleValue(i,0)
    GUI_MEMDEV_CreateAuto(&aAutoDev[i]);
    GUI_RotatePolygon(aParam[i].aPoints, _aNeedle[i].pPolygon, _aNeedle[i].NumPoints, aParam[i].Angle);
    GUI_MEMDEV_DrawAuto(&aAutoDev[i], &aParam[i].AutoDevInfo, _pfDraw[i], &aParam[i]);
  }
		
	for(i=0;i<=PICTO_NUM;i++)
	{
			Set_Pictogram_State(i,PICTO_STATE_OFF);
	}

  t0 = GUI_GetTime();       // Get current time

	tBlinkNext=1000;
	while(1)
	{
				
		if((tDiff = GUI_GetTime() - t0) > 15000)
		{
			tBlinkNext=1000;
			t0 = GUI_GetTime();       // Get current time
		}
	
				
		if(tDiff > tBlinkNext)
		{
				tBlinkNext+=1000;
				if(blink_flag)
				{
						Set_Pictogram_State(PICTO_H19,PICTO_STATE_OFF);
						Set_Pictogram_State(PICTO_H20,PICTO_STATE_ON);
						Set_Pictogram_State(PICTO_H21,PICTO_STATE_OFF);
						Set_Pictogram_State(PICTO_H24,PICTO_STATE_ON);
						Set_Pictogram_State(PICTO_H35,PICTO_STATE_OFF);
						Set_Pictogram_State(PICTO_H36,PICTO_STATE_ON);
						Set_Pictogram_State(PICTO_H37,PICTO_STATE_OFF);
						Set_Pictogram_State(PICTO_H38,PICTO_STATE_ON);
						Set_Pictogram_State(PICTO_H39,PICTO_STATE_OFF);
						Set_Pictogram_State(PICTO_H40,PICTO_STATE_ON);					
				}
				else
				{
						Set_Pictogram_State(PICTO_H19,PICTO_STATE_ON);
						Set_Pictogram_State(PICTO_H20,PICTO_STATE_OFF);
						Set_Pictogram_State(PICTO_H21,PICTO_STATE_ON);
						Set_Pictogram_State(PICTO_H24,PICTO_STATE_OFF);
						Set_Pictogram_State(PICTO_H35,PICTO_STATE_ON);
						Set_Pictogram_State(PICTO_H36,PICTO_STATE_OFF);
						Set_Pictogram_State(PICTO_H37,PICTO_STATE_ON);
						Set_Pictogram_State(PICTO_H38,PICTO_STATE_OFF);
						Set_Pictogram_State(PICTO_H39,PICTO_STATE_ON);
						Set_Pictogram_State(PICTO_H40,PICTO_STATE_OFF);	
				}  
				blink_flag=~blink_flag;			

			}


			
			Set_TahometerScale_Value(_GetRPM(tDiff));
			//aParam[SCALE_TAHOMETER].Angle=_GetAngle_0(tDiff)*DEG2RAD;
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

float ScaleFilter(const FILTER *filter, float in)
{
		static float lastOut=0;
		float out = in * (filter->t_const - filter->wlag) + ((filter->wlag * lastOut) / filter->t_const);
		lastOut = out;
		return (out / filter->t_const); 
}

void Pictogram_Init(void)
{
		uint8_t i=0;
		
		for(i=0;i<PICTO_NUM;i++)
		{
				picto[i].palette_passive_state=_Colorspicto_gray;
				picto[i].picto->pPal->pPalEntries=picto[i].palette_passive_state;
				picto[i].state=PICTO_STATE_OFF;
		}
		
		picto[PICTO_H19].pos.x								=	120;
		picto[PICTO_H19].pos.y								=	10;
		picto[PICTO_H19].picto								=	&bmpicto_H19;
		picto[PICTO_H19].palette_active_state	=	_Colorspicto_red;		
		
		picto[PICTO_H20].pos.x								=	90;
		picto[PICTO_H20].pos.y								=	110;
		picto[PICTO_H20].picto								=	&bmpicto_H20;
		picto[PICTO_H20].palette_active_state	=	_Colorspicto_red;	

		picto[PICTO_H21].pos.x								=	60;
		picto[PICTO_H21].pos.y								=	210;
		picto[PICTO_H21].picto								=	&bmpicto_H21;
		picto[PICTO_H21].palette_active_state	=	_Colorspicto_red;	

		picto[PICTO_H24].pos.x								=	30;
		picto[PICTO_H24].pos.y								=	310;
		picto[PICTO_H24].picto								=	&bmpicto_H24;
		picto[PICTO_H24].palette_active_state	=	_Colorspicto_red;			
		
		picto[PICTO_H35].pos.x								=	10;
		picto[PICTO_H35].pos.y								=	410;
		picto[PICTO_H35].picto								=	&bmpicto_H35;
		picto[PICTO_H35].palette_active_state	=	_Colorspicto_red;	

		picto[PICTO_H36].pos.x								=	220;
		picto[PICTO_H36].pos.y								=	10;
		picto[PICTO_H36].picto								=	&bmpicto_H36;
		picto[PICTO_H36].palette_active_state	=	_Colorspicto_red;		
		
		picto[PICTO_H37].pos.x								=	190;
		picto[PICTO_H37].pos.y								=	110;
		picto[PICTO_H37].picto								=	&bmpicto_H37;
		picto[PICTO_H37].palette_active_state	=	_Colorspicto_red;	

		picto[PICTO_H38].pos.x								=	160;
		picto[PICTO_H38].pos.y								=	210;
		picto[PICTO_H38].picto								=	&bmpicto_H38;
		picto[PICTO_H38].palette_active_state	=	_Colorspicto_red;		
		
		picto[PICTO_H39].pos.x								=	130;
		picto[PICTO_H39].pos.y								=	310;
		picto[PICTO_H39].picto								=	&bmpicto_H39;
		picto[PICTO_H39].palette_active_state	=	_Colorspicto_red;

		picto[PICTO_H40].pos.x								=	110;
		picto[PICTO_H40].pos.y								=	410;
		picto[PICTO_H40].picto								=	&bmpicto_H40;
		picto[PICTO_H40].palette_active_state	=	_Colorspicto_red;		
		
		picto[PICTO_H41].pos.x								=	120;
		picto[PICTO_H41].pos.y								=	10;
		picto[PICTO_H41].picto								=	&bmpicto_H41;
		picto[PICTO_H41].palette_active_state	=	_Colorspicto_red;			
		
		picto[PICTO_H42].pos.x								=	90;
		picto[PICTO_H42].pos.y								=	110;
		picto[PICTO_H42].picto								=	&bmpicto_H42;
		picto[PICTO_H42].palette_active_state	=	_Colorspicto_red;	
		
		picto[PICTO_H43].pos.x								=	60;
		picto[PICTO_H43].pos.y								=	210;
		picto[PICTO_H43].picto								=	&bmpicto_H43;
		picto[PICTO_H43].palette_active_state	=	_Colorspicto_red;		

		picto[PICTO_H44].pos.x								=	30;
		picto[PICTO_H44].pos.y								=	310;
		picto[PICTO_H44].picto								=	&bmpicto_H44;
		picto[PICTO_H44].palette_active_state	=	_Colorspicto_red;	
		
		picto[PICTO_H45].pos.x								=	10;
		picto[PICTO_H45].pos.y								=	410;
		picto[PICTO_H45].picto								=	&bmpicto_H45;
		picto[PICTO_H45].palette_active_state	=	_Colorspicto_red;	

		picto[PICTO_H46].pos.x								=	220;
		picto[PICTO_H46].pos.y								=	10;
		picto[PICTO_H46].picto								=	&bmpicto_H46;
		picto[PICTO_H46].palette_active_state	=	_Colorspicto_red;	
		
		picto[PICTO_H47].pos.x								=	190;
		picto[PICTO_H47].pos.y								=	110;
		picto[PICTO_H47].picto								=	&bmpicto_H47;
		picto[PICTO_H47].palette_active_state	=	_Colorspicto_red;	

		picto[PICTO_H48].pos.x								=	160;
		picto[PICTO_H48].pos.y								=	210;
		picto[PICTO_H48].picto								=	&bmpicto_H48;
		picto[PICTO_H48].palette_active_state	=	_Colorspicto_red;

		picto[PICTO_H49].pos.x								=	130;
		picto[PICTO_H49].pos.y								=	310;
		picto[PICTO_H49].picto								=	&bmpicto_H49;
		picto[PICTO_H49].palette_active_state	=	_Colorspicto_red;	
		
		picto[PICTO_H51].pos.x								=	110;
		picto[PICTO_H51].pos.y								=	410;
		picto[PICTO_H51].picto								=	&bmpicto_H51;
		picto[PICTO_H51].palette_active_state	=	_Colorspicto_red;	
		
		
		/*******************************************************/

}

void Scales_Init(void)
{
//		scales[SCALE_TAHOMETER].pos.x=
//		scales[SCALE_TAHOMETER].pos.y=	
}