#ifndef PROCESS_H
#define PROCESS_H

#include <netinet/in.h>

int process_loop(char** hosts, int nb_hosts, int socket_fd);
int resolve_domain(char* name, struct sockaddr_in* addr_res);

#endif
