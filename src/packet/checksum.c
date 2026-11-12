#include <stdint.h>

uint16_t compute_checksum(const void* data, int size)
{
	long sum = 0;
	const uint16_t* ptr = data;

	while (size > 1)
	{
		sum += *ptr;
		size -= 2;
		++ptr;
	}

	if (size > 0)
		sum += *(uint8_t*)ptr;

	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	return (~sum);
}
