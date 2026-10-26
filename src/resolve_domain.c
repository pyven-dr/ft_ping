#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>

int resolve_domain(char* name, struct sockaddr_in* addr_res)
{
	(void)addr_res;
	struct addrinfo hints = {0};
	struct addrinfo *res = {0};
	
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;
	hints.ai_protocol = IPPROTO_ICMP;

	if (getaddrinfo(name, NULL, &hints, &res) != 0)
	{
		printf("err\n");
		return (1);
	}

	for (struct addrinfo *cur = res; cur != NULL; cur = cur->ai_next) 
	{
		struct sockaddr_in addr = *(struct sockaddr_in*)cur->ai_addr;

		char addr_str[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &addr.sin_addr, addr_str, INET_ADDRSTRLEN);
		printf("valid addr %s\n", addr_str);
	}
	freeaddrinfo(res);
	return (0);
}
