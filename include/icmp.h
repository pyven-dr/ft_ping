#ifndef ICMP_H
#define ICMP_H

#include <stdint.h>

typedef struct s_client t_client;
typedef struct s_rx_packet t_rx_packet;

#define ICMP_TYPE_OFFSET		0
#define ICMP_CODE_OFFSET		1
#define ICMP_CHECKSUM_OFFSET	2
#define ICMP_ID_OFFSET			4
#define ICMP_SEQ_OFFSET			6
#define ICMP_DATA_OFFSET		8

#define ICMP_TYPE_ENCODE(type, code)	((uint16_t)(((type) << 8) | (code)))

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
	ICMP_ECHO_REPLY			= 0,
	ICMP_DEST_UNREACH		= 3,
	ICMP_REDIRECT			= 5,
	ICMP_ECHO				= 8,
	ICMP_TIME_EXC			= 11
}	t_icmp_types;

typedef enum e_icmp_unreach_codes
{
	ICMP_NET_UNREACH		= (ICMP_DEST_UNREACH << 8) | 0,
	ICMP_HOST_UNREACH		= (ICMP_DEST_UNREACH << 8) | 1,
	ICMP_PROTO_UNREACH		= (ICMP_DEST_UNREACH << 8) | 2,
	ICMP_PORT_UNREACH		= (ICMP_DEST_UNREACH << 8) | 3,
	ICMP_FRAG_NEEDED		= (ICMP_DEST_UNREACH << 8) | 4,
	ICMP_SRC_RT_FAILED		= (ICMP_DEST_UNREACH << 8) | 5,
	ICMP_NET_UNKNOWN		= (ICMP_DEST_UNREACH << 8) | 6,
	ICMP_HOST_UNKNOWN		= (ICMP_DEST_UNREACH << 8) | 7,
	ICMP_HOST_ISOLATED		= (ICMP_DEST_UNREACH << 8) | 8,
	ICMP_NET_PROHIB			= (ICMP_DEST_UNREACH << 8) | 9,
	ICMP_HOST_PROHIB		= (ICMP_DEST_UNREACH << 8) | 10,
	ICMP_NET_UNREACH_TOS	= (ICMP_DEST_UNREACH << 8) | 11,
	ICMP_HOST_UNREACH_TOS	= (ICMP_DEST_UNREACH << 8) | 12,
	ICMP_COM_PROHIB			= (ICMP_DEST_UNREACH << 8) | 13,
	ICMP_PREC_VIOLATION		= (ICMP_DEST_UNREACH << 8) | 14,
	ICMP_PREC_CUTOFF		= (ICMP_DEST_UNREACH << 8) | 15
}	t_icmp_unreach_codes;

typedef enum e_icmp_redir_codes
{
	ICMP_NET_REDIR			= (ICMP_REDIRECT << 8) | 0,
	ICMP_HOST_REDIR			= (ICMP_REDIRECT << 8) | 1,
	ICMP_NET_TOS_REDIR		= (ICMP_REDIRECT << 8) | 2,
	ICMP_HOST_TOS_REDIR		= (ICMP_REDIRECT << 8) | 3,
}	t_icmp_redir_codes;

typedef enum e_time_exc_codes
{
	ICMP_TTL_EXC			= (ICMP_TIME_EXC << 8) | 0,
	ICMP_FRAG_EXC			= (ICMP_TIME_EXC << 8) | 1
}	t_time_exc_codes;

typedef struct s_icmp_err_mess
{
	uint16_t	type;
	char*		message;
}	t_icmp_err_mess;

int parse_icmp_msg(t_rx_packet* packet);
int parse_icmp_err_payload(t_rx_packet* packet);

#endif
