#include "GUIDEMO.h"
#include "GUI.h"


extern GUI_CONST_STORAGE GUI_BITMAP bmpicto1_2;
extern GUI_COLOR _Colorspicto1_2[];

#define MAG         3
#define NUM_SCALES  3
#define LOGO_DIST    5
#define YSIZE_SCALE 380	//98

//#define FONT_GEAR &GUI_FontRounded22
#define STR_MSEC "msec/picture:\n"
#define STR_GEAR "Gear    1"

#define MSP_DIST_BOTTOM 40
#define NEEDLE_OFF_Y -120 //40

#define DEG2RAD      (3.1415926f / 180)


#include "tahometerScale.c"
#include "fuelScale.c"
#include "temperatureScale.c"
/*********************************************************************
*
*       static data, shape of polygons
*
**********************************************************************
*/
/*static GUI_POINT _aNeedle_0[] = {
  { MAG * ( 0), MAG * (  0 + 125)},
  { MAG * (-3), MAG * (-15 + 125)},
  { MAG * (-3), MAG * (-65 + 125)},
  { MAG * ( 3), MAG * (-65 + 125)},
  { MAG * ( 3), MAG * (-15 + 125)},
};*/
#define NEEDLE_LEN_VISIO	175
#define NEEDLE_CENTER_TO_VISIO 15	// расстояние от центра вращения до видимой части
#define NEEDLE_LEN_ALL	NEEDLE_LEN_VISIO+NEEDLE_CENTER_TO_VISIO		//общая длина стрелки

static GUI_POINT _aNeedle_0[] = { //tahometer needle
  { MAG * ( 0), MAG * (  0 + NEEDLE_LEN_ALL)},
  { MAG * (-3), MAG * (-15 + NEEDLE_LEN_ALL)},
  { MAG * (-3), MAG * (-NEEDLE_LEN_VISIO + NEEDLE_LEN_ALL)},
  { MAG * ( 3), MAG * (-NEEDLE_LEN_VISIO + NEEDLE_LEN_ALL)},
  { MAG * ( 3), MAG * (-15 + NEEDLE_LEN_ALL)},
};


#define FUELSCALE_NEEDLE_LEN_VISIO	95
#define FUELSCALE_NEEDLE_CENTER_TO_VISIO 5	// расстояние от центра вращения до видимой части
#define FUELSCALE_NEEDLE_LEN_ALL	FUELSCALE_NEEDLE_LEN_VISIO + FUELSCALE_NEEDLE_CENTER_TO_VISIO		//общая длина стрелки
static GUI_POINT _aNeedle_1[] = { //other needles
  { MAG * ( 0), MAG * (  0 + FUELSCALE_NEEDLE_LEN_ALL)},
  { MAG * (-3), MAG * (-15 + FUELSCALE_NEEDLE_LEN_ALL)},
  { MAG * (-3), MAG * (-FUELSCALE_NEEDLE_LEN_VISIO + FUELSCALE_NEEDLE_LEN_ALL)},
  { MAG * ( 3), MAG * (-FUELSCALE_NEEDLE_LEN_VISIO + FUELSCALE_NEEDLE_LEN_ALL)},
  { MAG * ( 3), MAG * (-15 + FUELSCALE_NEEDLE_LEN_ALL)},
};

static int _ySpace;

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
	{ _aNeedle_1, GUI_COUNTOF(_aNeedle_1) },
};

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
static float _GetAngle_1(int tDiff) {
  // Gear 1
  if ((tDiff >=    0) && (tDiff < 1000))  { return 225 -      0.02   *  tDiff;         }
  if ((tDiff >= 1000) && (tDiff <  1250)) { return 225 - 20;                           }
  // Gear 2
  if ((tDiff >= 1250) && (tDiff <  3250)) { return 225 - 20 - 0.01   * (tDiff - 1250); }
  if ((tDiff >= 3250) && (tDiff <  3500)) { return 225 - 40;                           }
  // Gear 3
  if ((tDiff >= 3500) && (tDiff <  6000)) { return 225 - 40 - 0.004  * (tDiff - 3500); }
  if ((tDiff >= 6000) && (tDiff <  6250)) { return 225 - 50;                           }
  // Gear 4
  if ((tDiff >= 6250) && (tDiff <  9250)) { return 225 - 50 - 0.004  * (tDiff - 6250); }
  if ((tDiff >= 9250) && (tDiff <  9500)) { return 225 - 62;                           }
  // Gear 5
  if ((tDiff >= 9500) && (tDiff < 15000)) { return 225 - 62 - 0.0012 * (tDiff - 9500);
  }
  return 225 - 90;
}

