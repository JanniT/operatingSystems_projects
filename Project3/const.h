#ifndef CONST_H
#define CONST_H

#define MAX_ARG_NUM 256
#define MAX_ARG_LEN 1024

#define MAX_PATH_LEN 1024

#define QUOTE(str) #str
#define STR(str) QUOTE(str)

#ifndef PROG
#   define PROG shellapp
#endif

#define PROGNAME STR(PROG)

#endif // CONST_H
