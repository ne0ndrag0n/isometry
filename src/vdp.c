#include "md/vdp.h"
#include "md/dma.h"

uint16_t mdVdpPlaneWidth = 64;
uint16_t mdVdpPlaneHeight = 32;

void mdVdpClearNametable( VdpPlane plane ) {
    // Plane width * plane height * each nametable entry is a word
    uint16_t totalBytes = mdVdpPlaneWidth * mdVdpPlaneHeight * 2;

    // Stage DMA FILL for byte 0x00 for `totalBytes` at location `plane`
    mdDmaEnqueue( VDP_DMA_FILL( 0 ), totalBytes, VDP_CONTROL_WORD( plane, VDP_VRAM_WRITE ) );
}

uint32_t mdVdpGetControlWord( uint32_t address, uint32_t mode ) {
    return
        ( 0x3FFFFFFF & ( address << 16 ) ) |
        ( address >> 14 ) |
        ( mode << 30 ) |
        ( ( mode << 2 ) & 0xF0 );
}