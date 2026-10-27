#include <arpa/inet.h>
#include <stdio.h>
#include <sys/time.h>
#include <string.h>

#include "client.h"
#include "process.h"
#include "icmp.h"

int process_loop(char** hosts, int nb_hosts, t_client* client)
{
	(void)client;
	int data_size = 64 + sizeof(t_icmp_header);

	for (int i = 0; i < nb_hosts; ++i)
	{
		struct sockaddr_in addr = {0};

		if (resolve_addr(hosts[i], &addr) == 1)
			return (1);
		
		t_icmp_header* header = (t_icmp_header*)client->buffer;
	

		if (client->opt.size >= 16)
		{
			struct timeval* timestamp = (struct timeval*)(client->buffer + sizeof(t_icmp_header));
			gettimeofday(timestamp, NULL);
		}

		header->type = ICMP_ECHO;
		header->code = 0;
		header->checksum = 0;
		header->identifier = htons(1234);
		header->sequence = htons(1);

		header->checksum = compute_checksum(client->buffer, client->opt.size + sizeof(t_icmp_header));

		sendto(client->socket_fd, client->buffer, client->opt.size + sizeof(t_icmp_header), 0, (struct sockaddr*)&addr, sizeof(addr));

		char addr_str[INET_ADDRSTRLEN];
		inet_ntop(AF_INET, &addr.sin_addr, addr_str, INET_ADDRSTRLEN);
		printf("valid addr %s\n", addr_str);

		for (int i = 0; i < data_size; ++i)
			printf("%02X ", client->buffer[i]);
		printf("\n");
	}
	return (0);
}
