#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

#include "path.h"
#include "const.h"
#include "util.h"

// Path delimiter
// -> "/bin:/usr/bin:/usr/local/bin"
#define PATH_DELIM ":"

char path[MAX_PATH_LEN] = "/bin";

// Check if a filepath is already included in 'path'
int check_path_included(char *newpath) {
    char p[MAX_PATH_LEN];
    strcpy(p, path);
    char *token = strtok(p, PATH_DELIM);

    // Tokenize path using it's delimiter and compare strings, if a match is
    // found 'newpath' should not be added to 'path'
    while (token != NULL) {
        if (strcmp(token, newpath) == 0) {
            return 0;
        }

        token = strtok(NULL, PATH_DELIM);
    }

    return 1;
}

// Add 'newpath' to 'path' if it's valid
int update_path(char *newpath) {
    // Check if it's already there
    if (!check_path_included(newpath)) {
        printerr("%s: path already included\n", PROGNAME);
        return 1;
    }

    // Check if such file exists
    if (access(newpath, F_OK)) {
        if (errno == ENOTDIR) {
            printerr("%s: Path dir does not exist\n", PROGNAME);
            return 1;
        }
    }

    // Update path
    strcat(path, PATH_DELIM);
    strcat(path, newpath);

    return 0;
}

// Search the paths for a 'cmd' named program
int which_path(char *cmd, char *ret) {
    // Copy 'path' to 'p', which is then tokenized using path's delimiter
    char p[MAX_PATH_LEN];
    strcpy(p, path);
    char *pathdir = strtok(p, PATH_DELIM);

    char cmdpath[MAX_PATH_LEN];
    while (pathdir != NULL) {
        // Generate the aboslute path of a 'cmd' and check if such file exists
        strcpy(cmdpath, "");
        strcat(cmdpath, pathdir);
        strcat(cmdpath, "/");
        strcat(cmdpath, cmd);

        // If file exists and has user has executable access, store the path
        // into the 'ret' argument
        if (access(cmdpath, X_OK) == 0) {
            strcpy(ret, cmdpath);
            return 0;
        }

        pathdir = strtok(NULL, PATH_DELIM);
    }

    return 1;
}

