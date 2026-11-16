#include <netinet/in.h>
#include <stdio.h>

#include "client.h"
#include "utils.h"

static void update_time_stats(t_ping_stats* stats, double time_interval)
{
	if (time_interval > stats->max)
		stats->max = time_interval;
	if (time_interval < stats->min)
		stats->min = time_interval;

	double delta = time_interval - stats->avg;

	stats->avg += (time_interval - stats->avg) / (stats->nb_rx + 1);

	stats->m2 += delta * (time_interval - stats->avg);
}

static int update_stats(t_ping_stats* stats, size_t seq)
{
	++stats->nb_response;

	if (bitmap_get(stats->pend_bitmap, seq) == 0)
	{
		++stats->nb_dup;
		return (1);
	}

	++stats->nb_rx;
	return (0);
}

void handle_echo_reply(t_rx_packet* packet, struct sockaddr_in* addr, t_ping_stats* stats)
{
	struct timeval cur_time = {0};
	gettimeofday(&cur_time, NULL);
	
	size_t msg_size = packet->packet_size - packet->ip_header.ihl * 4;

	if (packet->ip_header.src_addr != ntohl(addr->sin_addr.s_addr))
		return;

	printf("%zu bytes from ", msg_size);
	print_ip(packet->ip_header.src_addr);
	printf(": icmp_seq=%d ttl=%d", packet->icmp_header.sequence, packet->ip_header.ttl);

	if (msg_size - sizeof(t_icmp_header) >= sizeof(struct timeval))
	{
		double time_interval = interval(&packet->sent_time, &cur_time);
		printf(" time=%.3f ms", time_interval);
		update_time_stats(stats, time_interval);
	}
	if (update_stats(stats, packet->icmp_header.sequence) == 1)
		printf(" (DUP !)");
	bitmap_unset(stats->pend_bitmap, packet->icmp_header.sequence);
	printf("\n");
}

