#pragma once
#include <stdint.h>

#define VDP_PLANE_A 0xC000
#define VDP_PLANE_B 0xE000
#define VDP_PLANE_W 0xD000

#define VDP_VRAM_READ       0x00
#define VDP_VRAM_WRITE      0x01
#define VDP_CRAM_READ       0x08
#define VDP_CRAM_WRITE      0x03
#define VDP_VSRAM_READ      0x04
#define VDP_VSRAM_WRITE     0x05

#define VDP_CONTROL_WORD( address, mode )  ( ( 0x3FFFFFFF & ( (address) << 16 ) ) | ( (address) >> 14 ) | ( (mode) << 30 ) | ( ( (mode) << 2 ) & 0xF0 ) )

typedef uint16_t VdpPlane;
typedef uint16_t VdpWord;

uint16_t mdVdpPlaneWidth;
uint16_t mdVdpPlaneHeight;

uint32_t mdVdpGetControlWord( uint32_t address, uint32_t mode );
void mdVdpClearNametable( VdpPlane plane );

/**
 * Write word to vdp address
 */
extern void mdVdpWriteWord( uint32_t format, uint16_t data );