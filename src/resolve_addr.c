#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

int resolve_addr(const char* name, struct sockaddr_in* addr_res)
{
	struct addrinfo hints = {0};
	struct addrinfo *res = NULL;
	
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;

	if (getaddrinfo(name, NULL, &hints, &res) != 0 || res == NULL)
	{
		printf("err\n");
		return (1);
	}

	memcpy(addr_res, res->ai_addr, sizeof(struct sockaddr_in));
	freeaddrinfo(res);
	return (0);
}
