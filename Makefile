CC = gcc
ARGS = -pedantic -Wall -Werror

REVERSEAPP = reverse
MYCATAPP = my-cat
MYGREPAPP = my-grep
MYZIPAPP = my-zip
MYUNZIPAPP = my-unzip
MYSHELLAPP = wish

all: $(REVERSEAPP) $(MYCATAPP) $(MYGREPAPP) $(MYZIPAPP) $(MYUNZIPAPP) $(MYSHELLAPP)

# reverse
$(REVERSEAPP): Project1/reverse.c
	$(CC) Project1/reverse.c -o $(REVERSEAPP) $(ARGS)

# my-cat
$(MYCATAPP): Project2/my-cat.c
	$(CC) Project2/my-cat.c -o $(MYCATAPP) $(ARGS)

# my-grep
$(MYGREPAPP): Project2/my-grep.c
	$(CC) Project2/my-grep.c -o $(MYGREPAPP) $(ARGS)

# my-zip
$(MYZIPAPP): Project2/my-zip.c
	$(CC) Project2/my-zip.c -o $(MYZIPAPP) $(ARGS)

# my-unzip
$(MYUNZIPAPP): Project2/my-unzip.c
	$(CC) Project2/my-unzip.c -o $(MYUNZIPAPP) $(ARGS)

# wish
$(MYSHELLAPP): Project3/wish.c Project3/cmd.c Project3/cmd.h Project3/const.h
	$(CC) Project3/wish.c Project3/cmd.c -o $(MYSHELLAPP) $(ARGS)

clean:
	rm -f $(REVERSEAPP) $(MYCATAPP) $(MYGREPAPP) $(MYZIPAPP) $(MYUNZIPAPP) $(MYSHELLAPP)
