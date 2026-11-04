#include <sys/time.h>
#include <stddef.h>

double interval(struct timeval* start, struct timeval* end)
{
	double start_us = start->tv_sec * 1000000 + start->tv_usec;
	double end_us = end->tv_sec * 1000000 + end->tv_usec;

	return ((end_us - start_us) / 1000);
}
