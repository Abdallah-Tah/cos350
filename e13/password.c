/*
Name: Abdallah Mohamed
Course: COS 350
Experiment 13 - password
Date: March 25, 2026
*/

#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#define MAX_PASSWORD 128

int main(void)
{
    struct termios oldt, newt;
    char password[MAX_PASSWORD];
    int ch;
    int i = 0;

    if (tcgetattr(STDIN_FILENO, &oldt) != 0)
    {
        perror("tcgetattr");
        return 1;
    }

    newt = oldt;

    newt.c_lflag &= ~(ECHO | ICANON);

    if (tcsetattr(STDIN_FILENO, TCSANOW, &newt) != 0)
    {
        perror("tcsetattr");
        return 1;
    }

    printf("Enter password: ");
    fflush(stdout);

    // Read characters one at a time until newline or EOF
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
        if ((ch == 127 || ch == '\b') && i > 0)
        {
            i--;
            // Erase a star visually.
            printf("\b \b");
            fflush(stdout);
        }
        else if (i < MAX_PASSWORD - 1)
        {
            password[i++] = ch;
            // Print a star for each character typed
            printf("*");
            fflush(stdout);
        }
    }

    password[i] = '\0';

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    printf("\nPassword entered: %s\n", password);

    return 0;
}