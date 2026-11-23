#include <stdio.h>
#include <arpa/inet.h>

#include "client.h"
#include "utils.h"
#include "packet.h"
#include "network.h"

static void print_error(uint16_t type)
{
	static const t_icmp_err_mess err_messages[] = {
		{ICMP_NET_UNREACH, "Destination Net Unreachable"},
		{ICMP_HOST_UNREACH, "Destination Host Unreachable"},
		{ICMP_PROTO_UNREACH, "Destination Protocol Unreachable"},
		{ICMP_PORT_UNREACH, "Destination Port Unreachable"},
		{ICMP_FRAG_NEEDED, "Fragmentation needed and DF set"},
		{ICMP_SRC_RT_FAILED, "Source Route Failed"},
		{ICMP_NET_UNKNOWN, "Network Unknown"},
		{ICMP_HOST_UNKNOWN, "Host Unknown"},
		{ICMP_HOST_ISOLATED, "Host Isolated"},
		{ICMP_NET_PROHIB, "Communication with Destination Network is Administratively Prohibited"},
		{ICMP_HOST_PROHIB, "Communication with Destination Host is Administratively Prohibited"},
		{ICMP_NET_UNREACH_TOS, "Destination Network Unreachable At This TOS"},
		{ICMP_HOST_UNREACH_TOS, "Destination Host Unreachable At This TOS"},
		{ICMP_COM_PROHIB, "Communication Administratively Prohibited"},
		{ICMP_PREC_VIOLATION, "Host Precedence Violation"},
		{ICMP_PREC_CUTOFF, "Precedence cutoff in effect"},

		{ICMP_NET_REDIR, "Redirect Network"},
		{ICMP_HOST_REDIR, "Redirect Host"},
		{ICMP_NET_TOS_REDIR, "Redirect Type of Service and Network"},
		{ICMP_HOST_TOS_REDIR, "Redirect Type of Service and Host"},

		{ICMP_TTL_EXC, "Time to live exceeded"},
		{ICMP_FRAG_EXC, "Frag reassembly time exceeded"}
	};

	size_t nb_types = sizeof(err_messages) / sizeof(t_icmp_err_mess);

	for (size_t i = 0; i < nb_types; ++i)
	{
		if (type == err_messages[i].type)
		{
			printf("%2s", err_messages[i].message);
			return;
		}
	}
	printf("Unknown icmp type");
}

static int print_source(uint32_t src_addr, bool numeric)
{
	if (numeric == false)
		return (print_name(src_addr) != 0);
	else
	{
		print_ip(src_addr);
		printf(": ");
	}
	return (0);
}

int handle_error(t_rx_packet* packet, struct sockaddr_in* addr, t_ping_stats* stats, t_ping_opt* opt)
{
	t_rx_packet original_packet = {0};
	size_t payload_offset = packet->ip_header.ihl * 4 + sizeof(t_icmp_header);
	size_t msg_size = packet->packet_size - packet->ip_header.ihl * 4;
	
	original_packet.raw_packet = packet->raw_packet + payload_offset;
	original_packet.packet_size = packet->packet_size - payload_offset;
	if (parse_pakcet_err_payload(&original_packet) == 1)
		return (0);
	if (original_packet.ip_header.dest_addr != ntohl(addr->sin_addr.s_addr))
		return (0);

	printf("%zu bytes from ", msg_size);
	if (print_source(packet->ip_header.src_addr, opt->numeric) == 1)
		return (1);
	print_error(ICMP_TYPE_ENCODE(packet->icmp_header.type, packet->icmp_header.code));
	printf("\n");

	if (opt->verbose == true)
		print_verbose(&original_packet);

	++stats->nb_response;
	return (0);
}
