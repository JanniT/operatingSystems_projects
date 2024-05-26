#ifndef UTIL_H
#define UTIL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>

#include "const.h"

// Debugging tools
void reveal(char *str);
void debuglog(char *format, ...);

// Print prompt and error message
void print_prompt(void);
void printerr(char *format, ...);

// Check if in interactive mode
bool is_interactive(int nextvalue);

#endif // UTIL_H
