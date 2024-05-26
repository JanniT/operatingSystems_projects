#ifndef ARGPARSE_H
#define ARGPARSE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "const.h"
#include "util.h"

// Container for parsed command, which contains:
// argc -> number of parsed arguments, including the command name
// argv -> list of parsed arguments
// output_redirect_filename -> parsed filename when used '>' symbol
// quote -> is used to help parse text in quotes
// background -> if command is meant to be run in the bacground, when used
//               '&' symbol
struct {
    int argc;
    char argv[MAX_ARG_NUM][MAX_ARG_LEN];
    char output_redirect_filename[MAX_ARG_LEN];

    int quote;
    
    bool background;
} typedef parsed_command;

// Get user input and parse the input
int parse_and_execute(parsed_command *cmd, char *cmdline);

// Will empty the parsed_command structure
void reset_cmd(parsed_command *cmd);

#endif // ARGPARSE_H
