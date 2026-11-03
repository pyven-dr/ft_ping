#include <netinet/in.h>
#include <stdio.h>

#include "client.h"
#include "ip.h"
#include "icmp.h"

static int check_src(t_rx_packet* packet, struct sockaddr_in* target_addr)
{
	uint32_t target = ntohl(target_addr->sin_addr.s_addr);
	if (packet->ip_header.src_addr != target)
		return (1);
	return (0);
}

static void print_ip_header(t_ip_header* header)
{
	printf("                            IP Header                            \n");
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf("|%7u|%7u|%15u|%31u|\n",header->version, header->ihl, header->tos, header->total_len);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf("|%31u|%31u|\n", header->id, header->fragment);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf("|%15u|%15u|%31u|\n", header->ttl, header->protocol, header->header_checksum);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf("|%63u|\n", header->src_addr);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf("|%63u|\n", header->dest_addr);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
}

static void print_icmp_header(t_icmp_header* header)
{
	printf("                           ICMP Header                           \n");
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf("|%15u|%15u|%31u|\n", header->type, header->code, header->checksum);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf("|%31u|%31u|\n", header->identifier, header->sequence);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
}

int parse_packet(t_rx_packet* packet, t_client* client, struct sockaddr_in* target_addr)
{
	if (parse_ip_header(packet) == 1)
		return (1);
	if (check_src(packet, target_addr) == 1)
		return (1);
	if (parse_icmp_msg(packet, client) == 1)
		return (1);

	print_ip_header(&packet->ip_header);
	printf("\n");
	print_icmp_header(&packet->icmp_header);
	return (0);
}
