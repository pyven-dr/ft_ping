#include <stdio.h>
#include <stdlib.h>

#include "parsing.h"

int set_opt(size_t* opt, char* arg, unsigned long min, unsigned long max)
{
	char* end;
	unsigned long val = strtoul(arg, &end, 0);

	if (val < min)
	{
		dprintf(2, "ft_ping: option value too small: %s\n", arg);
		return (PARSE_ERROR);
	}
	if (val > max)
	{
		dprintf(2, "ft_ping: option value too big: %s\n", arg);
		return (PARSE_ERROR);
	}
	if (*end != '\0')
	{
		dprintf(2, "ft_ping: invalid value (`%s' near `%s')\n", arg, end);
		return (PARSE_ERROR);
	}
	*opt = val;
	return (PARSE_OK);
}
