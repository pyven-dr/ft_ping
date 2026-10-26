#include <arpa/inet.h>
#include <stdio.h>

#include "process.h"

int process_loop(char** hosts, int nb_hosts, int socket_fd)
{
	(void)socket_fd;
	printf("%d\n", nb_hosts);
	for (int i = 0; i < nb_hosts; ++i)
	{
		struct sockaddr_in addr = {0};

		if (resolve_addr(hosts[i], &addr) == 1)
			return (1);

		char addr_str[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &addr.sin_addr, addr_str, INET_ADDRSTRLEN);
		printf("valid addr %s\n", addr_str);
	}
	return (0);
}
