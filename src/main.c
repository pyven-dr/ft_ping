#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <getopt.h>

#include "parsing.h"
#include "process.h"

int main(int argc, char** argv)
{
	write(1, "ft_ping\n", 8);

	int ret = parsing_args(argc, argv);

	if (ret == PARSE_HELP)
		return (0);
	else if (ret ==	PARSE_ERROR)
		return (64);

	int fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd == -1)
		return (1);

	return (process_loop(argv + optind, argc - optind, fd));

/*	int fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (fd == -1)
		return (1);

	t_icmp_header header = {0};
	header.type = 8;
	header.identifier = htons(1);
	header.sequence = htons(1);

	header.checksum = compute_checksum(&header, sizeof(header));

	struct sockaddr_in addr = {0};
	inet_pton(AF_INET, "8.8.8.8", &addr.sin_addr);
	addr.sin_family = AF_INET;

	sendto(fd, &header, sizeof(header), 0, (struct sockaddr*)&addr, sizeof(addr));

	uint8_t buffer[2048];
	socklen_t len = sizeof(addr);

	recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&addr, &len);

	struct iphdr *packet = (struct iphdr *)buffer;
	int packet_len = packet->ihl * 4;

	t_icmp_header *icmp_recv = (t_icmp_header *)(buffer + packet_len);


	printf("type: %d ident: %d sed: %d\n", icmp_recv->type, ntohs(icmp_recv->identifier), ntohs(icmp_recv->sequence));*/
	return (0);
}
