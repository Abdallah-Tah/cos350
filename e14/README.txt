Name: Abdallah Mohamed
Course: COS 350
Experiment 14 - endless loop
Date: March 25, 2026

SIGINT stopped the program.
SIGFPE also stopped the program and showed a floating point exception message.
SIGKILL killed the program right away.
SIGCHLD did not stop the program, so it kept running. That was the surprise. 
At the end, I used ps -u $USER to check for running processes and then killed the endless loop process.

abdallah.mohamed@ant:~/exp14$ script result 
Script started, output log file is 'result'.
bash: export: `:/usr/local/cuda-12.2/lib64': not a valid identifier
abdallah.mohamed@ant:~/exp14$ ./endlessloop &
[1] 449103
abdallah.mohamed@ant:~/exp14$ PID: 449103
kill -SIGINT 449103
abdallah.mohamed@ant:~/exp14$ ./endlessloop &
[2] 449291
[1]   Interrupt               ./endlessloop
abdallah.mohamed@ant:~/exp14$ PID: 449291
kill -SIGFPE 449292
bash: kill: (449292) - No such process
abdallah.mohamed@ant:~/exp14$ kill -SIGFPE 449291
abdallah.mohamed@ant:~/exp14$ ./endlessloop &
[3] 449430
[2]   Floating point exception(core dumped) ./endlessloop
abdallah.mohamed@ant:~/exp14$ PID: 449430
kill -SIGKILL 449430
abdallah.mohamed@ant:~/exp14$ ./endlessloop &
[4] 449639
[3]   Killed                  ./endlessloop
abdallah.mohamed@ant:~/exp14$ PID: 449639
kill -SIGCHLD 449639
abdallah.mohamed@ant:~/exp14$ ps -u $USER
    PID TTY          TIME CMD
 431132 ?        00:00:00 systemd
 431133 ?        00:00:00 (sd-pam)
 431144 ?        00:00:00 pipewire
 431145 ?        00:00:00 pipewire
 431147 ?        00:00:00 snapd-desktop-i
 431149 ?        00:00:00 wireplumber
 431150 ?        00:00:00 pipewire-pulse
 431182 ?        00:00:00 dbus-daemon
 431259 ?        00:00:03 sshd
 431263 ?        00:00:00 xdg-document-po
 431264 pts/0    00:00:00 bash
 431268 ?        00:00:00 xdg-permission-
 431439 ?        00:00:00 snapd-desktop-i
 446928 pts/0    00:00:00 script
 446929 pts/2    00:00:00 bash
 447568 pts/2    00:00:00 script
 447569 pts/3    00:00:00 bash
 449019 pts/3    00:00:00 script
 449020 pts/1    00:00:00 bash
 449639 pts/1    00:00:00 endlessloop
 449768 pts/1    00:00:00 ps
abdallah.mohamed@ant:~/exp14$ kill pid 449639
bash: kill: pid: arguments must be process or job IDs
abdallah.mohamed@ant:~/exp14$ ps -u $USER
    PID TTY          TIME CMD
 431132 ?        00:00:00 systemd
 431133 ?        00:00:00 (sd-pam)
 431144 ?        00:00:00 pipewire
 431145 ?        00:00:00 pipewire
 431147 ?        00:00:00 snapd-desktop-i
 431149 ?        00:00:00 wireplumber
 431150 ?        00:00:00 pipewire-pulse
 431182 ?        00:00:00 dbus-daemon
 431259 ?        00:00:03 sshd
 431263 ?        00:00:00 xdg-document-po
 431264 pts/0    00:00:00 bash
 431268 ?        00:00:00 xdg-permission-
 431439 ?        00:00:00 snapd-desktop-i
 446928 pts/0    00:00:00 script
 446929 pts/2    00:00:00 bash
 447568 pts/2    00:00:00 script
 447569 pts/3    00:00:00 bash
 449019 pts/3    00:00:00 script
 449020 pts/1    00:00:00 bash
 449952 pts/1    00:00:00 ps
[4]+  Terminated              ./endlessloop
abdallah.mohamed@ant:~/exp14$ 
