Name: Abdallah Mohamed
Course: COS 350
Experiment 20 - exec4
Date: April 14, 2026


I changed my shell prompt by editing the .bashrc file. I changed the PS1 variable to a new value. 
Then I used source ~/.bashrc to apply it. After I logged out and logged back in, the new prompt was still there, 
so the change is permanent.

abdallah.mohamed@ant:~$ script result.txt
Script started, output log file is 'result.txt'.
nbash: export: `:/usr/local/cuda-12.2/lib64': not a valid identifier
abdallah.mohamed@ant:~$ nano ~/.bashrc
abdallah.mohamed@ant:~$ source ~/.bashrc
MyShell> exit
exit
Script done.
abdallah.mohamed@ant:~$ cat result.txt 
Script started on 2026-04-14 22:57:13-04:00 [TERM="xterm-256color" TTY="/dev/pts/5" COLUMNS="80" LINES="24"]
nbash: export: `:/usr/local/cuda-12.2/lib64': not a valid identifier
abdallah.mohamed@ant:~$ nano ~/.bashrc
abdallah.mohamed@ant:~$ source ~/.bashrc
MyShell> exit
exit

Script done on 2026-04-14 22:58:55-04:00 [COMMAND_EXIT_CODE="0"]