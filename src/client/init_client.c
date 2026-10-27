#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>

#include "client.h"
#include "icmp.h"


#include <stdio.h>
static void write_pattern(unsigned char* buffer, int size)
{
	unsigned char val = 0;

	for (int i = 0; i < size; ++i)
	{
		buffer[i] = val % (0xFF + 1);
		++val;
	}
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

	return (0);
}

