#include <arpa/inet.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>

uint32_t read_raw_32(const uint8_t* raw_packet, size_t offset)
{
	uint32_t val = 0;

	memcpy(&val, raw_packet + offset, sizeof(uint32_t));

	return (ntohl(val));
}

uint16_t read_raw_16(const uint8_t* raw_packet, size_t offset)
{
	uint16_t val = 0;

	memcpy(&val, raw_packet + offset, sizeof(uint16_t));

	return (ntohs(val));
}
