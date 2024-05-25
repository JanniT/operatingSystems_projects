#ifndef CMD_H
#define CMD_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <fcntl.h>

#include "argparse.h"
#include "path.h"
#include "const.h"

#define MAX_CMD_NAME_LEN 64

struct {
    char cmd[MAX_CMD_NAME_LEN];
    int (*callback)(parsed_command *cmd);
} typedef internal_cmd;

int check_atoi_ret(char *s);

int cmd_path(parsed_command *cmd);
int cmd_cd(parsed_command *cmd);
int cmd_exit(parsed_command *cmd);
int cmd_pwd(parsed_command *cmd);

int execute_internal(parsed_command *cmd);
int execute_external(parsed_command *cmd);
int execute_command(parsed_command *cmd);

#endif // CMD_H
