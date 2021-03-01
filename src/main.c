#include "md/debug.h"
#include "md/vdp.h"
#include "md/joypad.h"
#include "md/dma.h"
#include "resource/noodle.h"
#include <stdint.h>

int main(void) {
    mdWriteDebugFontColor( 0xEEE );
    mdLoadDebugFont();
    mdDebugPrint( "Goobers or rasinets? Squeak once for yes!", VDP_PLANE_A, 0, 0 );

    mdDmaEnqueue( ( uintptr_t ) noodle, 32, VDP_CONTROL_WORD( 0x20, VDP_CRAM_WRITE ) );
    mdDmaEnqueue( ( ( uintptr_t ) noodle ) + 32, noodle_len - 32, VDP_CONTROL_WORD( 0x0c00, VDP_VRAM_WRITE ) );

    mdVdpWriteNametable(
        VDP_PLANE_B,
        VDP_NAMETABLE_ENTRY( 0, 1, VDP_FLIP_NONE, 0x60 ),
        VDP_DIMENSIONS( 0, 0, 40, 28 )
    );

    while ( 1 ) {
        if( mdJoyButtonSelected( JOY_BUTTON_START ) ) {
            mdVdpSetPlaneScroll( VDP_SCROLL_SETTINGS( VDP_VSCROLL_PLANE_B, 0x0030 ) );
        }
    }

    return 0;
}
