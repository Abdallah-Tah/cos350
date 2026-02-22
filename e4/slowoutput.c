/*
Name: Abdallah Mohamed
Course: COS 350
Experiment 4
Date: Feb. 24, 2026
*/
#include <stdio.h>
#include <unistd.h>

int main(void)
{
    FILE *fp = fopen("file.txt", "w");
    if (!fp)
        return 1;

    while (1)
    {
        fprintf(fp, "test\n");
        usleep(10000);
    }

    return 0;
}