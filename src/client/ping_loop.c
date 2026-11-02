#include "client.h"

size_t interval(struct timeval* start, struct timeval* end)
{
	size_t start_us = start->tv_sec * 1000000 + start->tv_usec;
	size_t end_us = end->tv_sec * 1000000 + end->tv_usec;

	return ((end_us - start_us) / 1000);
}

int ping_loop(t_client* client, struct sockaddr_in* addr)
{	
	t_ping_stats stats = {0};

	if (send_ping(addr, client, stats.seq_number) == 1)
		return (1);
	gettimeofday(&stats.last_sent, NULL);

	while (1)
	{
		if (receive(addr, client, &stats) == 1)
			return (1);
	
		struct timeval cur_time = {0};
		gettimeofday(&cur_time, NULL);

		if (interval(&stats.last_sent, &cur_time) >= client->opt.interval)
		{
			if (send_ping(addr, client, stats.seq_number) == 1)
				return (1);
			gettimeofday(&stats.last_sent, NULL);
			++stats.seq_number;
		}
	}
}
