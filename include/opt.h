#ifndef OPT_H
#define OPT_H

#include <stdbool.h>
#include <limits.h>
#include <stddef.h>

#define S_TO_MS 1000

#define DEFAULT_SIZE 56
#define DEFAULT_TTL 64
#define DEFAULT_INTERVAL 1000
#define DEFAULT_LINGER 10000

#define MAX_TTL 255
#define MAX_TIMEOUT INT_MAX
#define MAX_LINGER INT_MAX
#define MAX_DATA_SIZE 65399

typedef struct s_ping_opt
{
	size_t count;
	size_t interval;
	size_t ttl;
	size_t timeout;
	size_t linger;
	size_t size;
	bool verbose;
	bool numeric;
}	t_ping_opt;

#endif
