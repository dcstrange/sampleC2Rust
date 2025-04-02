CC = gcc
CFLAGS = -Wall -Wextra -g
OBJS = main.o book.o library.o

all: library_system

library_system: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS)

main.o: main.c book.h library.h
	$(CC) $(CFLAGS) -c main.c

book.o: book.c book.h
	$(CC) $(CFLAGS) -c book.c

library.o: library.c library.h
	$(CC) $(CFLAGS) -c library.c

clean:
	rm -f $(OBJS) library_system

.PHONY: all clean 