/*********************************************************************
*
*       DATA - _pfGetAngle[] - Array of function pointers to GetAngle functions
*/
static float (* _pfGetAngle[NUM_SCALES])(int tDiff) = {
  _GetAngle_0,
  _GetAngle_1,
	_GetAngle_1
};

/*********************************************************************
*
*       _Draw_0
*/
static void _Draw_0(void * p) {
  PARAM * pParam = (PARAM *)p;
  int     xSize;

  xSize = LCD_GetXSize();
  //
  // Fixed background
  //
  if (pParam->AutoDevInfo.DrawFixed) {
    GUI_ClearRect ((xSize - bmtahometerScale.XSize) , _ySpace + bmtahometerScale.YSize, ((xSize - bmtahometerScale.XSize) >> 1) + bmtahometerScale.XSize - 1, _ySpace + YSIZE_SCALE);
    GUI_DrawBitmap(&bmtahometerScale, (xSize - bmtahometerScale.XSize) , _ySpace);
  }
  //
  // Moving needle
  //
  GUI_SetColor(GUI_WHITE);
  GUI_AA_FillPolygon(pParam->aPoints, GUI_COUNTOF(_aNeedle_0), MAG * (xSize -(bmtahometerScale.XSize>>1)), MAG * (_ySpace + YSIZE_SCALE + NEEDLE_OFF_Y));

}

/*********************************************************************
*
*       _Draw_1
*/

#define FUELSCALE_POS_X					250	
#define FUELSCALE_POS_Y					ySize-bmfuelScale.YSize	
#define FUELSCALE_NEEDLE_POS_X	FUELSCALE_POS_X+80
#define FUELSCALE_NEEDLE_POS_Y	30

static void _Draw_1(void * p) {
  PARAM * pParam = (PARAM *)p;
  int     xSize, ySize;

  xSize = LCD_GetXSize();
	ySize = LCD_GetYSize();
  // Fixed background
  if (pParam->AutoDevInfo.DrawFixed) {
    GUI_ClearRect (FUELSCALE_POS_X, FUELSCALE_POS_Y,FUELSCALE_POS_X+ bmfuelScale.XSize - 1,FUELSCALE_POS_Y+ bmfuelScale.YSize - 1);
    GUI_DrawBitmap(&bmfuelScale, FUELSCALE_POS_X, FUELSCALE_POS_Y);
  }
  // Moving needle
  GUI_SetColor(GUI_WHITE);
  GUI_AA_FillPolygon(pParam->aPoints, GUI_COUNTOF(_aNeedle_1),  FUELSCALE_NEEDLE_POS_X,  FUELSCALE_NEEDLE_POS_Y);

}


#define TEMPERATURESCALE_POS_X	570	
#define TEMPERATURESCALE_POS_Y	ySize-bmtemperatureScale.YSize	
#define TEMPERATURESCALE_NEEDLE_POS_X	TEMPERATURESCALE_POS_X+80
#define TEMPERATURESCALE_NEEDLE_POS_Y	30

static void _Draw_2(void * p) {
  PARAM * pParam = (PARAM *)p;
  int     xSize, ySize;

  xSize = LCD_GetXSize();
	ySize = LCD_GetYSize();
  // Fixed background
  if (pParam->AutoDevInfo.DrawFixed) {
    GUI_ClearRect (TEMPERATURESCALE_POS_X,TEMPERATURESCALE_POS_Y, TEMPERATURESCALE_POS_X + bmtemperatureScale.XSize - 1, TEMPERATURESCALE_POS_Y + bmtemperatureScale.YSize - 1);
    GUI_DrawBitmap(&bmtemperatureScale, TEMPERATURESCALE_POS_X , TEMPERATURESCALE_POS_Y);
  }
  // Moving needle
 // GUI_SetColor(GUI_WHITE);
 // GUI_AA_FillPolygon(pParam->aPoints, GUI_COUNTOF(_aNeedle_1), MAG * (xSize >> 1), MAG * ((2 * (_ySpace + YSIZE_SCALE)) + NEEDLE_OFF_Y));

}

