#include "client.h"

static int receive_last(t_client* client, t_ping_stats* stats, struct sockaddr_in* addr)
{
	struct timeval start_time = {0};
	struct timeval curr_time = {0};

	gettimeofday(&start_time, NULL);
	gettimeofday(&curr_time, NULL);

	while (interval(&start_time, &curr_time) < (double)client->opt.linger)
	{
		if (receive(addr, client, stats) == 1)
			return (1);
		if (stats->nb_rx == client->opt.count)
			return (0);
		gettimeofday(&curr_time, NULL);
	}
	return (0);
}

int ping_loop(t_client* client, struct sockaddr_in* addr)
{	
	t_ping_stats stats = {0};

	if (send_ping(addr, client, &stats) == 1)
		return (1);

	while (1)
	{
		if (receive(addr, client, &stats) == 1)
			return (1);
	
		struct timeval cur_time = {0};
		gettimeofday(&cur_time, NULL);

		if (interval(&stats.last_sent, &cur_time) >= (double)client->opt.interval)
		{
			if (send_ping(addr, client, &stats) == 1)
				return (1);
		}
		if (stats.nb_tx >= client->opt.count && client->opt.count != 0)
			return (receive_last(client, &stats, addr));
	}
}
