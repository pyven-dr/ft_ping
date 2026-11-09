#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>
#include <stdint.h>

#include "client.h"
#include "icmp.h"
#include "network.h"


int receive(struct sockaddr_in* addr, t_client* client, t_ping_stats* stats)
{
	(void)stats;
	(void)addr;
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
	{
		t_rx_packet packet = {0};
		packet.raw_packet = buffer;
		packet.packet_size = rx_size;
		if (parse_packet(&packet) == 1)
			return (1);

		uint16_t icmp_mes_type = ICMP_TYPE_ENCODE(packet.icmp_header.type, packet.icmp_header.code);
		
		if (icmp_mes_type == ICMP_ECHO_REPLY)
			handle_echo_reply(&packet);
		else if (icmp_mes_type != ICMP_ECHO)
			handle_error(&packet, client);
	}
	return (0);
}


