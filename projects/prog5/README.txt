Name: Abdallah Mohamed
Course: COS 350
Program 5 - mysh
Date: April 24, 2026

Files:
mysh.c
Makefile
README.txt

How to build:
    make

How to run:
    ./mysh

Features added to the book's smallsh:
- Custom prompt "mysh> "
- exit [value] built-in
- cd [dir] built-in (no arg goes to home)
- Background jobs with & at end of line
- Background start/finish messages with PID
- Uses waitpid() with WNOHANG to clean up zombies

Notes:
Ctrl-C and Ctrl-\ are ignored by the shell (like the book) but
restored in child processes so commands can still be killed.

Testing/Grading

changed prompt                   10  works
correct command execution        10  works
exit                             10  works
exit value                       10  works
cd dir                           15  works
cd                               15  works
start job in background          15  works
notify background job complete   15  works
