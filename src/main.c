#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>

#include "parsing.h"
#include "network.h"
#include "client.h"

int main(int argc, char** argv)
{
	int ret;
	t_client client = {0};

	ret = parsing_args(argc, argv, &client.opt);
	if (ret == PARSE_HELP)
	{
		print_help();
		return (0);
	}
	if (ret ==	PARSE_ERROR)
		return (64);

	if (init_client(&client) == 1)
	{
		perror("ft_ping");
		return (1);
	}

	ret = process_hosts(argv + optind, argc - optind, &client);
	free(client.buffer);
	close(client.socket_fd);
	return (ret);

	return (0);
}
