I ran the program in the background (./slowoutput &) and checked the file size using ls -l (or watch ls -l file.txt).

The file size did not grow line by line. It stayed the same for some time and then grew in big chunks.

The file size increased by about 8192 bytes each time.

After that, I stopped the program using fg and Ctrl-C, and then removed the file.

Output:
total 60
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed  8192 Feb  5 00:23 file.txt
-rwxrwx--x 1 abdallah.mohamed abdallah.mohamed 16056 Feb  5 00:22 slowoutput
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed   293 Feb  5 00:17 slowoutput.c
abdallah.mohamed@ant:~/experiments/e4$ ls -l
total 68
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed 16384 Feb  5 00:23 file.txt
-rwxrwx--x 1 abdallah.mohamed abdallah.mohamed 16056 Feb  5 00:22 slowoutput
-rw-rw---- 1 abdallah.mohamed abdallah.mohamed   293 Feb  5 00:17 slowoutput.c

