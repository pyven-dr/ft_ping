#include <netinet/in.h>
#include <arpa/inet.h>

#include "client.h"
#include "ip.h"
#include "icmp.h"

/*static void print_ip_header(t_ip_header* header)
{
	char ip[INET_ADDRSTRLEN];

	printf("                            IP Header                            \n");
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf("|ver: %2u|IHL: %2u|TOS: %10u|Total len: %20u|\n",header->version, \
			header->ihl, header->tos, header->total_len);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf("|ID: %27u|Fragment: %21u|\n", header->id, header->fragment);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf("|TTL: %10u|Protocol: %5u|Checksum: %21u|\n", header->ttl, \
			header->protocol, header->header_checksum);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	inet_ntop(AF_INET, &header->src_addr, ip, sizeof(ip));
	printf("|Src Addr: %53s|\n", ip);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	inet_ntop(AF_INET, &header->dest_addr, ip, sizeof(ip));
	printf("|Dest Addr: %52s|\n", ip);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
}*/

/*static void print_icmp_header(t_icmp_header* header)
{
	printf("                           ICMP Header                           \n");
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf("|Type: %9u|Code: %9u|Checksum: %21u|\n", header->type, header->code, header->checksum);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
	printf("|ID: %27u|Sequence: %21u|\n", header->identifier, header->sequence);
	printf("+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+\n");
}*/

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
