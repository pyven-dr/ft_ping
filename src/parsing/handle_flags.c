#include <getopt.h>
#include <stdio.h>
#include <string.h>

#include "parsing.h"

static void invalid_opt(char **argv) {
  if (optopt != 0)
    dprintf(2, "ft_ping: invalid option -- '%c'\n", optopt);
  else
    dprintf(2, "ft_ping: unrecognized option '%s'\n", argv[optind - 1]);
  dprintf(2, "Try 'ft_ping --help' for more information.\n");
}

int handle_flags(int flag, char **argv) {
  if (flag == '?') {
    if (optopt == 0 && strncmp(argv[optind - 1], "--", 2) != 0) {
      printf("? opt\n");
      return (PARSE_HELP);
    } else {
      invalid_opt(argv);
      return (PARSE_INVALID_OPT);
    }
  } else if (flag == 'v')
    printf("v opt\n");
  else if (flag == OPT_HELP) {
    printf("? opt\n");
    return (PARSE_HELP);
  }
  return (PARSE_OK);
}
