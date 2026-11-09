#ifndef CLIENT_H
#define CLIENT_H

#include <sys/time.h>
#include <stddef.h>
#include <stdint.h>

#include "opt.h"
#include "ip.h"
#include "icmp.h"

struct sockaddr_in;

typedef struct s_client
{
	int socket_fd;

	unsigned char* buffer;

	int ping_id;

	t_ping_opt opt;
}	t_client;

typedef struct s_ping_stats
{
	struct timeval last_sent;
	size_t seq_number;


	size_t nb_tx;
	size_t nb_rx;

	size_t min;
	size_t max;
	size_t avg;
	size_t m2;

}	t_ping_stats;

typedef struct s_rx_packet
{
	t_ip_header ip_header;
	t_icmp_header icmp_header;
	
	struct timeval sent_time;

	uint8_t* raw_packet;
	size_t packet_size;
}	t_rx_packet;

int init_client(t_client* client);

int send_ping(struct sockaddr_in *addr, t_client *client, t_ping_stats* stats);
int receive(struct sockaddr_in* addr, t_client* client, t_ping_stats* stats);
int ping_loop(t_client* client, struct sockaddr_in* addr);

double interval(struct timeval* start, struct timeval* end);
void print_ip(size_t ip);

void handle_echo_reply(t_rx_packet* packet);
int handle_error(t_rx_packet* packet, t_client* client);

#endif
