#pragma once
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