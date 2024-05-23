#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "const.h"
#include "util.h"

struct {
    int argc;
    char argv[MAX_ARG_NUM][MAX_ARG_LEN];
    char output_redirect_filename[MAX_ARG_LEN];
    FILE *output_redirect;

    int quote;
    
    bool background;
} typedef parsed_command;

int parse_and_execute(parsed_command *cmd, char *cmdline);

void reset_cmd(parsed_command *cmd);

#endif // ARGPARSE_H
