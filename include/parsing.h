#ifndef PARSING_H
#define PARSING_H

#define OPT_HELP 200

typedef enum e_parse_codes
{
	PARSE_OK = 0,
	PARSE_HELP = 1,
	PARSE_ERROR = 2
}	t_parse_code;

int parsing_args(int argc, char** argv);
int handle_flags(int flag, char** argv);

#endif
