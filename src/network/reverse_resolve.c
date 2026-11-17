#include <netdb.h>
#include <stdio.h>

int print_name(uint32_t addr)
{
	struct sockaddr_in socket_addr = {0};
	char host[NI_MAXHOST] = {0};

	socket_addr.sin_family = AF_INET;
	socket_addr.sin_addr.s_addr = htonl(addr);
	
	int ret = getnameinfo((struct sockaddr*)&socket_addr, sizeof(socket_addr), \
				host, sizeof(host), NULL, 0, 0);
	if (ret != 0)
	{
		dprintf(2, "ft_ping: %s\n", gai_strerror(ret));
		return (1);
	}

	printf("%s", host);
	return (0);
}
