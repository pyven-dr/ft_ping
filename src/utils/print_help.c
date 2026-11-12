#include <stdio.h>

struct s_option
{
	char	short_opt;
	char*	long_opt;
	char*	description;
};

void print_help(void)
{
	static const struct s_option opt_desc[] = {
		{'c', "count=NUMBER", "stop after sending NUMBER packets"},
		{'i', "interval=NUMBER", "wait NUMBER seconds between sending each packet"},
		{'\0', "ttl=N", "specify N as time-to-live"},
		{'v', "verbose", "verbose output"},
		{'w', "timeout=N", "stop after N seconds"},
		{'W', "linger=N", "number of seconds to wait for response"},
		{'s', "size=NUMBER", "send NUMBER data octets"},
		{'?', "help", "give this help list"}
	};

	printf("Usage: ft_ping [OPTION...] HOST ...\n");
	printf("Send ICMP ECHO_REQUEST packets to network hosts.\n\n");

	size_t nb_opt = sizeof(opt_desc) / sizeof(struct s_option);

	for (size_t i = 0; i < nb_opt; ++i)
	{
		if (opt_desc[i].short_opt != '\0')
			printf("  -%c, ", opt_desc[i].short_opt);
		else
			printf("      ");
		printf("--%-20s %s\n", opt_desc[i].long_opt, opt_desc[i].description);
	}
	printf("\nMandatory or optional arguments to long options are also mandatory or " \
			"optional\n for any corresponding short options.\n");
}
