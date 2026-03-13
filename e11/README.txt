When I used chmod 007, I could not read the file. Even though others had full permissions, I am the owner. 
The owner permissions were - - - so the kernel denied access.

When I changed the mode to 707 and 700, I was able to read the file because the owner had read permission.

From this experiment, I learned that the kernel checks permissions in order, Owner, then Group, then Other. 
When the kernel finds which category the user belongs to, it only uses that category permissions and stops checking. 
This is why I could not read the file with 007 permissions because I am the owner, the kernel only checked the owner 
permissions (- - -) and did not look at the other permissions rwx.


Script started on 2026-03-03 19:19:09-05:00 [TERM="xterm-256color" TTY="/dev/pts/22" COLUMNS="80" LINES="24"]
bash: export: `:/usr/local/cuda-12.2/lib64': not a valid identifier
^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ touch filename.txt
^[[?2004l^M^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ echo 'This is my file' > filename.txt  ^M^[[A^[[C^[[C^[[C^[[C^[[C^[[C^[[C^[[C^[[C^[[C^[[C^[[C^[[C^[[>
^[[?2004l^M^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ ls -l
^[[?2004l^Mtotal 4
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed 16 Mar  3 19:20 filename.txt
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed  0 Mar  3 19:19 result.txt
^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ cat filename.txt
^[[?2004l^MThis is my file
^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ chm^God 007 filename.txt
^[[?2004l^M^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ ls -ls
^[[?2004l^Mtotal 4
4 -------rwx? 1 abdallah.mohamed abdallah.mohamed 16 Mar  3 19:20 ^[[0m^[[01;32mfilename.txt^[[0m
0 -rw-rw----  1 abdallah.mohamed abdallah.mohamed  0 Mar  3 19:19 result.txt
^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ cat filename.txt
^[[?2004l^Mcat: filename.txt: Permission denied
^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ ^[[7mhmod 707 filename.txt^[[27m^G^H^H^H^H^H^H^H^H^H^H^H^H^H^H^H^H^H^H^H^H^Hhmod 707 filename.txt^H^H^H^H^H^H^H>
^[[?2004l^M^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ ls -ls
^[[?2004l^Mtotal 4
4 -rwx---rwx 1 abdallah.mohamed abdallah.mohamed 16 Mar  3 19:20 ^[[0m^[[01;32mfilename.txt^[[0m
0 -rw-rw---- 1 abdallah.mohamed abdallah.mohamed  0 Mar  3 19:19 result.txt
^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ cd ^H^[[K^H^[[Kat filename.txt
^[[?2004l^MThis is my file
^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ cm^H^[[Khmod 0^H^[[K700 filename.txt
^[[?2004l^M^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ ls -^H^[[K^H^[[K^H^[[K^H^[[K^G^G^G^Gls -l
^[[?2004l^Mtotal 4
-rwx------ 1 abdallah.mohamed abdallah.mohamed 16 Mar  3 19:20 ^[[0m^[[01;32mfilename.txt^[[0m
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed  0 Mar  3 19:19 result.txt
^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ cat filename.txt
^[[?2004l^MThis is my file
^[[?2004h^[]0;abdallah.mohamed@ant: ~/experiments/exp11^G^[[01;32mabdallah.mohamed@ant^[[00m:^[[01;34m~/experiments/exp11^[[00m$ exit
^[[?2004l^Mexit

Script done on 2026-03-03 19:26:05-05:00 [COMMAND_EXIT_CODE="0"]