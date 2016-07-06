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
* Source file: H37_transmiss_oil_temper                              *
* Dimensions:  87 * 80                                               *
* NumColors:   16                                                    *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmH37_transmiss_oil_temper;

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
static GUI_CONST_STORAGE GUI_COLOR _ColorsH37_transmiss_oil_temper[] = {
  0x000000, 0x111111, 0x222222, 0x333333,
  0x444444, 0x555555, 0x666666, 0x777777,
  0x888888, 0x999999, 0xAAAAAA, 0xBBBBBB,
  0xCCCCCC, 0xDDDDDD, 0xEEEEEE, 0xFFFFFF
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalH37_transmiss_oil_temper = {
  16,  // Number of entries
  0,   // No transparency
  &_ColorsH37_transmiss_oil_temper[0]
};

static GUI_CONST_STORAGE unsigned char _acH37_transmiss_oil_temper[] = {
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xDB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xBB, 0xCF, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5, 0x44, 0x4A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x8E, 0xFF, 0xFF, 0xD0, 0x00, 0x07, 0xFF, 0xFF, 0xFB, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x35, 0x55, 0x55, 0x55, 0x55, 0x50, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE8, 0x20, 0x09, 0xFF, 0xFF, 0xB0, 0x00, 0x05, 0xFF, 0xFF, 0xE2, 0x03, 0x9E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x00, 0x02, 0xFF, 0xFF, 0x90, 0x00, 0x04, 0xFF, 0xFF, 0x80, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF2, 0x00, 0x00, 0x9F, 0xFF, 0x70, 0x00, 0x03, 0xFF, 0xFE, 0x10, 0x00, 0x0A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xF4, 0x00, 0x00, 0x2C, 0x96, 0x20, 0x00, 0x01, 0x79, 0xC7, 0x00, 0x00, 0x1E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x73, 0xDF, 0xFF, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xC9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE4, 0x00, 0x2D, 0xFF, 0xF9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6F, 0xFF, 0xFB, 0x10, 0x6E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x30, 0x00, 0x02, 0xDC, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0xEF, 0xA1, 0x00, 0x04, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x60, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x02, 0x58, 0xAB, 0xBB, 0xA9, 0x75, 0x10, 0x00, 0x00, 0x00, 0x37, 0x00, 0x00, 0x00, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x27, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEB, 0x61, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0x00, 0x00, 0x00, 0x00, 0x3A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xFF, 0xFF, 0xFF, 0xFE, 0x81, 0x00, 0x00, 0x00, 0x00, 0x3E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x19, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x60, 0x00, 0x00, 0x00, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFB, 0xAF, 0xFF, 0xFB, 0x10, 0x00, 0x03, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0x20, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xE2, 0x02, 0x8E, 0xC1, 0x00, 0x00, 0x6E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE4, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD3, 0x00, 0x00, 0x6F, 0xFF, 0xD8, 0x5F, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0x60, 0x00, 0x01, 0x10, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA5, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x30, 0x00, 0x08, 0xB5, 0x10, 0x09, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFC, 0x00, 0x00, 0x00, 0x00, 0x00, 0x6F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x68, 0xAF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE3, 0x00, 0x00, 0x00, 0x00, 0x01, 0xDF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFC, 0x30, 0x00, 0x00, 0x00, 0x04, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x4C, 0x6F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x10, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xE5, 0x00, 0x00, 0x00, 0x1D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF9, 0x7F, 0x3D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA0, 0x00, 0x00, 0x00, 0x04, 0xEF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0xDF, 0x87, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF6, 0x00, 0x00, 0x00, 0x8F, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xF2, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x94, 0xFF, 0xD2, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x10, 0x00, 0x2B, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xA0, 0x00, 0x0B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x2B, 0xFF, 0xF6, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x70, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFE, 0xEF, 0xFF, 0x40, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0x4F, 0xFF, 0xFD, 0x1C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD1, 0x00, 0x0B, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xF3, 0x12, 0x34, 0x00, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC1, 0xCF, 0xFF, 0xFF, 0x73, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5, 0x00, 0x06, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xD0, 0x00, 0x00, 0x00, 0x00, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x37, 0xFF, 0xFF, 0xFF, 0xE3, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0x00, 0x00, 0x11, 0x11, 0x2F, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xA0, 0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0x3E, 0xFF, 0xFF, 0xFF, 0xFC, 0x1C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x10, 0x00, 0x00, 0x00, 0x0D, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0x70, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB1, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0x82, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x30, 0x00, 0x00, 0x00, 0x0B, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xC6, 0x10, 0x00, 0x00, 0x0A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x28, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x60, 0x00, 0x00, 0x00, 0x09, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xEB, 0x60, 0x00, 0x0C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0x4F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x1B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x03, 0x8D, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xD0, 0x00, 0x0D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC1, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA0, 0x00, 0x29, 0xDF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xC0, 0x00, 0x1E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x56, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE2, 0xAF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA0, 0x00, 0x4F, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xC0, 0x00, 0x1E, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x1D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x4F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA0, 0x00, 0x4F, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xD9, 0x40, 0x00, 0x0D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0x5F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x1C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA0, 0x00, 0x5F, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0x93, 0x00, 0x00, 0x00, 0x0C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x48, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x27, 0xCF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0x50, 0x00, 0x00, 0x00, 0x0A, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x74, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x60, 0x00, 0x00, 0x02, 0x7D, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0x70, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x40, 0x00, 0x00, 0x00, 0x0B, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xA0, 0x00, 0x00, 0x00, 0x04, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB0, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x81, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x10, 0x00, 0x00, 0x00, 0x0D, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xD3, 0x33, 0x43, 0x00, 0x01, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x83, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0x00, 0x00, 0x00, 0x00, 0x2F, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFD, 0x00, 0x00, 0xAF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1, 0xAF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x55, 0xFF, 0xFF, 0xFF, 0xFF, 0xF6, 0x00, 0x03, 0x54, 0x32, 0x7F, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0x30, 0x00, 0x4F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 0x5F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x18, 0xFF, 0xFF, 0xFF, 0xFF, 0xE1, 0x00, 0x0B, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x0C, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x1D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF9, 0x0D, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x1E, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFE, 0x40, 0x00, 0x04, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x16, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD1, 0x5F, 0xFF, 0xFF, 0xFF, 0xFE, 0x10, 0x00, 0x6F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xB2, 0x00, 0x00, 0x00, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x41, 0xDF, 0xFF, 0xFF, 0xFF, 0xF7, 0x00, 0x00, 0x2C, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xF7, 0x00, 0x00, 0x00, 0x00, 0x2E, 0xFF, 0xFF, 0xFF, 0xFF, 0xF6, 0x07, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD3, 0x1A, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x00, 0x01, 0xAF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xF4, 0x00, 0x00, 0x00, 0x00, 0x05, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x50, 0x29, 0xEF, 0xFF, 0xFF, 0xC7, 0x11, 0xAF, 0xFF, 0xFF, 0xFF, 0xFE, 0x20, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x04, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0x20, 0x03, 0x55, 0x42, 0x00, 0x4C, 0xFF, 0xFF, 0xFF, 0xFF, 0xE4, 0x00, 0x00, 0x00, 0x00, 0x01, 0xDF, 0xFF, 0xFF, 0xF5, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 0x02, 0xEF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0x50, 0x04, 0xBB, 0x00, 0x00, 0x09, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEB, 0x63, 0x11, 0x25, 0x7C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x50, 0x00, 0x02, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0x60, 0x00, 0xAF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x3E, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xD7, 0xDF, 0xFF, 0x80, 0x00, 0x00, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE5, 0x00, 0x00, 0x2E, 0xD7, 0x10, 0x2E, 0xFF, 0xFF, 0xF9, 0x00, 0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0x10, 0x05, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5, 0x00, 0x00, 0x05, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x30, 0x00, 0x01, 0xCF, 0xFF, 0xE9, 0xCF, 0xFF, 0xFF, 0xE1, 0x00, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC1, 0x00, 
        0xAF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xE2, 0x00, 0x00, 0x00, 0x2B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x91, 0x00, 0x00, 0x08, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x70, 0x04, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF9, 0x00, 
        0x2F, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x70, 0x00, 0x00, 0x00, 0x00, 0x5C, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA3, 0x00, 0x00, 0x00, 0x02, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x10, 0x0D, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x30, 
        0x0B, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x4A, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x83, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFB, 0x00, 0x4F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x90, 
        0x06, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xF4, 0x00, 0x00, 0x06, 0x40, 0x00, 0x00, 0x00, 0x14, 0x8A, 0xCD, 0xED, 0xDB, 0x97, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1D, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0x00, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD0, 
        0x03, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x20, 0x00, 0x8F, 0xF8, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xB8, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFF, 0xFF, 0xF5, 0x00, 0xCF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF1, 
        0x01, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD2, 0x1A, 0xFF, 0xFF, 0xB0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x9F, 0xFF, 0x90, 0x00, 0x4E, 0xFF, 0xFF, 0xFF, 0xFF, 0xF4, 0x00, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 
        0x00, 0xE0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xCF, 0xFF, 0xFF, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xFF, 0xFF, 0xF9, 0x16, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF4, 0x00, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF3, 
        0x00, 0xE0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x40, 0x00, 0x03, 0x85, 0x31, 0x00, 0x00, 0x01, 0x24, 0x40, 0x00, 0x00, 0xDF, 0xFF, 0xFF, 0xDF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF6, 0x00, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF1, 
        0x01, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x10, 0x00, 0x0A, 0xFF, 0xF9, 0x00, 0x00, 0x2E, 0xFF, 0xE2, 0x00, 0x00, 0xAF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 
        0x03, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFD, 0x00, 0x00, 0x4F, 0xFF, 0xFB, 0x00, 0x00, 0x4F, 0xFF, 0xF9, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x70, 
        0x07, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC6, 0x10, 0xCF, 0xFF, 0xFD, 0x00, 0x00, 0x6F, 0xFF, 0xFF, 0x20, 0x01, 0x9F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x20, 0x0B, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x10, 
        0x0C, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEA, 0xFF, 0xFF, 0xFD, 0x00, 0x00, 0x8F, 0xFF, 0xFF, 0xA5, 0xAE, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x90, 0x02, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF6, 0x00, 
        0x4F, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x53, 0x22, 0xBF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF2, 0x00, 0x5F, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x90, 0x00, 
        0xCF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x04, 0xEF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF7, 0x00, 0x08, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xA0, 0x00, 0x19, 0xEF, 0xFF, 0xFF, 0xFB, 0x30, 0x00, 0x5F, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFA, 0x10, 0x00, 0x14, 0x78, 0x75, 0x20, 0x00, 0x06, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xD4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0xAF, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xB5, 0x10, 0x00, 0x00, 0x03, 0x9E, 0xFF, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xEC, 0xA9, 0x9B, 0xEF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xF0,
  0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 
        0xFF, 0xF0
};

GUI_CONST_STORAGE GUI_BITMAP bmH37_transmiss_oil_temper = {
  87, // xSize
  80, // ySize
  44, // BytesPerLine
  4, // BitsPerPixel
  _acH37_transmiss_oil_temper,  // Pointer to picture data (indices)
  &_PalH37_transmiss_oil_temper   // Pointer to palette
};

/*************************** End of file ****************************/
