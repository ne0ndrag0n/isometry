#include "md/vdp.h"

uint16_t mdVdpPlaneWidth = 64;
uint16_t mdVdpPlaneHeight = 32;

void mdVdpClearNametable( VdpPlane plane ) {
    // This function will issue a dma fill for value 0x0000
    // For mdVdpPlaneWidth * mdVdpPlaneHeight beginning at the given plane address
}

uint32_t mdVdpGetControlWord( uint32_t address, uint32_t mode ) {
    return
        ( 0x3FFFFFFF & ( address << 16 ) ) |
        ( address >> 14 ) |
        ( mode << 30 ) |
        ( ( mode << 2 ) & 0xF0 );
}