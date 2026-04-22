/*
Name: Abdallah Mohamed
Course: COS 350
Experiment 18 - fork4
Date: April 7, 2026
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int count = 1;

    for (int i = 0; i < 4; i++)
    {
        pid_t pid = fork();

        if (pid == 0)
        {
            count = i + 2;
            break;
        }
    }

    sleep(1);

    printf("Count: %d, PID: %d\n", count, getpid());

    if (count == 1)
    {
        for (int i = 0; i < 4; i++)
        {
            wait(NULL);
        }
    }

    return 0;
}