#pragma once
#include <stdint.h>
#include <stddef.h>

#define VDP_DMA_FILL( value ) ( 0x00800000 | value )
#define VDP_DMA_COPY( value ) ( 0x00C00000 | value )

struct DmaQueueItem {
	uintptr_t sourceAddress;
	uint16_t size;
	uint32_t destinationWord;
};

struct DmaQueueItem dmaQueue[ 15 ];

void mdDmaEnqueue( uintptr_t source, uint16_t size, uint32_t destinationWord );
