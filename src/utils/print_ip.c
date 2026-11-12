#include <stdio.h>

void print_ip(size_t ip)
{
	printf("%lu.", (ip >> 24) & 0xFF);
	printf("%lu.", (ip >> 16) & 0xFF);
	printf("%lu.", (ip >> 8) & 0xFF);
	printf("%lu", ip & 0xFF);
}

