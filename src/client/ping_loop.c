#include "client.h"

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
	}
}
