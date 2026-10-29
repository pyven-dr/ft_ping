#include <netinet/in.h>
#include <stddef.h>
#include <sys/time.h>
#include <stdio.h>

#include "client.h"
#include "icmp.h"


int send_ping(struct sockaddr_in *addr, t_client *client, int seq_number)
{
	t_icmp_header* header = (t_icmp_header*)client->buffer;
	int message_size = client->opt.size + sizeof(t_icmp_header);

	if (client->opt.size >= 16)
	{
		struct timeval* timestamp = (struct timeval*)(client->buffer + sizeof(t_icmp_header));
		gettimeofday(timestamp, NULL);
	}

	header->type = ICMP_ECHO;
	header->code = 0;
	header->checksum = 0;
	header->identifier = htons(client->ping_id);
	header->sequence = htons(seq_number);

	header->checksum = compute_checksum(client->buffer, message_size);

	if (sendto(client->socket_fd, client->buffer, message_size, 0, \
			(struct sockaddr*)addr, sizeof(struct sockaddr_in)) != message_size)
	{
		perror("ft_ping");
		return (1);
	}
	return (0);
}
