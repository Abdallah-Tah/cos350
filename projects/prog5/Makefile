CC = gcc
CFLAGS = -Wall

mysh: mysh.c execute.c splitline.c smsh.h
	$(CC) $(CFLAGS) -o mysh mysh.c execute.c splitline.c

clean:
	rm -f mysh
