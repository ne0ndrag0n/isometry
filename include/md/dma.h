#pragma once
#include <stdint.h>
#include <stddef.h>

struct DmaQueueItem {
	uint32_t sourceAddress;
	uint16_t size;
	uint32_t destinationWord;
};

struct DmaQueueItem dmaQueue[ 15 ];

void mdDmaEnqueue( struct DmaQueueItem item );
