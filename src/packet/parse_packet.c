#include "icmp.h"
#include "ip.h"

int parse_packet(char* raw_packet, t_icmp_header* icmp_header, struct sockaddr_in target_addr)
{
	t_ip_header header = {0};

}
