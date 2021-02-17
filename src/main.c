#include "md/debug.h"
#include "md/vdp.h"
#include "md/joypad.h"
#include "md/dma.h"
#include "example_image.h"

int main(void) {
    mdWriteDebugFontColor( 0xEEE );
    mdLoadDebugFont();
    mdDebugPrint( "Goobers or rasinets? Squeak once for yes!", VDP_PLANE_A, 0, 0 );

    mdDmaEnqueue( ( struct DmaQueueItem ) {
        ( uint32_t ) vdp_image,
        32,
        VDP_CONTROL_WORD( 0x20, VDP_CRAM_WRITE )
    } );

    mdDmaEnqueue( ( struct DmaQueueItem ) {
        ( uint32_t ) ( vdp_image + 32 ),
        vdp_image_len - 32,
        VDP_CONTROL_WORD( 0x0c00, VDP_VRAM_WRITE )
    } );

    while ( 1 ) {
        if( mdJoyButtonSelected( JOY_BUTTON_START ) ) {
            mdDebugPrint( "Start", VDP_PLANE_A, 5, 5 );
        }
    }

    return 0;
}
