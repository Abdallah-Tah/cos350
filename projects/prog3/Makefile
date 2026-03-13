CC = gcc
CFLAGS = -Wall -g

# Build zarchive
all: zarchive

# Compile zarchive
zarchive: zarchive.c
	$(CC) $(CFLAGS) -o zarchive zarchive.c

# Remove the executable
clean:
	rm -f zarchive

.PHONY: all clean
