#ifndef ICMP_H
#define ICMP_H

#include <stdint.h>

typedef struct s_client t_client;
typedef  struct s_rx_packet t_rx_packet;

#define ICMP_TYPE_OFFSET		0
#define ICMP_CODE_OFFSET		1
#define ICMP_CHECKSUM_OFFSET	2
#define ICMP_ID_OFFSET			4
#define ICMP_SEQ_OFFSET			6
#define ICMP_DATA_OFFSET		8

#define ICMP_TYPE_ENCODE(type, code)	((uint16_t)(((type) << 8) | (code)))
#define ICMP_GET_TYPE(coded) 			((uint8_t)(coded >> 8))
#define ICMP_GET_CODE(coded)			((uint8_t)(coded & 0xFF))

typedef struct s_icmp_header
{
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	uint16_t identifier;
	uint16_t sequence;
}	t_icmp_header;

typedef enum e_icmp_types
{
	ICMP_ECHO_REPLY			= (0 << 8) | 0,

	ICMP_NET_UNREACH		= (3 << 8) | 0,
	ICMP_HOST_UNREACH		= (3 << 8) | 1,
	ICMP_PROTO_UNREACH		= (3 << 8) | 2,
	ICMP_PORT_UNREACH		= (3 << 8) | 3,
	ICMP_FRAG_NEEDED		= (3 << 8) | 4,
	ICMP_SRC_RT_FAILED		= (3 << 8) | 5,
	ICMP_NET_UNKNOWN		= (3 << 8) | 6,
	ICMP_HOST_UNKNOWN		= (3 << 8) | 7,
	ICMP_HOST_ISOLATED		= (3 << 8) | 8,
	ICMP_NET_PROHIB			= (3 << 8) | 9,
	ICMP_HOST_PROHIB		= (3 << 8) | 10,
	ICMP_NET_UNREACH_TOS	= (3 << 8) | 11,
	ICMP_HOST_UNREACH_TOS	= (3 << 8) | 12,
	ICMP_COM_PROHIB			= (3 << 8) | 13,
	ICMP_PREC_VIOLATION		= (3 << 8) | 14,
	ICMP_PREC_CUTOFF		= (3 << 8) | 15,

	ICMP_NET_REDIR			= (5 << 8) | 0,
	ICMP_HOST_REDIR			= (5 << 8) | 1,
	ICMP_NET_TOS_REDIR		= (5 << 8) | 2,
	ICMP_HOST_TOS_REDIR		= (5 << 8) | 3,

	ICMP_ECHO				= (8 << 8) | 0,

	ICMP_TTL_EXC			= (11 << 8) | 0,
	ICMP_FRAG_EXC			= (11 << 8) | 0
} t_icmp_types;

typedef struct s_icmp_err_mess
{
	t_icmp_types type;
	char* message;
}	t_icmp_err_mess;

int parse_icmp_msg(t_rx_packet* packet);
int parse_icmp_err_payload(t_rx_packet* packet);

#endif
