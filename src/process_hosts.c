#include "client.h"
#include "network.h"
#include <stdio.h>
int process_hosts(char** hosts, int nb_hosts, t_client* client)
{
	for (int i = 0; i < nb_hosts; ++i)
	{
		printf("host\n");
		struct sockaddr_in addr = {0};

		if (resolve_addr(hosts[i], &addr) == 1)
			return (1);

		if (ping_loop(client, &addr) == 1)
			return (1);
	}
	return (0);
}
