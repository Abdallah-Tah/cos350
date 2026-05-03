/* execute.c - code used by small shell to execute commands */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include "smsh.h"

int execute(char *argv[], int background)
/*
 * purpose: run a program passing it arguments
 * returns: status returned via wait, or -1 on error
 *  errors: -1 on fork() or waitpid() errors
 */
{
  pid_t	pid;
  int	child_info = -1;

  if ( argv[0] == NULL )		/* nothing succeeds	*/
    return 0;

  if ( (pid = fork())  == -1 )
    perror("fork");
  else if ( pid == 0 ){
    signal(SIGINT, SIG_DFL);
    signal(SIGQUIT, SIG_DFL);
    execvp(argv[0], argv);
    perror("cannot execute command");
    exit(1);
  }
  else {
    if ( background ){
      printf("[background] started PID %d\n", pid);
      return 0;
    }
    if ( waitpid(pid, &child_info, 0) == -1 )
      perror("waitpid");
  }
  return child_info;
}
