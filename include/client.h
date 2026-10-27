#ifndef CLIENT_H
#define CLIENT_H

#include "opt.h"

typedef struct s_client
{
	int socket_fd;

	unsigned char* buffer;

	t_ping_opt opt;
}	t_client;

int init_client(t_client* client);

#endif
