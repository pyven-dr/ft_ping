#ifndef UTILS_H
#define UTILS_H

#include <stddef.h>

struct timeval;

int init_signal(void);
void handler(int signal);

void print_ip(size_t ip);
void print_help(void);

double interval(struct timeval* start, struct timeval* end);

#endif
