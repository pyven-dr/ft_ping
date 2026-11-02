#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <errno.h>

#include "client.h"
#include "icmp.h"

int receive(struct sockaddr_in* addr, t_client* client, t_ping_stats* stats)
{
	(void)addr;
	(void)stats;
	char buffer[MAX_DATA_SIZE + sizeof(t_icmp_header)];
	struct sockaddr_in rx_addr = {0};
	socklen_t rx_len = 0;

	ssize_t rx_size = recvfrom(client->socket_fd, buffer, MAX_DATA_SIZE + sizeof(t_icmp_header),\
			MSG_DONTWAIT, (struct sockaddr*)&rx_addr, &rx_len);
	if (rx_size == -1)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
			return (0);
		perror("ft_ping");
		return (1);
	}

	printf("%d, %ld\n", rx_len, sizeof(struct sockaddr_in));
	if (rx_size != 0)
		printf("received\n");
	return (0);
}


