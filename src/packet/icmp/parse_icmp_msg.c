#include <string.h>

#include <stdio.h>

#include "client.h"
#include "ip.h"
#include "icmp.h"
#include "network.h"

int parse_icmp_msg(t_rx_packet* packet, t_client* client)
{
	size_t message_size = client->opt.size + sizeof(t_icmp_header);
	uint8_t* raw_icmp;

	if (packet->packet_size - (packet->ip_header.ihl * 4) < message_size)
		return (1);
	if(packet->ip_header.protocol != IP_PROTOCOL_ICMP)
		return (1);

	raw_icmp = packet->raw_packet + (packet->ip_header.ihl * 4);
	packet->icmp_header.type = raw_icmp[ICMP_TYPE_OFFSET];
	packet->icmp_header.code = raw_icmp[ICMP_CODE_OFFSET];
	packet->icmp_header.checksum = read_raw_16(raw_icmp, ICMP_CHECKSUM_OFFSET);
	packet->icmp_header.identifier = read_raw_16(raw_icmp, ICMP_ID_OFFSET);
	packet->icmp_header.sequence = read_raw_16(raw_icmp, ICMP_SEQ_OFFSET);

	if (message_size >= 16)
	{
		memcpy(&packet->sent_time, raw_icmp + ICMP_DATA_OFFSET, sizeof(struct timeval));
	}
	if (compute_checksum(raw_icmp, message_size) != 0)
		return (1);
	return (0);
}
