/*
Name: Abdallah Mohamed
Course: COS 350
Program 5 - mysh
Date: April 24, 2026

A simple shell based on smallsh from the book.
Adds: custom prompt, exit, cd, background jobs.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>

#define MAX_LINE 1024
#define MAX_ARGS 64
#define PROMPT "mysh> "

void check_background(void);
int parse_line(char *line, char **args, int *background);
void run_command(char **args, int background);
int do_builtin(char **args);

int main(int argc, char *argv[])
{
    char line[MAX_LINE];
    char *args[MAX_ARGS];
    int background;

    /* ignore Ctrl-C and Ctrl-\ like the book's shell */
    signal(SIGINT, SIG_IGN);
    signal(SIGQUIT, SIG_IGN);

    while (1)
    {
        /* check for finished background jobs */
        check_background();

        /* prompt and read */
        printf(PROMPT);
        fflush(stdout);

        if (fgets(line, MAX_LINE, stdin) == NULL)
        {
            printf("\n");
            break;
        }

        /* remove newline */
        line[strcspn(line, "\n")] = '\0';

        /* skip empty lines */
        if (strlen(line) == 0)
            continue;

        /* parse the line */
        if (parse_line(line, args, &background) == 0)
            continue;

        /* try built-in commands first */
        if (do_builtin(args))
            continue;

        /* run external command */
        run_command(args, background);
    }

    return 0;
}

/* split line into args, set background flag if line ends with & */
int parse_line(char *line, char **args, int *background)
{
    int i = 0;
    char *token;

    *background = 0;

    /* check for & at end */
    int len = strlen(line);
    while (len > 0 && line[len - 1] == ' ')
    {
        line[len - 1] = '\0';
        len--;
    }
    if (len > 0 && line[len - 1] == '&')
    {
        *background = 1;
        line[len - 1] = '\0';
    }

    token = strtok(line, " \t");
    while (token != NULL && i < MAX_ARGS - 1)
    {
        args[i++] = token;
        token = strtok(NULL, " \t");
    }
    args[i] = NULL;

    return i;
}

/* handle built-in commands, return 1 if handled */
int do_builtin(char **args)
{
    /* exit [value] */
    if (strcmp(args[0], "exit") == 0)
    {
        int code = 0;
        if (args[1] != NULL)
            code = atoi(args[1]);
        exit(code);
    }

    /* cd [dir] */
    if (strcmp(args[0], "cd") == 0)
    {
        char *dir;
        if (args[1] == NULL)
            dir = getenv("HOME");
        else
            dir = args[1];

        if (chdir(dir) != 0)
            perror("cd");

        return 1;
    }

    return 0;
}

/* fork and exec the command */
void run_command(char **args, int background)
{
    pid_t pid;
    int status;

    pid = fork();

    if (pid < 0)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        /* child - restore signals so commands can be killed */
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);

        execvp(args[0], args);
        perror(args[0]);
        exit(1);
    }

    /* parent */
    if (background)
    {
        printf("[background] started PID %d\n", pid);
    }
    else
    {
        waitpid(pid, &status, 0);
    }
}

/* check for finished background jobs */
void check_background(void)
{
    pid_t pid;
    int status;

    while ((pid = waitpid(-1, &status, WNOHANG)) > 0)
    {
        printf("[background] finished PID %d\n", pid);
    }
}
