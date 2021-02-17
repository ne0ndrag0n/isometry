#pragma once
#include <stdint.h>
#include <stddef.h>

struct DmaQueueItem {
	uintptr_t sourceAddress;
	uint16_t size;
	uint32_t destinationWord;
};

struct DmaQueueItem dmaQueue[ 15 ];

void mdDmaEnqueue( uintptr_t source, uint16_t size, uint32_t destinationWord );
