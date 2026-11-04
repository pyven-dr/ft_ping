#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>

#include "client.h"
#include "icmp.h"
#include "network.h"

static int handle_packet(t_rx_packet* packet, t_client* client, t_ping_stats* stats)
{
	(void)client;
	(void)stats;
	if (packet->icmp_header.type == ICMP_ECHO_REPLY)
	{
		size_t msg_size = packet->packet_size - packet->ip_header.ihl * 4;
		struct timeval curr_time = {0};
		gettimeofday(&curr_time, NULL);
		/*printf("%x\n", (unsigned int)packet->sent_time.tv_sec);
		printf("%x\n", (unsigned int)packet->sent_time.tv_usec);

		printf("%x\n", (unsigned int)curr_time.tv_sec);
		printf("%x\n", (unsigned int)curr_time.tv_usec);*/

		double time_interval = interval(&packet->sent_time, &curr_time);
		printf("%zu bytes from %s: icmp_seq=%d ttl=%d time=%.3f ms\n", msg_size, "0.0.0.0", packet->icmp_header.sequence, packet->ip_header.ttl, time_interval);
	}
	return (0);
}

int receive(struct sockaddr_in* addr, t_client* client, t_ping_stats* stats)
{
	(void)stats;
	uint8_t buffer[MAX_DATA_SIZE + sizeof(t_icmp_header)];

	ssize_t rx_size = recvfrom(client->socket_fd, buffer, MAX_DATA_SIZE + sizeof(t_icmp_header),\
			MSG_DONTWAIT, NULL, NULL);
	if (rx_size == -1)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return (0);
		perror("ft_ping");
		return (1);
	}

	if (rx_size != 0)
	{
		printf("received\n");
		t_rx_packet packet = {0};
		packet.raw_packet = buffer;
		packet.packet_size = rx_size;
		parse_packet(&packet, client, addr);
		handle_packet(&packet, client, stats);
	}
	return (0);
}


