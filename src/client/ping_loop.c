#include <signal.h>

#include "client.h"
#include "utils.h"

extern sig_atomic_t signal_interrupt;

static int receive_last(t_client* client, t_ping_stats* stats, struct sockaddr_in* addr, \
		struct timeval* global_start)
{
	struct timeval start_time = {0};
	struct timeval cur_time = {0};

	gettimeofday(&start_time, NULL);
	gettimeofday(&cur_time, NULL);

	while (interval(&start_time, &cur_time) < (double)client->opt.linger)
	{
		if (receive(addr, client, stats) == 1)
			return (1);

		if (signal_interrupt == 1)
			return (0);
		if (stats->nb_response == client->opt.count)
			return (0);	
		if (interval(global_start, &cur_time) >= (double)client->opt.timeout && client->opt.timeout != 0)
			return (0);
		gettimeofday(&cur_time, NULL);
	}
	return (0);
}

int ping_loop(t_client* client, struct sockaddr_in* addr, t_ping_stats* stats)
{	
	struct timeval start = {0};
	gettimeofday(&start, NULL);

	if (send_ping(addr, client, stats) == 1)
		return (1);

	while (1)
	{
		if (receive(addr, client, stats) == 1)
			return (1);
	
		struct timeval cur_time = {0};
		gettimeofday(&cur_time, NULL);

		if (interval(&stats->last_sent, &cur_time) >= (double)client->opt.interval)
		{
			if (send_ping(addr, client, stats) == 1)
				return (1);
		}
	
		if (signal_interrupt == 1)
			return (0);
		if (interval(&start, &cur_time) >= (double)client->opt.timeout && client->opt.timeout != 0)
			return (0);
		if (stats->nb_tx >= client->opt.count && client->opt.count != 0)
			return (receive_last(client, stats, addr, &start));
	}
}
