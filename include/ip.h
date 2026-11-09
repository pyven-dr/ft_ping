#ifndef IP_H
#define IP_H

#include <stdint.h>
#include <stddef.h>

typedef struct s_rx_packet t_rx_packet;

#define IP_IHL(byte)		((byte) & 0xF)
#define IP_VERSION(byte)	((byte) >> 4)

#define IP_VERSION_OFFSET	0
#define IP_TOS_OFFSET		1
#define IP_TOTAL_LEN_OFFSET	2
#define IP_ID_OFFSET		4
#define IP_FRAG_OFFSET		6
#define IP_TTL_OFFSET		8
#define IP_PROTOCOL_OFFSET	9
#define IP_CHECKSUM_OFFSET	10
#define IP_SRC_ADDR_OFFSET	12
#define IP_DEST_ADDR_OFFSET	16

#define IP_PROTOCOL_ICMP 	1

typedef struct s_ip_header
{
	uint8_t version;
	uint8_t ihl;
	uint8_t tos;
	uint16_t total_len;
	uint16_t id;
	uint16_t fragment;
	uint8_t ttl;
	uint8_t protocol;
	uint16_t header_checksum;
	uint32_t src_addr;
	uint32_t  dest_addr;
}	t_ip_header;

int parse_ip_header(t_rx_packet* packet);
int parse_ip_err_payload(t_rx_packet* packet);

#endif
