#ifndef CMD_H
#define CMD_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include "argparse.h"
#include "path.h"
#include "const.h"

#define MAX_CMD_NAME_LEN 64

struct {
    char cmd[MAX_CMD_NAME_LEN];
    int (*callback)(int argc, char (*argv)[MAX_ARG_LEN]);
} typedef internal_cmd;

int check_ret(char *s);

int cmd_path(int argc, char (*argv)[MAX_ARG_LEN]);
int cmd_cd(int argc, char (*argv)[MAX_ARG_LEN]);
int cmd_exit(int argc, char (*argv)[MAX_ARG_LEN]);
int cmd_pwd(int argc, char (*argv)[MAX_ARG_LEN]);

int execute_internal(parsed_command *cmd);
int execute_external(parsed_command *cmd);
int execute_command(parsed_command *cmd);

#endif // CMD_H
