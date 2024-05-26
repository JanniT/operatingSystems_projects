#ifndef CONST_H
#define CONST_H

// MAX_ARG_NUM -> Maximum number of args a command can have
// MAX_ARG_LEN -> Maximum lenght of an arg
#define MAX_ARG_NUM 256
#define MAX_ARG_LEN 1024

// MAX_PATH_LEN -> Maximum length of a internal 'path' variable
#define MAX_PATH_LEN 1024

// Macros to help convert a definition into a string literal
#define QUOTE(str) #str
#define STR(str) QUOTE(str)

// Default name of app is 'shellapp'
#ifndef PROG
#   define PROG shellapp
#endif

#define PROGNAME STR(PROG)

#endif // CONST_H
