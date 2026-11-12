#include <arpa/inet.h>
#include <stdio.h>
#include <math.h>

#include "client.h"
#include "network.h"

static void print_prologue(char* host, struct sockaddr_in* addr, t_client* client)
{
	char addr_str[INET_ADDRSTRLEN] = {0};
	inet_ntop(AF_INET, &addr->sin_addr, addr_str, INET_ADDRSTRLEN);

	printf("PING %s (%s): %zu data bytes", host, addr_str, client->opt.size);
	if (client->opt.verbose == true)
		printf(", id %#06x = %d", client->ping_id, client->ping_id);
	printf("\n");
}

static void print_epilogue(char* host, t_ping_stats* stats)
{
	size_t loss = (stats->nb_tx - stats->nb_rx) * 100 / stats->nb_tx;
	double stddev = sqrtl(stats->m2 / stats->nb_rx);

	printf("--- %s ping statistics ---\n", host);
	printf("%zu packets transmitted, %zu packets received, %zu%% packet loss\n", \
			stats->nb_tx, stats->nb_rx, loss);
	printf("round-trip min/avg/max/stddev = %.3f/%.3f/%.3f/%.3f ms\n", \
			stats->min, stats->avg, stats->max, stddev);
}

int process_hosts(char** hosts, int nb_hosts, t_client* client)
{
	for (int i = 0; i < nb_hosts; ++i)
	{
		t_ping_stats stats = {.min = INFINITY};
		struct sockaddr_in addr = {0};

		if (resolve_addr(hosts[i], &addr) == 1)
			return (1);

		print_prologue(hosts[i], &addr, client);
		if (ping_loop(client, &addr, &stats) == 1)
			return (1);
		print_epilogue(hosts[i], &stats);
	}
	return (0);
}
