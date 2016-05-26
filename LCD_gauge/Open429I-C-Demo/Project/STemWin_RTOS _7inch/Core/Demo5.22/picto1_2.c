/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Bitmap Converter for emWin V5.22.                           *
*        Compiled Jul  4 2013, 12:18:24                              *
*        (c) 1998 - 2013 Segger Microcontroller GmbH && Co. KG       *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: picto1_2                                              *
* Dimensions:  80 * 62                                               *
* NumColors:   2                                                     *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmpicto1_2;

/*********************************************************************
*
*       Palette
*
*  Description
*    The following are the entries of the palette table.
*    The entries are stored as a 32-bit values of which 24 bits are
*    actually used according to the following bit mask: 0xBBGGRR
*
*    The lower   8 bits represent the Red   component.
*    The middle  8 bits represent the Green component.
*    The highest 8 bits represent the Blue  component.
*/
/*static GUI_CONST_STORAGE*/ GUI_COLOR _Colorspicto1_2[] = {
  0x000000, 0xFFFFFF
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _Palpicto1_2 = {
  2,  // Number of entries
  0,  // No transparency
  &_Colorspicto1_2[0]
};

static GUI_CONST_STORAGE unsigned char _acpicto1_2[] = {
  ________, ________, ________, ________, ________, ________, ________, ________, ________, ________,
  ________, ________, ________, ________, ________, ________, ________, ________, ________, ________,
  ________, ________, ________, ________, __XXXXXX, XXXXXX__, ________, ________, ________, ________,
  ________, ________, ________, ________, XXXXXXXX, XXXXXXXX, ________, ________, ________, ________,
  ________, ______XX, X_______, ______XX, XXXXXXXX, XXXXXXXX, XX______, _______X, XX______, ________,
  ________, _____XXX, XX______, ____XXXX, XXXXXXXX, XXXXXXXX, XXXX____, ______XX, XX______, ________,
  ________, ____XXXX, XXX_____, __XXXXXX, XXXXXXXX, XXXXXXXX, XXXXXX__, _____XXX, XXX_____, ________,
  ________, ____XXXX, XXX_____, XXXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, _____XXX, XXXX____, ________,
  ________, ___XXXXX, XXX____X, XXXXXXXX, XXX_____, ______XX, XXXXXXXX, XX____XX, XXXXX___, ________,
  ________, __XXXXXX, XX____XX, XXXXXXXX, ________, ________, _XXXXXXX, XXX____X, XXXXX___, ________,
  ________, _XXXXXXX, X___XXXX, XXXXXX__, ________, ________, __XXXXXX, XXXXX___, XXXXXX__, ________,
  ________, _XXXXXXX, ___XXXXX, XXXX____, ________, ________, ____XXXX, XXXXXX__, XXXXXXX_, ________,
  ________, XXXXXXX_, __XXXXXX, XX______, ________, ________, _____XXX, XXXXXXX_, _XXXXXX_, ________,
  ________, XXXXXXX_, _XXXXXXX, X_______, ________, ________, _______X, XXXXXXXX, __XXXXXX, ________,
  _______X, XXXXXX__, XXXXXXXX, X_______, ________, ________, ________, XXXXXXXX, __XXXXXX, X_______,
  _______X, XXXXXX__, XXXXXXXX, ________, ________, ________, ________, _XXXXXXX, X__XXXXX, X_______,
  _______X, XXXXX__X, XXXXXX__, ________, ________, ________, ________, __XXXXXX, X___XXXX, XX______,
  ______XX, XXXX___X, XXXXX___, ________, ________, ________, ________, ___XXXXX, XX__XXXX, XX______,
  ______XX, XXXX__XX, XXXXX___, ________, ________, ________, ________, ____XXXX, XX__XXXX, XXX_____,
  ______XX, XXX___XX, XXXX____, ______XX, ________, ________, XXX_____, ____XXXX, XXX__XXX, XXX_____,
  _____XXX, XXX___XX, XXX_____, ______XX, X_______, ________, XXX_____, ____XXXX, XXX__XXX, XXXX____,
  _____XXX, XXX__XXX, XXX_____, ______XX, XX______, _______X, XXX_____, _____XXX, XXX__XXX, XXXX____,
  _____XXX, XXX__XXX, XXX_____, ______XX, _XX_____, ______XX, XXX_____, _____XXX, XXXX__XX, XXXX____,
  ____XXXX, XXX__XXX, XX______, ______XX, __XX____, _____XXX, _XX_____, ______XX, XXXX__XX, XXXX____,
  ____XXXX, XX___XXX, XX______, ______XX, __XXX___, ____XXX_, _XX_____, ______XX, XXXX__XX, XXXX____,
  ____XXXX, XX___XXX, XX____XX, XXXXXXXX, ___XXX__, ___XXX__, _XXXXXXX, XXX___XX, XXXX__XX, XXXX____,
  ____XXXX, XX__XXXX, XX___XXX, XXXXXXXX, ____XX__, __XXX___, _XXXXXXX, XXXX__XX, XXXX__XX, XXXX____,
  ____XXXX, XX__XXXX, XX___XXX, ________, _____XX_, _XXX____, ________, _XXX___X, XXXXX_XX, XXXX____,
  ____XXXX, XX__XXXX, XX___XXX, ________, ______XX, XXX_____, ________, _XXX___X, XXXXX_XX, XXXX____,
  ____XXXX, X___XXXX, XX___XXX, ________, ______XX, XX______, ________, _XXX___X, XXXXX_XX, XXXX____,
  ____XXXX, X___XXXX, XX___XXX, ________, ______XX, _XX_____, ________, _XXX___X, XXXXX_XX, XXXX____,
  ____XXXX, X___XXXX, XX___XXX, XXXXXXXX, _____XX_, __XX____, XXXXXXXX, XXXX___X, XXXXX_XX, XXXX____,
  ____XXXX, XX__XXXX, XX___XXX, XXXXXXXX, X___XX__, ___XX___, XXXXXXXX, XXX____X, XXXXX_XX, XXXX____,
  ____XXXX, XX__XXXX, XX______, ________, X__XX___, ___XXX__, XX______, _______X, XXXXX_XX, XXXX____,
  ____XXXX, XX__XXXX, XX______, ________, X_XX____, ____XXX_, XX______, ______XX, XXXX__XX, XXXX____,
  ____XXXX, XX___XXX, XX______, ________, XXXX____, _____XXX, XX______, ______XX, XXXX__XX, XXXX____,
  ____XXXX, XX___XXX, XX______, ________, XXX_____, ______XX, XX______, ______XX, XXXX__XX, XXXX____,
  ____XXXX, XXX__XXX, XX______, ________, XX______, _______X, XX______, ______XX, XXXX__XX, XXXX____,
  _____XXX, XXX__XXX, XXX_____, ________, ________, ________, ________, _____XXX, XXX___XX, XXXX____,
  _____XXX, XXX__XXX, XXX_____, ________, ________, ________, ________, _____XXX, XXX___XX, XXXX____,
  _____XXX, XXX___XX, XXX_____, ________, ________, ________, ________, ____XXXX, XXX__XXX, XXX_____,
  ______XX, XXX___XX, XXXX____, ________, ________, ________, ________, ____XXXX, XXX__XXX, XXX_____,
  ______XX, XXXX__XX, XXXXX___, ________, ________, ________, ________, ____XXXX, XX___XXX, XXX_____,
  ______XX, XXXXX__X, XXXXXX__, ________, ________, ________, ________, ___XXXXX, XX__XXXX, XX______,
  _______X, XXXXX__X, XXXXXXX_, ________, ________, ________, ________, __XXXXXX, X___XXXX, XX______,
  _______X, XXXXXX__, XXXXXXXX, ________, ________, ________, ________, _XXXXXXX, X__XXXXX, X_______,
  ________, XXXXXX__, XXXXXXXX, ________, ________, ________, ________, XXXXXXXX, __XXXXXX, X_______,
  ________, XXXXXXX_, _XXXXXXX, X_______, ________, ________, _______X, XXXXXXX_, __XXXXXX, ________,
  ________, _XXXXXX_, __XXXXXX, XX______, ________, ________, _____XXX, XXXXXXX_, _XXXXXXX, ________,
  ________, __XXXXXX, ___XXXXX, XXXX____, ________, ________, ____XXXX, XXXXXX__, XXXXXXX_, ________,
  ________, __XXXXXX, X___XXXX, XXXXXXX_, ________, ________, ___XXXXX, XXXX____, XXXXXX__, ________,
  ________, ___XXXXX, XX____XX, XXXXXXXX, ________, ________, _XXXXXXX, XXX____X, XXXXX___, ________,
  ________, ____XXXX, XXX____X, XXXXXXXX, XXXX____, _____XXX, XXXXXXXX, XX____XX, XXXXX___, ________,
  ________, ____XXXX, XXX_____, _XXXXXXX, XXXXXXXX, XXXXXXXX, XXXXXXXX, _____XXX, XXXX____, ________,
  ________, _____XXX, XXXX____, ___XXXXX, XXXXXXXX, XXXXXXXX, XXXXXX__, _____XXX, XXX_____, ________,
  ________, _____XXX, XXX_____, _____XXX, XXXXXXXX, XXXXXXXX, XXXX____, ______XX, XX______, ________,
  ________, ______XX, XX______, _______X, XXXXXXXX, XXXXXXXX, XX______, _______X, X_______, ________,
  ________, ________, ________, ________, _XXXXXXX, XXXXXXXX, ________, ________, ________, ________,
  ________, ________, ________, ________, ___XXXXX, XXXXXX__, ________, ________, ________, ________,
  ________, ________, ________, ________, ________, ________, ________, ________, ________, ________,
  ________, ________, ________, ________, ________, ________, ________, ________, ________, ________,
  X_______, ________, ________, ________, ________, ________, ________, ________, ________, ________
};

GUI_CONST_STORAGE GUI_BITMAP bmpicto1_2 = {
  80, // xSize
  62, // ySize
  10, // BytesPerLine
  1, // BitsPerPixel
  _acpicto1_2,  // Pointer to picture data (indices)
  &_Palpicto1_2   // Pointer to palette
};

/*************************** End of file ****************************/
