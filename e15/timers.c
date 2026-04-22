/*
Name: Abdallah Mohamed
Course: COS 350
Experiment 15 - Timers
Date: 31 March 2026
*/

#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

struct timeval times[1000];
int count = 0;

void handler(int signum)
{
    if (count < 1000)
    {
        gettimeofday(&times[count], NULL);
        count++;
    }
}

int main()
{
    struct itimerval timer;

    signal(SIGALRM, handler);

    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 1000;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 1000;

    setitimer(ITIMER_REAL, &timer, NULL);

    while (count < 1000)
        pause();

    // print the intervals
    long diff;
    long total = 0;
    for (int i = 1; i < count; i++)
    {
        diff = (times[i].tv_sec - times[i - 1].tv_sec) * 1000000 +
               (times[i].tv_usec - times[i - 1].tv_usec);
        printf("Interval %d: %ld microseconds\n", i, diff);
        total += diff;
    }

    printf("\nAverage: %ld microseconds\n", total / (count - 1));

    return 0;
}
