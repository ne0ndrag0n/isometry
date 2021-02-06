#pragma once
#include "md/vdp.h"
#include <stdint.h>

/**
 * Write the specified color to palette 0, which is used by the debug font
 *
 * @param   {uint16_t}      color
 */
extern void mdWriteDebugFontColor( uint16_t color );

/**
 * Load debug font into top of VDP RAM
 */
extern void mdLoadDebugFont();

/**
 * Print string at given location
 */
void mdDebugPrint( const char* string, VdpPlane plane, uint8_t x, uint8_t y );