#include <sys/time.h>
#include <stddef.h>

double interval(struct timeval* start, struct timeval* end)
{
	double start_us = (double)start->tv_sec * 1000000.0 + (double)start->tv_usec;
	double end_us = (double)end->tv_sec * 1000000.0 + (double)end->tv_usec;

	return ((end_us - start_us) / 1000.0);
}
