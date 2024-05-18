#ifndef CMD_H
#define CMD_H

#include <unistd.h>
#include <stdio.h>

#include "const.h"

#define MAX_CMD_NAME_LEN 64

struct {
    char cmd[MAX_CMD_NAME_LEN];
    int (*callback)(int argc, char (*argv)[MAX_ARG_LEN]);
} typedef internal_cmd;

int check_ret(char *s);
int execute_internal(int argc, char (*argv)[MAX_ARG_LEN]);
int execute_external(int argc, char (*argv)[MAX_ARG_LEN]);

int cmd_exit(int argc, char (*argv)[MAX_ARG_LEN]);
int cmd_pwd(int argc, char (*argv)[MAX_ARG_LEN]);
int cmd_cd(int argc, char (*argv)[MAX_ARG_LEN]);
int cmd_path(int argc, char (*argv)[MAX_ARG_LEN]);

#endif // CMD_H
