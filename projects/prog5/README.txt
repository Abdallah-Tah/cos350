Name: Abdallah Mohamed
Course: COS 350
Program 5 - mysh
Date: April 24, 2026

Files:
mysh.c
execute.c
splitline.c
smsh.h
Makefile
README.txt

How to build:
    make

How to run:
    ./mysh

Result:
abdallah.mohamed@ant:~/prog5$ ./mysh 
mysh> ls
execute.c  Makefile  mysh  mysh.c  result.txt  smsh1.c	smsh.h	splitline.c
mysh> date
Fri Apr 24 11:39:30 PM EDT 2026
mysh> bogus
cannot execute command: No such file or directory
mysh> exit
abdallah.mohamed@ant:~/prog5$ ./mysh 
mysh> exit 7
abdallah.mohamed@ant:~/prog5$ echo $?
7
abdallah.mohamed@ant:~/prog5$ ./mysh 
mysh> pwd
/home/abdallah.mohamed/prog5
mysh> cd ..
mysh> cd /usr/bin
mysh> pwd
/usr/bin
mysh> cd
mysh> pwd
/home/abdallah.mohamed
mysh> sleep 10 &
[background] started PID 2621244
mysh> ps -l
[background] finished PID 2621244
F S   UID     PID    PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
0 S 982097 2614384 2614383  0 80   0 -  5553 do_wai pts/11   00:00:00 bash
0 S 982097 2620388 2614384  0 80   0 -   670 do_wai pts/11   00:00:00 mysh
0 R 982097 2621611 2620388 12 80   0 -  3412 -      pts/11   00:00:00 ps
mysh> ps -l
F S   UID     PID    PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
0 S 982097 2614384 2614383  0 80   0 -  5553 do_wai pts/11   00:00:00 bash
0 S 982097 2620388 2614384  0 80   0 -   670 do_wai pts/11   00:00:00 mysh
0 R 982097 2621655 2620388  0 80   0 -  3412 -      pts/11   00:00:00 ps
mysh> ps -l
F S   UID     PID    PPID  C PRI  NI ADDR SZ WCHAN  TTY          TIME CMD
0 S 982097 2614384 2614383  0 80   0 -  5553 do_wai pts/11   00:00:00 bash
0 S 982097 2620388 2614384  0 80   0 -   670 do_wai pts/11   00:00:00 mysh
0 R 982097 2622100 2620388  0 80   0 -  3412 -      pts/11   00:00:00 ps
mysh> exit
abdallah.mohamed@ant:~/prog5$ 