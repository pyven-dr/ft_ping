#ifndef NETWORK_H
#define NETWORK_H

#include <stddef.h>
#include <stdint.h>
#include <netinet/in.h>

typedef struct s_client t_client;
typedef struct s_rx_packet t_rx_packet;
typedef struct s_ping_stats t_ping_stats;

uint32_t read_raw_32(const uint8_t* raw_packet, size_t offset);
uint16_t read_raw_16(const uint8_t* raw_packet, size_t offset);

int process_hosts(char** hosts, int nb_hosts, t_client* socket_fd);
int resolve_addr(char* name, struct sockaddr_in* addr_res);
int print_name(uint32_t addr);

#endif
