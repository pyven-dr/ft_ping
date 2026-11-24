#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#include "client.h"
#include "icmp.h"

static void write_pattern(unsigned char* buffer, int size)
{
	unsigned char val = 0;

	for (int i = 0; i < size; ++i)
	{
		buffer[i] = val % (0xFF + 1);
		++val;
	}
}

static void set_opt(t_client* client)
{
	int broadcast_flag = 1;
	struct timeval timeout = {0};
	timeout.tv_sec = 0;
	timeout.tv_usec = 100000;

	setsockopt(client->socket_fd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(struct timeval));
	setsockopt(client->socket_fd, SOL_IP, IP_TTL, &client->opt.ttl, sizeof(size_t));
	setsockopt(client->socket_fd, SOL_SOCKET, SO_BROADCAST, &broadcast_flag, sizeof(int));
}

int init_client(t_client* client)
{
	client->socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (client->socket_fd == -1)
		return (1);

	client->buffer = malloc(client->opt.size + sizeof(t_icmp_header));
	if (client->buffer == NULL)
	{
		close(client->socket_fd);
		return (1);
	}

	if (client->opt.size < 16)
		write_pattern(client->buffer + sizeof(t_icmp_header), client->opt.size);
	else
		write_pattern(client->buffer + sizeof(t_icmp_header) + 16, client->opt.size - 16);

	client->ping_id = getpid();

	set_opt(client);
	return (0);
}

