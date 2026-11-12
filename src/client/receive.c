#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>

#include "client.h"
#include "icmp.h"
#include "network.h"

static void handle_packet(uint8_t* buffer, size_t rx_size, struct sockaddr_in* addr, t_ping_stats* stats)
{
	t_rx_packet packet = {0};
	packet.raw_packet = buffer;
	packet.packet_size = rx_size;
	if (parse_packet(&packet) == 1)
		return;

	switch (packet.icmp_header.type)
	{
		case ICMP_ECHO_REPLY:
			handle_echo_reply(&packet, addr, stats);
			break;

		case ICMP_DEST_UNREACH:
		case ICMP_REDIRECT:
		case ICMP_TIME_EXC:
			handle_error(&packet, addr, stats);
			break;

		default:
			break;
	}
}

int receive(struct sockaddr_in* addr, t_client* client, t_ping_stats* stats)
{
	uint8_t buffer[MAX_DATA_SIZE + sizeof(t_icmp_header)];
	ssize_t rx_size = recvfrom(client->socket_fd, buffer, MAX_DATA_SIZE + sizeof(t_icmp_header),\
			0, NULL, NULL);
	if (rx_size == -1)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return (0);
		perror("ft_ping");
		return (1);
	}

	if (rx_size != 0)
		handle_packet(buffer, rx_size, addr, stats);
	return (0);
}


