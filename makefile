CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -g

all: bignumber_test

bignumber_test: bignumber.o client.o
	$(CC) $(CFLAGS) -o bignumber_test bignumber.o client.o

bignumber.o: bignumber.c bignumber.h
	$(CC) $(CFLAGS) -c bignumber.c

client.o: client.c bignumber.h
	$(CC) $(CFLAGS) -c client.c

clean:
	rm -f *.o bignumber_test