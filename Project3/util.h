#ifndef UTIL_H
#define UTIL_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdbool.h>

#include "const.h"

void reveal(char *str);
void debuglog(char *format, ...);

void print_prompt(void);
void printerr(char *format, ...);

#endif // UTIL_H
