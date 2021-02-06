#include "md/vdp.h"

uint32_t mdVdpGetControlWord( uint32_t address, uint32_t mode ) {
    return
        ( 0x3FFFFFFF & ( address << 16 ) ) |
        ( address >> 14 ) |
        ( mode << 30 ) |
        ( ( mode << 2 ) & 0xF0 );
}