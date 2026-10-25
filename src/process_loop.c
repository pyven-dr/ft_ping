#include <arpa/inet.h>
#include <stdio.h>

int process_loop(char** hosts, int nb_hosts, int socket_fd)
{
	(void)socket_fd;
	printf("%d\n", nb_hosts);
	for (int i = 0; i < nb_hosts; ++i)
	{
		struct sockaddr_in addr = {0};

		addr.sin_family = AF_INET;
		if (inet_aton(hosts[i], &addr.sin_addr) == 0)
		{
			dprintf(2, "ft_ping: unknown host\n");
			return (1);
		}

		char addr_str[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &addr.sin_addr, addr_str, INET_ADDRSTRLEN);
		printf("valid addr %s\n", addr_str);
	}
	return (0);
}
