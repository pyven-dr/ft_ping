#ifndef PARSING_H
#define PARSING_H

#define OPT_HELP 200

typedef struct s_ping_opt t_ping_opt;

typedef enum e_parse_codes
{
	PARSE_OK = 0,
	PARSE_HELP = 1,
	PARSE_ERROR = 2
}	t_parse_code;

int parsing_args(int argc, char** argv, t_ping_opt* opt);
int handle_flags(int flag, char **argv, t_ping_opt* opt);
int set_opt(size_t* opt, char* arg, unsigned long min, unsigned long max);

#endif
