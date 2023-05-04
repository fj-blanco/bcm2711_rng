CC = gcc
CFLAGS = -Wall -Wextra
LDFLAGS =

all: main

main: main.o bcm2711_rng.o
	$(CC) $(CFLAGS) -o main main.o bcm2711_rng.o $(LDFLAGS)

main.o: main.c bcm2711_rng.h
	$(CC) $(CFLAGS) -c main.c

bcm2711_rng.o: bcm2711_rng.c bcm2711_rng.h
	$(CC) $(CFLAGS) -c bcm2711_rng.c

clean:
	rm -f main *.o

.PHONY: all clean