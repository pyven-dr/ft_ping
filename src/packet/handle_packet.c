#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>
#include <netinet/in.h>
#include <stdint.h>

#include "client.h"
#include "icmp.h"

/*static int check_src(t_rx_packet* packet, struct sockaddr_in* target_addr)
{
	uint32_t target = ntohl(target_addr->sin_addr.s_addr);
	if (packet->ip_header.src_addr != target)
		return (1);
	return (0);
}*/

static void print_ip(size_t ip)
{
	printf("%lu.", (ip >> 24) & 0xFF);
	printf("%lu.", (ip >> 16) & 0xFF);
	printf("%lu.", (ip >> 8) & 0xFF);
	printf("%lu", ip & 0xFF);
}

static void print_echo(t_rx_packet* packet)
{
	struct timeval curr_time = {0};
	gettimeofday(&curr_time, NULL);
	
	size_t msg_size = packet->packet_size - packet->ip_header.ihl * 4;
	
	printf("%zu bytes from ", msg_size);
	print_ip(packet->ip_header.src_addr);
	printf(": icmp_seq=%d ttl=%d", packet->icmp_header.sequence, packet->ip_header.ttl);

	if (msg_size - sizeof(t_icmp_header) >= sizeof(struct timeval))
	{
		double time_interval = interval(&packet->sent_time, &curr_time);
		printf(" time=%.3f ms", time_interval);
	}
	printf("\n");
}

int handle_packet(t_rx_packet* packet, t_client* client, t_ping_stats* stats, struct sockaddr_in* target)
{
	(void)client;
	(void)stats;
	(void)target;
	if (packet->icmp_header.type == ICMP_ECHO_REPLY)
	{
		//if (check_src(packet, target) == 1)
		//	return (1);
		print_echo(packet);
	}
	else if (packet->icmp_header.type != ICMP_ECHO)
	{
		printf("%d\n", packet->icmp_header.identifier);
		printf("Err %d\n", packet->icmp_header.type);
	}
	return (0);
}
