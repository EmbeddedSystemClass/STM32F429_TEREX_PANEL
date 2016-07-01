#include "GUI.h"
#include <stdint.h>
#include "automotivePanel.h"
#include "global_includes.h"

//-----------
#include "tahometerScale.c"
#include "speedometerScale.c"
#include "fuelScale.c"
#include "temperatureScale.c"
//-----------

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

static enDisplay currentDisplay=DISPLAY_0;

#define MAG         3
#define NUM_SCALES  4

typedef enum
{
	SCALE_TAHOMETER=0,
	SCALE_FUEL=1,
	SCALE_TEMPERATURE=2,
	SCALE_SPEEDOMETER=3,
}enScale;
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
		float lastOut;
}
FILTER;

static FILTER TahometerScaleFilter={TAHOMETERSCALE_FILTER_TCONST,TAHOMETERSCALE_WLAG,0};
static FILTER FuelScaleFilter={FUELSCALE_FILTER_TCONST,FUELSCALE_WLAG,0};
static FILTER TemperatureScaleFilter={TEMPERATURESCALE_FILTER_TCONST,TEMPERATURESCALE_WLAG,0};
static FILTER SpeedometerScaleFilter={SPEEDOMETERSCALE_FILTER_TCONST,SPEEDOMETERSCALE_WLAG,0};

float ScaleFilter(FILTER *filter, float in);
/***************************************************/

typedef struct {
	GUI_AUTODEV 		 aAutoDev;
  GUI_AUTODEV_INFO AutoDevInfo; // Information about what has to be displayed
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
	GUI_POINT   needle_points[7];  // Polygon data
	PARAM			  param;
  FILTER *filter;	
	enScaleState state;
	enDisplay		display;
} SCALE;

/*********************************************************************
*
*       static data, shape of polygons
*
**********************************************************************
*/

#define NEEDLE_0_LEN_VISIO	175
#define NEEDLE_0_CENTER_TO_VISIO 15	// расстояние от центра вращения до видимой части
#define NEEDLE_0_LEN_ALL	NEEDLE_0_LEN_VISIO + NEEDLE_0_CENTER_TO_VISIO		//общая длина стрелки

static GUI_POINT _aNeedle_0[] = { //tahometer needle
  { MAG * ( 0), MAG * (  0 + NEEDLE_0_LEN_ALL)},
  { MAG * (-3), MAG * (-15 + NEEDLE_0_LEN_ALL)},
  { MAG * (-3), MAG * (-NEEDLE_0_LEN_VISIO + NEEDLE_0_LEN_ALL)},
  { MAG * ( 3), MAG * (-NEEDLE_0_LEN_VISIO + NEEDLE_0_LEN_ALL)},
  { MAG * ( 3), MAG * (-15 + NEEDLE_0_LEN_ALL)},
};


#define NEEDLE_1_LEN_VISIO	100
#define NEEDLE_1_CENTER_TO_VISIO 50	// расстояние от центра вращения до видимой части
#define NEEDLE_1_LEN_ALL	NEEDLE_1_LEN_VISIO + NEEDLE_1_CENTER_TO_VISIO		//общая длина стрелки
static GUI_POINT _aNeedle_1[] = { //other needles
  { MAG * ( 0), MAG * (  0 + NEEDLE_1_LEN_ALL)},
  { MAG * (-3), MAG * (-15 + NEEDLE_1_LEN_ALL)},
  { MAG * (-3), MAG * (-NEEDLE_1_LEN_VISIO + NEEDLE_1_LEN_ALL)},
  { MAG * ( 3), MAG * (-NEEDLE_1_LEN_VISIO + NEEDLE_1_LEN_ALL)},
  { MAG * ( 3), MAG * (-15 + NEEDLE_1_LEN_ALL)},
};


static NEEDLE _aNeedle[2] = { 
  { _aNeedle_0, GUI_COUNTOF(_aNeedle_0) },
  { _aNeedle_1, GUI_COUNTOF(_aNeedle_1) },
};

static SCALE scales[NUM_SCALES]=
{
	{&bmtahometerScale	,{250,  0},&_aNeedle[0],{513,251},{0},{{0},{0},270.0,270.0, 90.0,0.0,0.0,2500.0},&TahometerScaleFilter		,SCALE_STATE_DRAW,DISPLAY_0},
	{&bmfuelScale				,{250,290},&_aNeedle[1],{450,455},{0},{{0},{0},270.0,270.0,198.0,0.0,0.0, 100.0},&FuelScaleFilter				,SCALE_STATE_DRAW,DISPLAY_0},
	{&bmtemperatureScale,{570,290},&_aNeedle[1],{770,455},{0},{{0},{0},270.0,270.0,198.0,0.0,0.0, 120.0},&TemperatureScaleFilter	,SCALE_STATE_DRAW,DISPLAY_0},
	{&bmspeedometerScale,{250,  0},&_aNeedle[0],{513,251},{0},{{0},{0},270.0,270.0, 90.0,0.0,0.0,  40.0},&SpeedometerScaleFilter	,SCALE_STATE_DRAW,DISPLAY_1},
};
/***************************************************/

typedef struct
{
	GUI_POINT pos;
	GUI_BITMAP *picto;
	GUI_COLOR  *palette_active_state;
	GUI_COLOR  *palette_passive_state;
	enPictoState state;	
	enDisplay		display;
}
PICTOGRAM;

