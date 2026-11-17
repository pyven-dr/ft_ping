#ifndef PACKET_H
#define PACKET_H

#include <stdint.h>

typedef struct s_rx_packet t_rx_packet;

int parse_packet(t_rx_packet* packet);
int parse_pakcet_err_payload(t_rx_packet* packet);
uint16_t compute_checksum(const void* data, int size);
void print_verbose(t_rx_packet* packet);

#endif
