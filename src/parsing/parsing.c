#include <getopt.h>
#include <stdio.h>
#include <unistd.h>

#include "parsing.h"

int parsing_args(int argc, char** argv, t_ping_opt* opt)
{
	static struct option long_options[] =
	{
		{"help", no_argument, NULL, OPT_HELP},
		{"verbose", no_argument, NULL, 'v'},
		{"count", required_argument, NULL, 'c'},
		{"interval", required_argument, NULL, 'i'},
		{"ttl", required_argument, NULL, 't'},
		{"timeout", required_argument, NULL, 'w'},
		{"linger", required_argument, NULL, 'W'},
		{0, 0, 0, 0}
	};

	opterr = 0;
	int flag = getopt_long(argc, argv, ":?vc:i:w:W:", long_options, NULL);

	while (flag != -1)
	{
		int ret = handle_flags(flag, argv, opt);
		if (ret != 0)
			return (ret);
		
		flag = getopt_long(argc, argv, ":?vc:i:w:W:", long_options, NULL);
	}
	
	if (optind == argc)
	{
		dprintf(2, "ft_ping: missing host operand\n");
		dprintf(2, "Try 'ft_ping --help' or 'ping --usage' for more information.\n");
		return (PARSE_ERROR);
	}
	return (PARSE_OK);
}
