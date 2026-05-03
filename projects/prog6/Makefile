CC = gcc
CFLAGS = -Wall -Wextra -O2
PTHREADFLAGS = -pthread

PROGRAMS = lc1 lc2 lc3

all: $(PROGRAMS)

lc1: lc1.c linecount.c linecount.h
	$(CC) $(CFLAGS) -o $@ lc1.c linecount.c

lc2: lc2.c
	$(CC) $(CFLAGS) -o $@ lc2.c

lc3: lc3.c linecount.c linecount.h
	$(CC) $(CFLAGS) $(PTHREADFLAGS) -o $@ lc3.c linecount.c

clean:
	rm -f $(PROGRAMS)
