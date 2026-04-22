Name: Abdallah Mohamed
Course: COS 350
Experiment 19 - exec4
Date: April 14, 2026

This program runs itself 4 times using exec().
Each run prints a count from 1 to 5 and its PID.
The count is passed as a command line argument to the next run.

To compile and run:
    gcc -o exec4 exec4.c
    ./exec4

Results:
abdallah.mohamed@ant:~/exp19$ ./exec4
Count: 1, PID: 2544442
Count: 2, PID: 2544442
Count: 3, PID: 2544442
Count: 4, PID: 2544442
Count: 5, PID: 2544442

The PID is the same for all runs because exec() replaces the current process. 
It does not create a new process like fork() in E18.
