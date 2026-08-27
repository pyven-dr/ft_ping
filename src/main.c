#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include "icmp.h"

uint16_t compute_checksum(void* data, int size)
{
	long sum = 0;
	uint16_t* ptr = data;

	while (size > 1)
	{
		sum += *ptr;
		size -= 2;
		++ptr;
	}

	if (size > 0)
		sum += *(uint8_t*)ptr;

	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);

	return (~sum);
}

int main(void)
{
	write(1, "ft_ping\n", 8);

	int fd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
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


	printf("type: %d ident: %d sed: %d\n", icmp_recv->type, ntohs(icmp_recv->identifier), ntohs(icmp_recv->sequence));
	return (0);
}
