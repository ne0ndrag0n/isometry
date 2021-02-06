#include "md/debug.h"

void mdDebugPrint( const char* string, VdpPlane plane, uint8_t x, uint8_t y ) {
    plane += 2 * ( ( y * 64 ) + x );

    while( *string != 0 ) {
        mdVdpWriteWord( mdVdpGetControlWord( plane, VDP_VRAM_WRITE ), *string - 32 );
        plane += 2;
        string++;
    }
}