#define PICTO_NUM	20
static PICTOGRAM picto[PICTO_NUM]=
{
{{120, 10},&bmpicto_H19,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_0},
{{ 90,110},&bmpicto_H20,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_0},
{{ 60,210},&bmpicto_H21,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_0},
{{ 30,310},&bmpicto_H24,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_0},
{{ 10,410},&bmpicto_H35,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_0},
{{220, 10},&bmpicto_H36,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_0},
{{190,110},&bmpicto_H37,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_0},
{{160,210},&bmpicto_H38,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_0},
{{130,310},&bmpicto_H39,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_0},
{{110,410},&bmpicto_H40,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_0},
{{120, 10},&bmpicto_H41,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_1},
{{ 90,110},&bmpicto_H42,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_1},
{{ 60,210},&bmpicto_H43,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_1},
{{ 30,310},&bmpicto_H44,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_1},
{{ 10,410},&bmpicto_H45,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_1},
{{220, 10},&bmpicto_H46,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_1},
{{190,110},&bmpicto_H47,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_1},
{{160,210},&bmpicto_H48,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_1},
{{130,310},&bmpicto_H49,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_1},
{{110,410},&bmpicto_H51,_Colorspicto_red,_Colorspicto_gray,PICTO_STATE_OFF,DISPLAY_1}
};


/***************************************************/
#define AutomotivePanel_Task_PRIO    ( tskIDLE_PRIORITY  + 9 )
#define AutomotivePanel_Task_STACK   ( 3048 )
xTaskHandle                   				AutomotivePanel_Task_Handle;
static void AutomotivePanel_Task(void * pvParameters);

//#define FONT_GEAR &GUI_FontRounded22

#define DEG2RAD      (3.1415926f / 180)

static int _OldGear = 0;



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
static void _Draw_Scale(void * p)
{
		SCALE *pScale=(SCALE *)p;
		if(pScale->param.AutoDevInfo.DrawFixed)
		{
		    GUI_ClearRect (pScale->scale_pos.x ,pScale->scale_pos.y, pScale->scale_pos.x  + pScale->scale->XSize /*- 1*/+10,pScale->scale_pos.y+ pScale->scale->YSize - 1);
		    GUI_DrawBitmap(pScale->scale, pScale->scale_pos.x , pScale->scale_pos.y);		
		}
		GUI_SetColor(GUI_WHITE);
		GUI_AA_FillPolygon(pScale->needle_points, pScale->needle->NumPoints,  MAG*pScale->needle_pos.x,  MAG*pScale->needle_pos.y);
}
/*********************************************************************/
void (* _pfDraw[NUM_SCALES])(void * p) = {
  _Draw_Scale,
  _Draw_Scale,
	_Draw_Scale,
	_Draw_Scale,
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
	
	if(picto[pictogram].display==currentDisplay)
	{
			GUI_DrawBitmap(picto[pictogram].picto, picto[pictogram].pos.x , picto[pictogram].pos.y );
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

void Automotive_Panel_ChangeDisplay(enDisplay display)
{
		uint16_t xSize, ySize;
		uint8_t i=0;
		xSize=LCD_GetXSize();
		ySize=LCD_GetYSize();
		GUI_ClearRect (0 ,0, xSize - 1,ySize - 1);
		currentDisplay=display;
	
		for (i = 0; i < NUM_SCALES; i++) 
		{
			scales[i].param.AutoDevInfo.DrawFixed=1;
		}
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

  for (i = 0; i < NUM_SCALES; i++) 
	{
		aAngleOld[i] = -1;	 
		Set_ScaleValue(i,0);
    GUI_MEMDEV_CreateAuto(&scales[i].param.aAutoDev);
		if(scales[i].display==currentDisplay)
		{
			GUI_RotatePolygon(scales[i].needle_points, scales[i].needle->pPolygon, scales[i].needle->NumPoints, scales[i].param.Angle);
			GUI_MEMDEV_DrawAuto(&scales[i].param.aAutoDev, &scales[i].param.AutoDevInfo, _pfDraw[i], &scales[i]);
		}
  }
		
  t0 = GUI_GetTime(); 

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
						Automotive_Panel_ChangeDisplay(DISPLAY_0);
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
						Automotive_Panel_ChangeDisplay(DISPLAY_1);
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
			
			Set_ScaleValue(SCALE_TAHOMETER,   _GetRPM(tDiff));
			Set_ScaleValue(SCALE_FUEL, 		 		_GetFuel(tDiff));
			Set_ScaleValue(SCALE_TEMPERATURE, _GetTemperature(tDiff));
			Set_ScaleValue(SCALE_SPEEDOMETER, _GetSpeed(tDiff));
			
			for (i = 0; i < NUM_SCALES; i++) 
			{
				if (aAngleOld[i] != scales[i].param.Angle)
				{
					aAngleOld[i] = scales[i].param.Angle;
					t1           = GUI_GetTime();
					if(scales[i].display==currentDisplay)
					{
						GUI_RotatePolygon(scales[i].needle_points, scales[i].needle->pPolygon, scales[i].needle->NumPoints, scales[i].param.Angle);
						GUI_MEMDEV_DrawAuto(&scales[i].param.aAutoDev, &scales[i].param.AutoDevInfo, _pfDraw[i], &scales[i]);
					}
					atDiff[i]    = GUI_GetTime() - t1;
				}
			}			
			GUI_Exec();
  }
  
	// Delete GUI_AUTODEV-objects
  
  for (i = 0; i < NUM_SCALES; i++) 
	{
    GUI_MEMDEV_DeleteAuto(&scales[i].param.aAutoDev);
  }
}

float ScaleFilter(FILTER *filter, float in)
{
		float out = in * (filter->t_const - filter->wlag) + ((filter->wlag * filter->lastOut) / filter->t_const);
		filter->lastOut = out;
		return (out / filter->t_const); 
}
