#include "client.h"

void bitmap_set(uint8_t bitmap[static BITMAP_SIZE], size_t seq)
{
	size_t index = (seq / 8) % BITMAP_SIZE;
	bitmap[index] |= (1U << (seq % 8));
}

void bitmap_unset(uint8_t bitmap[static BITMAP_SIZE], size_t seq)
{
	size_t index = (seq / 8) % BITMAP_SIZE;
	bitmap[index] &= ~(1U << (seq % 8));
}

uint8_t bitmap_get(uint8_t bitmap[static BITMAP_SIZE], size_t seq)
{
	size_t index = (seq / 8) % BITMAP_SIZE;
	return ((bitmap[index] & (1U << (seq % 8))) != 0);
}
