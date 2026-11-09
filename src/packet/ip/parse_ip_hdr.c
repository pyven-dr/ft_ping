#include <stdint.h>
#include <arpa/inet.h>

#include "client.h"
#include "ip.h"
#include "network.h"

static int parse_ip_fields(t_rx_packet* packet)
{
	t_ip_header* ip_header = &packet->ip_header;
	uint8_t* raw_packet = packet->raw_packet;

	if (packet->packet_size < 20)
		return (1);

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

int parse_ip_header(t_rx_packet* packet)
{
	if (parse_ip_fields(packet) == 1)
		return (1);

	if (packet->ip_header.version != 4)
		return (1);
	if (packet->ip_header.total_len > packet->packet_size)
		return (1);
	if (packet->ip_header.ihl * 4 > packet->packet_size)
		return (1);
	if (compute_checksum(packet->raw_packet, packet->ip_header.ihl * 4) != 0)
		return (1);
	return (0);
}

int parse_ip_err_payload(t_rx_packet* packet)
{
	if (parse_ip_fields(packet) == 1)
		return (1);

	if (packet->ip_header.version != 4)
		return (1);
	if (packet->ip_header.ihl * 4 > packet->packet_size)
		return (1);
	if (compute_checksum(packet->raw_packet, packet->ip_header.ihl * 4) != 0)
		return (1);
	return (0);
}
