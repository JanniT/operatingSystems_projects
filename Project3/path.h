#ifndef PATH_H
#define PATH_H

#include "const.h"

int update_path(char *newpath); // Append "newpath" to path
int which_path(char *cmd, char *ret); // Return path where "cmd" is found
int check_valid_path(char *newpath);
int check_path_included(char *newpath);

#endif // PATH_H
