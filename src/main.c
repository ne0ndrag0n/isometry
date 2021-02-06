#include "md/debug.h"
#include "md/vdp.h"

int main(void) {
    mdWriteDebugFontColor( 0xEEE );
    mdLoadDebugFont();
    mdDebugPrint( "Goobers or rasinets? Squeak once for yes!", VDP_PLANE_A, 0, 0 );

    while ( 1 );

    return 0;
}
