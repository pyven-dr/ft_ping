#ifndef ICMP_H
#define ICMP_H

#include <stdint.h>

typedef struct s_icmp_header
{
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	uint16_t identifier;
	uint16_t sequence;
}	t_icmp_header;

#endif
