/*
Name: Abdallah Mohamed
Course: COS 350
Experiment 19 - exec4
Date: April 14, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int count = 1;
    char buf[10];

    if (argc > 1)
        count = atoi(argv[1]);

    printf("Count: %d, PID: %d\n", count, getpid());

    if (count < 5)
    {
        sprintf(buf, "%d", count + 1);
        argv[1] = buf;
        execvp(argv[0], argv);
    }

    return 0;
}
