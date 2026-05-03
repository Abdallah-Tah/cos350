/*
Name: Abdallah Mohamed
Course: COS 350
Program 5 - mysh
Date: April 24, 2026

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include "smsh.h"

#define DFL_PROMPT "mysh> "

static void setup(void);
static int do_builtin(char **arglist);
static void check_background(void);

int main(void)
{
    char *cmdline, *prompt, **arglist;
    int background;

    prompt = DFL_PROMPT;
    setup();

    while ((cmdline = next_cmd(prompt, stdin)) != NULL)
    {
        check_background();

        if ((arglist = splitline(cmdline)) != NULL)
        {
            background = 0;

            if (arglist[0] != NULL)
            {
                int last;

                for (last = 0; arglist[last + 1] != NULL; last++)
                    ;

                if (strcmp(arglist[last], "&") == 0)
                {
                    background = 1;
                    free(arglist[last]);
                    arglist[last] = NULL;

                    if (arglist[0] == NULL)
                        background = 0;
                }
            }

            if (!do_builtin(arglist))
                execute(arglist, background);

            freelist(arglist);
        }
        free(cmdline);
    }

    putchar('\n');
    return 0;
}

static void setup(void)
{
    if (signal(SIGINT, SIG_IGN) == SIG_ERR)
        fatal("signal", "SIGINT", 1);
    if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
        fatal("signal", "SIGQUIT", 1);
}

static int do_builtin(char **arglist)
{
    if (arglist[0] == NULL)
        return 1;

    if (strcmp(arglist[0], "exit") == 0)
    {
        int code = 0;

        if (arglist[1] != NULL)
        {
            char *endptr;
            long value;

            errno = 0;
            value = strtol(arglist[1], &endptr, 10);
            if (errno != 0 || *arglist[1] == '\0' || *endptr != '\0')
            {
                fprintf(stderr, "exit: numeric argument required\n");
                return 1;
            }
            code = (int)value;
        }

        exit(code);
    }

    if (strcmp(arglist[0], "cd") == 0)
    {
        char *dir;

        if (arglist[1] == NULL)
        {
            dir = getenv("HOME");
            if (dir == NULL)
            {
                fprintf(stderr, "cd: HOME not set\n");
                return 1;
            }
        }
        else
        {
            dir = arglist[1];
        }

        if (chdir(dir) != 0)
            perror("cd");

        return 1;
    }

    return 0;
}

static void check_background(void)
{
    int status;
    pid_t pid;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
        printf("[background] finished PID %d\n", pid);

    if (pid < 0 && errno != ECHILD)
        perror("waitpid");
}

void fatal(char *s1, char *s2, int n)
{
    fprintf(stderr, "Error: %s %s\n", s1, s2);
    exit(n);
}
