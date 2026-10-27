#ifndef PROCESS_H
#define PROCESS_H

#include <netinet/in.h>

typedef struct s_client t_client;

int process_loop(char** hosts, int nb_hosts, t_client* socket_fd);
int resolve_addr(char* name, struct sockaddr_in* addr_res);

#endif
