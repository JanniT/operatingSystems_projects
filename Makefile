CC = gcc
ARGS = -pedantic -Wall -Werror

REVERSEAPP = reverse
MYCATAPP = my-cat

all: $(REVERSEAPP) $(MYCATAPP)

# reverse
$(REVERSEAPP): Project1/reverse.c
	$(CC) Project1/reverse.c -o $(REVERSEAPP) $(ARGS)

# my-cat
$(MYCATAPP): Project2/my-cat.c
	$(CC) Project2/my-cat.c -o $(MYCATAPP) $(ARGS)

clean:
	rm $(REVERSEAPP) $(MYCATAPP)
