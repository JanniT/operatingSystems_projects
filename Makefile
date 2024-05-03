CC = gcc
ARGS = -pedantic -Wall -Werror

REVERSEAPP = reverse
MYCATAPP = my-cat
MYGREPAPP = my-grep
MYZIPAPP = my-zip

all: $(REVERSEAPP) $(MYCATAPP) $(MYGREPAPP) $(MYZIPAPP)

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

clean:
	rm $(REVERSEAPP) $(MYCATAPP) $(MYGREPAPP) $(MYZIPAPP)
