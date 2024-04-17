CC = gcc
ARGS = -pedantic -Wall

REVERSEAPP = reverse

# reverse
$(REVERSEAPP): Project1/reverse.c
	$(CC) Project1/reverse.c -o $(REVERSEAPP) $(ARGS)

clean:
	rm $(REVERSEAPP)
