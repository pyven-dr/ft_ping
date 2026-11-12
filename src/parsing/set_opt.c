#include <stdio.h>

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
	if (max != 0 && val > max)
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

int set_opt_double(double* opt, char* arg, double min)
{
	char* end;
	double val = strtod(arg, &end);

	if (val < min)
	{
		dprintf(2, "ft_ping: option value too small: %s\n", arg);
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
