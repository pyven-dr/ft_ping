#ifndef OPT_H
#define OPT_H

#include <stdbool.h>

typedef struct s_ping_opt
{
	size_t count;
	size_t interval;
	size_t ttl;
	size_t timeout;
	size_t linger;
	bool verbose;
}	t_ping_opt;

#endif
