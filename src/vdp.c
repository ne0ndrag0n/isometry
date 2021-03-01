#include "md/vdp.h"
#include "md/dma.h"

uint16_t mdVdpPlaneWidth = 64;
uint16_t mdVdpPlaneHeight = 32;

void mdVdpSetPlaneScroll( uint32_t settings ) {
    // Upper word contains the location of a whole-plane-mode scroll table index
    // Lower word contains the amount by which to set

    if( ( ( settings & 0xFF000000 ) >> 16 ) == VDP_VSCROLL ) {
        // vscroll mode - write to vsram
        mdVdpWriteWord(
            VDP_CONTROL_WORD( ( ( settings & 0x00FF0000 ) >> 16 ), VDP_VSRAM_WRITE ),
            settings & 0x0000FFFF
        );
    } else {
        // hscroll mode - write to vram
        mdVdpWriteWord(
            VDP_CONTROL_WORD( ( ( settings & 0xFFFF0000 ) >> 16 ), VDP_VRAM_WRITE ),
            settings & 0x0000FFFF
        );
    }
}

void mdVdpClearNametable( VdpPlane plane ) {
    // Plane width * plane height * each nametable entry is a word
    uint16_t totalBytes = mdVdpPlaneWidth * mdVdpPlaneHeight * 2;

    // Stage DMA FILL for byte 0x00 for `totalBytes` at location `plane`
    mdDmaEnqueue( VDP_DMA_FILL( 0 ), totalBytes, VDP_CONTROL_WORD( plane, VDP_VRAM_WRITE ) );
}

void mdVdpWriteNametable( VdpPlane plane, uint16_t tileAttribute, uint32_t dimensions ) {
    // Unpack arguments
    uint16_t x = ( dimensions & 0xFF000000 ) >> 24;
    uint16_t y = ( dimensions & 0x00FF0000 ) >> 16;
    uint16_t maxX = x + ( ( dimensions & 0x0000FF00 ) >> 8 );
    uint16_t maxY = y + ( dimensions & 0x000000FF );
    uint16_t baseTile = tileAttribute & 0x07FF;

    for( ; y != maxY; y++ ) {
        uint16_t rowAddress = plane + ( ( mdVdpPlaneWidth * y ) * 2 );
        for( uint16_t rowX = x; rowX != maxX; rowX++ ) {
            uint16_t address = rowAddress + ( rowX * 2 );
            mdVdpWriteWord( VDP_CONTROL_WORD( address, VDP_VRAM_WRITE ), tileAttribute );
            tileAttribute = ( tileAttribute & 0xF800 ) | ++baseTile;
        }
    }
}

uint32_t mdVdpGetControlWord( uint32_t address, uint32_t mode ) {
    return
        ( 0x3FFFFFFF & ( address << 16 ) ) |
        ( address >> 14 ) |
        ( mode << 30 ) |
        ( ( mode << 2 ) & 0xF0 );
}