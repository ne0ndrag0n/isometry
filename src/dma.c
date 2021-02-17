#include "md/dma.h"
#include "md/debug.h"

struct DmaQueueItem dmaQueue[ 15 ] = { 0 };

void mdDmaEnqueue( uint32_t source, uint16_t size, uint32_t destinationWord ) {
    // Find nearest null sourceAddress
    for( size_t i = 0; i != 15; i++ ) {
        if( dmaQueue[ i ].sourceAddress == 0 ) {
            dmaQueue[ i ].sourceAddress = source;
            dmaQueue[ i ].size = size;
            dmaQueue[ i ].destinationWord = destinationWord;

            // Set bit CD5 to mark dma operation.
            // Doing it here means we don't do it in vblank.
            dmaQueue[ i ].destinationWord |= 0x00000080;
            // All DMA operations use words instead of bytes
            dmaQueue[ i ].sourceAddress >>= 1;
            dmaQueue[ i ].size >>= 1;
            return;
        }
    }

    // DMA queue full, this is a fatal condition
    mdDebugPrint( "fatal: DMA queue full!", VDP_PLANE_A, 1, 1 );
    while( 1 );
}