/*********************************************************************
*
*       DATA - _pfDraw[] - Array of function pointers to drawing routines
*/
void (* _pfDraw[NUM_SCALES])(void * p) = {
  _Draw_0,
  _Draw_1,
	_Draw_2
};

/*********************************************************************
*
*       _AutomotiveDemo
*/



static void _AutomotiveDemo(void) {
  GUI_AUTODEV aAutoDev [NUM_SCALES];               // Object for banding memory device
  PARAM       aParam   [NUM_SCALES] = {0};           // Parameters for drawing routine
  float       aAngleOld[NUM_SCALES];
  int         atDiff   [NUM_SCALES];
  int         atDiffOld[NUM_SCALES] = {0};
  int         tDiff, t0, t1, tBlinkNext;
  int         Cnt, i;
  int         ySize;

  tDiff = 0;
  ySize = LCD_GetYSize();
  //
  // Create GUI_AUTODEV-objects
  //
  for (i = 0; i < NUM_SCALES; i++) {
    //
    // Initialize values
    //
    aAngleOld[i] = -1;
    //
    // Create Device
    //
    GUI_MEMDEV_CreateAuto(&aAutoDev[i]);
    //
    // Pre-draw memory devices to avoid lag on slow targets
    //
    aParam[i].Angle = _pfGetAngle[i](tDiff) * DEG2RAD;
    GUI_RotatePolygon(aParam[i].aPoints, _aNeedle[i].pPolygon, _aNeedle[i].NumPoints, aParam[i].Angle);
    GUI_MEMDEV_DrawAuto(&aAutoDev[i], &aParam[i].AutoDevInfo, _pfDraw[i], &aParam[i]);
  }
  //
  // Run sample
  //
  t0 = GUI_GetTime();       // Get current time
//  for (Cnt = 0; ((tDiff = GUIDEMO_GetTime() - t0) < 15000) && !GUIDEMO_CheckCancel(); Cnt++) {
	Cnt = 0;
	tBlinkNext=1000;
	while(1){
		if((tDiff = GUI_GetTime() - t0) > TIME_4_2){
			Cnt=0;
			tBlinkNext=1000;
			t0 = GUI_GetTime();       // Get current time
		}
		if(tDiff > tBlinkNext){
			tBlinkNext+=1000;
			_Colorspicto1_2[1] ^= 0xFFFF00;
/*			if(tBlinkNext < 2000){
			}*/
		}
    //
    // Get values to display and calculate polygons
    //
    for (i = 0; i < NUM_SCALES; i++) {
      aParam[i].Angle = _pfGetAngle[i](tDiff) * DEG2RAD;
      if (aAngleOld[i] != aParam[i].Angle) {
        aAngleOld[i] = aParam[i].Angle;
        t1           = GUI_GetTime();
        GUI_RotatePolygon(aParam[i].aPoints, _aNeedle[i].pPolygon, _aNeedle[i].NumPoints, aParam[i].Angle);
        GUI_MEMDEV_DrawAuto(&aAutoDev[i], &aParam[i].AutoDevInfo, _pfDraw[i], &aParam[i]);
        atDiff[i]    = GUI_GetTime() - t1;
      }
    }

		GUI_DrawBitmap(&bmpicto1_2, 120, 150);

    GUI_Exec();
		Cnt++;	// Bykov
  }
  
  // Delete GUI_AUTODEV-objects
  
  for (i = 0; i < NUM_SCALES; i++) {
    GUI_MEMDEV_DeleteAuto(&aAutoDev[i]);
  }
}

/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       GUIDEMO_Automotive
*/
void GUIDEMO_Automotive(void) {
  GUI_AA_EnableHiRes();
  GUI_AA_SetFactor(MAG);
  _AutomotiveDemo();
  GUI_AA_DisableHiRes();
}

/*************************** End of file ****************************/
