#include <netinet/in.h>
#include <stddef.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>

#include "client.h"
#include "icmp.h"

int send_ping(struct sockaddr_in *addr, t_client *client, t_ping_stats* stats)
{
	t_icmp_header* header = (t_icmp_header*)client->buffer;
	int message_size = client->opt.size + sizeof(t_icmp_header);

	gettimeofday(&stats->last_sent, NULL);
	if (client->opt.size >= 16)
		memcpy(client->buffer + sizeof(t_icmp_header), \
				&stats->last_sent, sizeof(struct timeval));

	printf("%zu\n", stats->last_sent.tv_sec);
	printf("%zu\n", stats->last_sent.tv_usec);

	header->type = ICMP_ECHO;
	header->code = 0;
	header->checksum = 0;
	header->identifier = htons(client->ping_id);
	header->sequence = htons(stats->seq_number);

	header->checksum = compute_checksum(client->buffer, message_size);

	if (sendto(client->socket_fd, client->buffer, message_size, 0, \
			(struct sockaddr*)addr, sizeof(struct sockaddr_in)) != message_size)
	{
		perror("ft_ping");
		return (1);
	}

	++stats->seq_number;
	++stats->nb_tx;
	return (0);
}
