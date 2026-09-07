#include <getopt.h>
#include <stdio.h>
#include <unistd.h>

#include "parsing.h"

int parsing_args(int argc, char** argv)
{
	static struct option long_options[] =
	{
		{"help", no_argument, NULL, OPT_HELP},
		{"verbose", no_argument, NULL, 'v'},
		{0, 0, 0, 0}
	};

	opterr = 0;
	int flag = getopt_long(argc, argv, "?v", long_options, NULL);
	while (flag != -1)
	{
		int ret = handle_flags(flag, argv);
		if (ret != 0)
			return (ret);
		
		flag = getopt_long(argc, argv, "?v", long_options, NULL);
	}

	for (int i = optind; i < argc; ++i)
		printf("arg %s\n", argv[i]);
	return (PARSE_OK);
}

