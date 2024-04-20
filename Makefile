CC = gcc
ARGS = -pedantic -Wall -Werror

REVERSEAPP = reverse
MYCATAPP = my-cat
MYGREPAPP = my-grep

all: $(REVERSEAPP) $(MYCATAPP) $(MYGREPAPP)

# reverse
$(REVERSEAPP): Project1/reverse.c
	$(CC) Project1/reverse.c -o $(REVERSEAPP) $(ARGS)

# my-cat
$(MYCATAPP): Project2/my-cat.c
	$(CC) Project2/my-cat.c -o $(MYCATAPP) $(ARGS)

# my-grep
$(MYGREPAPP): Project2/my-cat.c
	$(CC) Project2/my-grep.c -o $(MYGREPAPP) $(ARGS)

clean:
	rm $(REVERSEAPP) $(MYCATAPP) $(MYGREPAPP)
