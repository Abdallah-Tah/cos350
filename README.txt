Name: Abdallah Mohamed
Experiment 2 - Recursive C Function

1) Write and test a recursive C function (not main) that endlessly calls itself.

I wrote a function called recursive(int n).  
This function calls itself again using recursive(n + 1).  

2) How many times can it call itself?

On my mac, the program printed up to:
n = 174230

So the function called itself about 174,230 times before it failed.

3) What error message do you get when it fails?

The program crashed because the stack became full.
The error message was:

segmentation fault

Terminal message:
[1]    68568 segmentation fault  ./recursive

Program output (end):
n = 174226
n = 174227
n = 174228
n = 174229
n = 174230
[1]    68568 segmentation fault  ./recursive

Commands used:

Compile:
gcc recursion.c -o recursive

Run:
./recursive
