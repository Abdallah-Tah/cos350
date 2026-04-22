/*
Name: Abdallah Mohamed
Course: COS 350
Experiment 14 - endless loop
Date: March 25, 2026
*/

#include <stdio.h>
#include <unistd.h>

int main(void)
{
    printf("PID: %d\n", getpid());
    fflush(stdout);

    while (1)
    {
        sleep(1);
    }

    return 0;
}
