#include <stdint.h>
#include <arpa/inet.h>
#include <string.h>

#include "ip.h"

static uint32_t read_raw_32(uint8_t* raw_packet, size_t offset)
{
	uint32_t val = 0;

	memcpy(&val, raw_packet + offset, sizeof(uint32_t));

	return (ntohl(val));
}

static uint16_t read_raw_16(uint8_t* raw_packet, size_t offset)
{
	uint16_t val = 0;

	memcpy(&val, raw_packet + offset, sizeof(uint16_t));

	return (ntohs(val));
}

int parse_ip_header(uint8_t* raw_packet, t_ip_header* ip_header)
{
	ip_header->version = IP_VERSION(raw_packet[IP_VERSION_OFFSET]);
	ip_header->ihl = IP_IHL(raw_packet[IP_VERSION_OFFSET]);
	ip_header->tos = raw_packet[IP_TOS_OFFSET];
	ip_header->total_len = read_raw_16(raw_packet, IP_TOTAL_LEN_OFFSET);
	ip_header->id = read_raw_16(raw_packet, IP_ID_OFFSET);
	ip_header->fragment = read_raw_16(raw_packet, IP_FRAG_OFFSET);
	ip_header->ttl = raw_packet[IP_TTL_OFFSET];
	ip_header->protocol = raw_packet[IP_PROTOCOL_OFFSET];
	ip_header->header_checksum = read_raw_16(raw_packet, IP_CHECKSUM_OFFSET);
	ip_header->src_addr = read_raw_32(raw_packet, IP_SRC_ADDR_OFFSET);
	ip_header->dest_addr = read_raw_32(raw_packet, IP_DEST_ADDR_OFFSET);
	return (0);
}
