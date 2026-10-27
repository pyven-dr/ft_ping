#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "opt.h"
#include "parsing.h"

static void invalid_opt(char **argv)
{
	if (optopt != 0)
		dprintf(2, "ft_ping: invalid option -- '%c'\n", optopt);
	else
		dprintf(2, "ft_ping: unrecognized option '%s'\n", argv[optind - 1]);
	dprintf(2, "Try 'ft_ping --help' for more information.\n");
}

static void missing_arg(char **argv)
{
	if (strncmp(argv[optind - 1], "--", 2) != 0)
		dprintf(2, "ft_ping: option requires an argument -- '%c'\n", optopt);
	else
		dprintf(2, "ft_ping: option '%s' requires an argument\n", argv[optind - 1]);
	dprintf(2, "Try 'ft_ping --help' for more information.\n");
}

static int parse_flag(int flag, t_ping_opt* opt)
{
	switch (flag)
	{
		case 'v':
		{
			opt->verbose = true;
			return (PARSE_OK);
		}
		case 'c':
			return (set_opt(&opt->count, optarg, 0, 0));
		case 'i':
			return (set_opt_double(&opt->interval, optarg, 0.2));
		case 'w':
			return (set_opt(&opt->timeout, optarg, 1, MAX_TIMEOUT));
		case 'W':
			return (set_opt(&opt->linger, optarg, 1, MAX_LINGER));
		case 't':
			return (set_opt(&opt->ttl, optarg, 1, MAX_TTL));
		case 's':
			return (set_opt(&opt->size, optarg, 0, MAX_DATA_SIZE));
		case OPT_HELP:
			return (PARSE_HELP);
		default:
			__builtin_unreachable();
	}
}

int handle_flags(int flag, char **argv, t_ping_opt* opt)
{
	if (flag == '?')
	{
		if (optopt == 0 && strncmp(argv[optind - 1], "--", 2) != 0)
		{
			printf("? opt\n");
			return (PARSE_HELP);
		}
			invalid_opt(argv);
			return (PARSE_ERROR);
	}
	if (flag == ':')
	{
		missing_arg(argv);
		return (PARSE_ERROR);
	}
	return (parse_flag(flag, opt));
}
