#ifndef OPT_H
#define OPT_H

#include <stdbool.h>
#include <limits.h>

#define DEFAULT_SIZE 65
#define DEFAULT_TTL 255
#define DEFAULT_INTERVAL 1

#define MAX_TTL 255
#define MAX_TIMEOUT INT_MAX
#define MAX_LINGER INT_MAX
#define MAX_DATA_SIZE 65399

typedef struct s_ping_opt
{
	size_t count;
	double interval;
	size_t ttl;
	size_t timeout;
	size_t linger;
	size_t size;
	bool verbose;
}	t_ping_opt;

#endif
