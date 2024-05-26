#ifndef PATH_H
#define PATH_H

#include "const.h"

// Update 'path' with new filepath
// Find filepath where a program is located
// Check if a filepath is already included in 'path'
int update_path(char *newpath);
int which_path(char *cmd, char *ret);
int check_path_included(char *newpath);

#endif // PATH_H
