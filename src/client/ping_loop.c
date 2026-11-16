#include <signal.h>

#include "client.h"
#include "utils.h"

extern sig_atomic_t signal_interrupt;

static int should_end(struct timeval* cur_time, t_client* client, t_ping_stats* stats)
{
	if (signal_interrupt == 1)
		return (1);
	if (client->opt.timeout != 0 && interval(&client->start, cur_time) >= (double)client->opt.timeout)
		return (1);
	if (stats->nb_response >= client->opt.count && client->opt.count != 0)
		return (1);
	return (0);
}

int ping_loop(t_client* client, struct sockaddr_in* addr, t_ping_stats* stats)
{
	struct timeval cur_time = {0};
	struct timeval end_time = {0};
	int finishing = 0;

	if (send_ping(addr, client, stats) == 1)
		return (1);
	while (1)
	{
		if (receive(addr, client, stats) == 1)
			return (1);
	
		gettimeofday(&cur_time, NULL);
		if (finishing == 1 && interval(&end_time, &cur_time) >= (double)client->opt.linger)
				return (0);
		
		if (finishing == 0 && interval(&stats->last_sent, &cur_time) >= (double)client->opt.interval)
		{
			if (client->opt.count != 0 && stats->nb_tx >= client->opt.count)
			{
				gettimeofday(&end_time, NULL);
				finishing = 1;
			}
			else if (send_ping(addr, client, stats) == 1)
				return (1);
		}

		if (should_end(&cur_time, client, stats) == 1)
			return (0);
	}
}
