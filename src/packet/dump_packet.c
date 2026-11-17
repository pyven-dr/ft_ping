#include <stddef.h>
#include <stdio.h>

#include "client.h"
#include "utils.h"

static void hexdump(uint8_t* data, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		if (i % 2 == 0)
			printf(" ");
		printf("%02x", data[i]);
	}
	printf("\n");
}

static void print_ip_header(t_ip_header* ip_header)
{
	printf("Vr HL TOS  Len   ID Flg  off TTL Pro  cks      Src\tDst\tData\n");
	printf(" %x  %x", ip_header->version, ip_header->ihl);
	printf("  %02x", ip_header->tos);
	printf(" %04x", ip_header->total_len);
	printf(" %04x", ip_header->id);
	printf("   %x %04x", ip_header->fragment >> 13, ip_header->fragment & 0x1FFF);
	printf("  %02x", ip_header->ttl);
	printf("  %02x", ip_header->protocol);
	printf(" %04x ", ip_header->header_checksum);
	print_ip(ip_header->src_addr);
	printf("  ");
	print_ip(ip_header->dest_addr);
	printf("\n");
}

static void print_icmp_header(t_rx_packet* packet)
{
	size_t msg_size = packet->ip_header.total_len - packet->ip_header.ihl * 4;
	
	printf("ICMP: type %d, code %d,", packet->icmp_header.type, packet->icmp_header.code);
	printf(" size %zu,", msg_size);
	printf(" id 0x%04x,", packet->icmp_header.identifier);
	printf(" seq 0x%04x\n", packet->icmp_header.sequence);
}

void print_verbose(t_rx_packet* packet)
{
	printf("IP Hdr Dump:\n");
	hexdump(packet->raw_packet, 20);
	print_ip_header(&packet->ip_header);
	print_icmp_header(packet);
}
