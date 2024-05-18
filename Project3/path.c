#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "path.h"
#include "const.h"

#define PATH_DELIM ":"

char path[MAX_PATH_LEN] = "/bin:/usr/bin:/usr/local/bin";

int check_path_included(char *newpath) {
    char p[MAX_PATH_LEN];
    strcpy(p, path);
    char *token = strtok(p, PATH_DELIM);

    while (token != NULL) {
        if (strcmp(token, newpath) == 0) {
            return 0;
        }

        token = strtok(NULL, PATH_DELIM);
    }

    return 1;
}

int update_path(char *newpath) {
    if (!check_path_included(newpath)) {
        printf("ERR: Path already included\n");
        return 1;
    }

    // Check if such file exists
    if (access(newpath, F_OK)) {
        if (errno == ENOTDIR) {
            printf("ERR: Path dir does not exist\n");
            return 1;
        }
    }

    strcat(path, PATH_DELIM);
    strcat(path, newpath);

    return 0;
}

// Return path to where appliaction is found
int which_path(char *cmd, char *ret) {
    char p[MAX_PATH_LEN];
    strcpy(p, path);
    char *pathdir = strtok(p, PATH_DELIM);

    char cmdpath[MAX_PATH_LEN];
    while (pathdir != NULL) {
        strcpy(cmdpath, "");
        strcat(cmdpath, pathdir);
        strcat(cmdpath, "/");
        strcat(cmdpath, cmd);

        if (access(cmdpath, X_OK) == 0) {
            strcpy(ret, cmdpath);
            return 0;
        }

        pathdir = strtok(NULL, PATH_DELIM);
    }

    return 1;
}

