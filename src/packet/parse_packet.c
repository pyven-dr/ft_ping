#include "ip.h"
#include "icmp.h"

int parse_packet(t_rx_packet* packet)
{
	if (parse_ip_header(packet) == 1)
		return (1);
	if (parse_icmp_msg(packet) == 1)
		return (1);
	return (0);
}

int parse_pakcet_err_payload(t_rx_packet* packet)
{
	if (parse_ip_err_payload(packet) == 1)
		return (1);
	if (parse_icmp_err_payload(packet) == 1)
		return (1);
	return (0);
}
