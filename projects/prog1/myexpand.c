#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Author: Abdallah Mohamed
 * Date:   February 12, 2026
 * Project 1: myexpand
 *
 */

int main(int argc, char **argv)
{
    int tabSpace = 8;        // 8 tab spaces
    int charInput;           // current character input
    int currentPosition = 0; // current position in the line

    if (argc == 1)
    {
        // tabSpace = 8
    }
    else if (argc == 3)
    {
        // check if the first argument is "-t" and the second argument is a positive integer
        if (strcmp(argv[1], "-t") == 0)
        {
            tabSpace = atoi(argv[2]);
            // check if the tabSpace is a positive integer
            if (tabSpace <= 0)
            {
                fprintf(stderr, "Error: tabstop must be a positive integer.\n");
                return 1;
            }
        }
        else
        {
            fprintf(stderr, "Error: invalid option.\n");
            fprintf(stderr, "Usage: %s [-t tabstop]\n", argv[0]);
            return 1;
        }
    }
    else
    {
        fprintf(stderr, "Error: invalid command line arguments.\n");
        fprintf(stderr, "Usage: %s [-t tabstop]\n", argv[0]);
        return 1;
    }

    // read, and process each character until end of the file.
    while ((charInput = getchar()) != EOF)
    {
        if (charInput == '\t')
        {
            int spaces = tabSpace - (currentPosition % tabSpace);

            for (int i = 0; i < spaces; i++)
            {
                putchar(' ');
                currentPosition++;
            }
        }
        else if (charInput == '\n')
        {
            putchar('\n');
            currentPosition = 0;
        }
        else
        {
            putchar(charInput);
            currentPosition++;
        }
    }

    return 0;
}
