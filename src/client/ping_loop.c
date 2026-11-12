#include <signal.h>

#include "client.h"
#include "utils.h"

extern sig_atomic_t signal_interrupt;

int ping_loop(t_client* client, struct sockaddr_in* addr, t_ping_stats* stats)
{
	struct timeval end_time = {0};
	int finishing = 0;

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
		
		if (client->opt.count != 0 && stats->nb_tx >= client->opt.count)
		{
			if (finishing == 0)
			{
				gettimeofday(&end_time, NULL);
				finishing = 1;
			}
			if (interval(&end_time, &cur_time) >= (double)client->opt.linger)
				return (0);
		}

		if (interval(&stats->last_sent, &cur_time) >= (double)client->opt.interval && finishing == 0)
		{
			if (send_ping(addr, client, stats) == 1)
				return (1);
		}

		if (signal_interrupt == 1)
			return (0);
		if (interval(&start, &cur_time) >= (double)client->opt.timeout && client->opt.timeout != 0)
			return (0);
		if (stats->nb_response >= client->opt.count && client->opt.count != 0)
			return (0);
	}
}
