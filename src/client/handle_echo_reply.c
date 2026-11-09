#include <stdio.h>

#include "client.h"

void handle_echo_reply(t_rx_packet* packet)
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

