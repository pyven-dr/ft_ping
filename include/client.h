#ifndef CLIENT_H
#define CLIENT_H

#include <sys/time.h>
#include <stddef.h>
#include <stdint.h>
#include "opt.h"

struct sockaddr_in;

typedef struct s_client
{
	int socket_fd;

	unsigned char* buffer;

	int ping_id;

	t_ping_opt opt;
}	t_client;

typedef struct s_ping_stats
{
	struct timeval last_sent;
	size_t seq_number;


	size_t nb_tx;
	size_t nb_rx;

	size_t min;
	size_t max;
	size_t avg;
	size_t m2;

}	t_ping_stats;

int init_client(t_client* client);
int send_ping(struct sockaddr_in *addr, t_client *client, int seq_number);

#endif
