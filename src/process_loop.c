#include <arpa/inet.h>
#include <sys/time.h>
#include <stddef.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "client.h"
#include "process.h"
#include "icmp.h"

int receive(struct sockaddr_in* addr, t_client* client)
{
	(void)addr;
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

size_t interval(struct timeval* start, struct timeval* end)
{
	size_t start_us = start->tv_sec * 1000000 + start->tv_usec;
	size_t end_us = end->tv_sec * 1000000 + end->tv_usec;

	return ((end_us - start_us) / 1000);
}

int process_loop(char** hosts, int nb_hosts, t_client* client)
{
	for (int i = 0; i < nb_hosts; ++i)
	{
		struct sockaddr_in addr = {0};
		t_ping_stats stats = {0};	

		if (resolve_addr(hosts[i], &addr) == 1)
			return (1);

		if (send_ping(&addr, client, stats.seq_number) == 1)
			return (1);
		gettimeofday(&stats.last_sent, NULL);

		while (1)
		{
			if (receive(&addr, client) == 1)
				return (1);
		
			struct timeval cur_time = {0};
			gettimeofday(&cur_time, NULL);

			if (interval(&stats.last_sent, &cur_time) >= client->opt.interval)
			{
				if (send_ping(&addr, client, stats.seq_number) == 1)
					return (1);
				gettimeofday(&stats.last_sent, NULL);
				++stats.seq_number;
			}

		}
	}
	return (0);
}
