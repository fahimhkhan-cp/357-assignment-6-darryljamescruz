CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -g
OBJ = main.o data.o

all: main

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

main.o: main.c data.h
	$(CC) $(CFLAGS) -c main.c

data.o: data.c data.h
	$(CC) $(CFLAGS) -c data.c

clean:
	rm -f *.o main