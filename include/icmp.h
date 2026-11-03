#ifndef ICMP_H
#define ICMP_H

#include <stdint.h>

typedef struct s_client t_client;
typedef  struct s_rx_packet t_rx_packet;

#define ICMP_ECHO		8
#define IMCP_ECHO_REPLY	0

#define ICMP_TYPE_OFFSET		0
#define ICMP_CODE_OFFSET		1
#define ICMP_CHECKSUM_OFFSET	2
#define ICMP_ID_OFFSET			4
#define ICMP_SEQ_OFFSET			6

typedef struct s_icmp_header
{
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	uint16_t identifier;
	uint16_t sequence;
}	t_icmp_header;

int parse_icmp_msg(t_rx_packet* packet, t_client* client);

#endif
