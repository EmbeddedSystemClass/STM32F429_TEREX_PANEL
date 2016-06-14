#ifndef AUTOMOTIVE_PANEL_H
#define AUTOMOTIVE_PANEL_H

typedef enum
{
	PICTO_H19=0,
	PICTO_H20,
	PICTO_H21,
	PICTO_H24,
	PICTO_H35,
	PICTO_H36,
	PICTO_H37,
	PICTO_H38,
	PICTO_H39,
	PICTO_H40,
	PICTO_H41,
	PICTO_H42,
	PICTO_H43,
	PICTO_H44,
	PICTO_H45,
	PICTO_H46,
	PICTO_H47,
	PICTO_H48,
	PICTO_H49,
	PICTO_H51,
}enPictogram;

typedef enum
{
	PICTO_STATE_OFF=0,
	PICTO_STATE_ON,
}enPictoState;

void AutomotivePanel_Init(void);
void Set_Pictogram_State(enPictogram pictogram, enPictoState state);

#endif