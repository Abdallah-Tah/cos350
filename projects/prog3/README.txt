/*
 * Author: Abdallah Mohamed
 * Date:   March 13, 2026
 * Program 3 - zarchive
 *
 */
 
abdallah.mohamed@ant:~/projects/program03$ script result.txt
Script started, output log file is 'result.txt'.
bash: export: `:/usr/local/cuda-12.2/lib64': not a valid identifier
abdallah.mohamed@ant:~/projects/program03$ ls
myfile.txt  result.txt  zarchive.c
abdallah.mohamed@ant:~/projects/program03$ gcc zarchive.c -o zarchive
abdallah.mohamed@ant:~/projects/program03$ ls -l
total 48
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed    16 Mar 13 15:54 myfile.txt
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed     0 Mar 13 16:15 result.txt
-rwxrwx--x 1 abdallah.mohamed abdallah.mohamed 25984 Mar 13 16:19 zarchive
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed 16031 Mar 13 15:52 zarchive.c
abdallah.mohamed@ant:~/projects/program03$  ./zarchive c myarchive.z
Archive owner: abdallah.mohamed

Files in current directory:
Size         Modified         Name
16           Mar 13 15:54     myfile.txt
0            Mar 13 16:15     result.txt
25984        Mar 13 16:19     zarchive
16031        Mar 13 15:52     zarchive.c

Enter file names to archive (* for all): *

Created myarchive.z with 4 file(s)

Archive contents:
Owner: abdallah.mohamed
Files: 4
Size         Modified         Name
16           Mar 13 15:54     myfile.txt
0            Mar 13 16:15     result.txt
25984        Mar 13 16:19     zarchive
16031        Mar 13 15:52     zarchive.c
abdallah.mohamed@ant:~/projects/program03$ ls -l
total 92
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed 43223 Mar 13 16:20 myarchive.z
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed    16 Mar 13 15:54 myfile.txt
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed     0 Mar 13 16:15 result.txt
-rwxrwx--x 1 abdallah.mohamed abdallah.mohamed 25984 Mar 13 16:19 zarchive
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed 16031 Mar 13 15:52 zarchive.c
abdallah.mohamed@ant:~/projects/program03$ ./zarchive x myfiles.z extractdir
Error: archive myfiles.z does not exist
abdallah.mohamed@ant:~/projects/program03$ ./zarchive x myarchive.z extractdir
Archive owner: abdallah.mohamed
Extracting 4 file(s)
Extracted extractdir/myfile.txt
Extracted extractdir/result.txt
Extracted extractdir/zarchive
Extracted extractdir/zarchive.c
abdallah.mohamed@ant:~/projects/program03$ ls -l
total 92
drwxr-x--x 2 abdallah.mohamed abdallah.mohamed    76 Mar 13 16:21 extractdir
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed 43223 Mar 13 16:20 myarchive.z
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed    16 Mar 13 15:54 myfile.txt
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed     0 Mar 13 16:15 result.txt
-rwxrwx--x 1 abdallah.mohamed abdallah.mohamed 25984 Mar 13 16:19 zarchive
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed 16031 Mar 13 15:52 zarchive.c
abdallah.mohamed@ant:~/projects/program03$ cd extractdir
abdallah.mohamed@ant:~/projects/program03/extractdir$ ls -l
total 48
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed    16 Mar 13 15:54 myfile.txt
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed     0 Mar 13 16:15 result.txt
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed 25984 Mar 13 16:19 zarchive
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed 16031 Mar 13 15:52 zarchive.c
abdallah.mohamed@ant:~/projects/program03/extractdir$ cd ..
abdallah.mohamed@ant:~/projects/program03$ ./zarchive x myarchive.z
Warning: extracting into current directory
Archive owner: abdallah.mohamed
Extracting 4 file(s)
Error: myfile.txt already exists, will not overwrite
abdallah.mohamed@ant:~/projects/program03$ ls -l
total 100
drwxr-x--x 2 abdallah.mohamed abdallah.mohamed    76 Mar 13 16:21 extractdir
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed 43223 Mar 13 16:20 myarchive.z
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed    16 Mar 13 15:54 myfile.txt
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed  8192 Mar 13 16:22 result.txt
-rwxrwx--x 1 abdallah.mohamed abdallah.mohamed 25984 Mar 13 16:19 zarchive
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed 16031 Mar 13 15:52 zarchive.c
abdallah.mohamed@ant:~/projects/program03$ exit
exit
Script done.
abdallah.mohamed@ant:~/projects/program03$
