/*
Name: Abdallah Mohamed
Course: COS 350
Experiment 2 - Recursive C
Date: January 24, 2026
Description: Write and test a recursive C function (not main) that endlessly calls itself. How many times can it call itself? What error message do you get when it fails?
*/

#include <stdio.h>

/*
This function calls itself again and again.
There is no stopping condition.
*/
int recursive(int n)
{
    printf("n = %d\n", n);   // print the value of n
    return recursive(n + 1); // call itself again
}

int main()
{
    recursive(1); // start the recursion
    return 0;
}
