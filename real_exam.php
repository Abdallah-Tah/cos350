# COS 350 - Predicted Final Exams (Practice)

**Author:** Abdallah Mohamed
**Based on:** the professor's Practice-Final-S26, lecture 26 review, all my experiments (e2-e22) and projects (prog1-prog6).

These are 3 full-length predicted exams in the same format and same 10 topic areas as the professor's practice. Each one varies the specific values so I can practice fresh.

For each exam:

1. Cover the **Answer** lines.
2. Try to write the answer on paper.
3. Compare.

The 10 topic areas (each exam covers all of them):
A. Bitwise Operations
B. C Pointers and Memory
C. argc / argv and String Handling
D. Process Control and wait
E. Unix I/O Redirection with System Calls
F. Pipes
G. Signals
H. Unix Commands and the Shell
I. make and Compilation
J. Threads and Synchronization

---
---

# PREDICTED EXAM 1

## A. Bitwise Operations

You are packing a small "header byte" used in a network protocol. You have:

```c
unsigned int header = 0;
```

Three fields (LSB first):

| Field | Value | Bits |
|------|-------|------|
| version | 0x3 | 2 |
| type    | 0x6 | 4 |
| flag    | 0x1 | 1 |

**Q1.** Pack all three into `header`.

**Answer.**
```c
unsigned int header = 0;
header  = version;
header |= type << 2;
header |= flag << (2 + 4);
```

**Q2.** Given a packed `header`, extract `type` back out.

**Answer.**
```c
unsigned int t = (header >> 2) & ((1 << 4) - 1);   // mask = 0xF
```

**Q3.** Clear bit 5 of `x` without changing any other bit.

**Answer.** `x = x & ~(1 << 5);`

---

## B. C Pointers and Memory

Consider:

```c
int *table[3];
int  vals[] = {10, 20, 30, 40};
```

**Q1.** What is the difference between `int *table[3]` and `int (*table)[3]`?

**Answer.**
- `int *table[3]` = an array of 3 pointers to int.
- `int (*table)[3]` = a pointer to an array of 3 ints.

**Q2.** After `table[0] = vals;`, what is `table[0][2]`?

**Answer.** `30` (vals[2]).

**Q3.** Make `table[1]` point to its own malloc'd copy of three ints `{1, 2, 3}`.

**Answer.**
```c
table[1] = malloc(3 * sizeof(int));
table[1][0] = 1;
table[1][1] = 2;
table[1][2] = 3;
```

**Q4.** Why is `+ 1` important when allocating space for a string?

**Answer.** For the terminating `'\0'`. Without it, library functions read past the end and produce wrong output or crash.

---

## C. argc / argv and String Handling

A program is invoked as:

```
./mycopy -v -r "my folder" /tmp/dest
```

**Q1.** Values of argc and each argv element?

**Answer.**
- argc = 5
- argv[0] = `./mycopy`
- argv[1] = `-v`
- argv[2] = `-r`
- argv[3] = `my folder`   (one element because of quotes)
- argv[4] = `/tmp/dest`
- argv[5] = NULL

**Q2.** Why is `if (argv[1] == "-v")` wrong? Show the right way.

**Answer.** `==` compares pointer addresses, not characters. The right way:

```c
if (strcmp(argv[1], "-v") == 0) { ... }
```

**Q3.** Show how to copy the string in `argv[3]` into a new heap buffer.

**Answer.**
```c
char *copy = malloc(strlen(argv[3]) + 1);
strcpy(copy, argv[3]);
```

---

## D. Process Control and wait

```c
pid_t pid = fork();
if (pid == 0) {
    execvp("grep", (char *[]){"grep", "error", "log.txt", NULL});
    perror("exec failed");
    exit(1);
}
int status;
waitpid(pid, &status, 0);
```

**Q1.** Using WIFEXITED, WEXITSTATUS, WIFSIGNALED, WTERMSIG, write code that prints either the exit status or the terminating signal.

**Answer.**
```c
if (WIFEXITED(status))
    printf("child exited with %d\n", WEXITSTATUS(status));
else if (WIFSIGNALED(status))
    printf("child killed by signal %d\n", WTERMSIG(status));
```

**Q2.** Why is `perror` + `exit(1)` after `execvp` important?

**Answer.** If `execvp` succeeds, the lines after it never run because the process is replaced. If `execvp` fails (bad path, no permission), the lines after still execute — `perror` reports the error and `exit(1)` kills the failed child cleanly so the parent can detect failure via `wait`.

**Q3.** What is a zombie process? When does it happen?

**Answer.** A process that has finished running but whose parent has not called `wait` yet. The exit status is still in the kernel's process table, waiting to be collected.

**Q4.** What happens if the parent dies before the child?

**Answer.** The child becomes an **orphan** and is adopted by `init` (PID 1), which will reap it.

---

## E. Unix I/O Redirection with System Calls

A shell needs to execute:

```
wc -l < log.txt > count.out
```

**Q1.** List, in order, the system calls (after fork, in the child) to set up the redirections and run `wc`.

**Answer.**
```c
int in = open("log.txt", O_RDONLY);
dup2(in, STDIN_FILENO);
close(in);

int out = open("count.out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
dup2(out, STDOUT_FILENO);
close(out);

execlp("wc", "wc", "-l", NULL);
perror("exec wc failed");
exit(1);
```

**Q2.** Why must `in` and `out` be closed after `dup2`?

**Answer.** After `dup2`, fd 0 and fd 1 already point to the same file. The original `in` and `out` descriptors are duplicates — leaving them open leaks file descriptors and can keep the file open longer than expected.

**Q3.** What flag would you change to make this `>>` (append) instead of `>` (overwrite)?

**Answer.** Replace `O_TRUNC` with `O_APPEND`. `O_APPEND` makes every write seek to the end of the file atomically.

---

## F. Pipes

A shell needs to execute:

```
ls -l | grep "txt" | wc -l
```

**Q1.** How many calls to `pipe()` and how many to `fork()`?

**Answer.** 2 pipes, 3 forks.

**Q2.** Describe what each child does with the pipe ends.

**Answer.**
- pipe1 connects ls → grep
- pipe2 connects grep → wc

```
ls -l:    dup write end of pipe1 onto stdout
          close BOTH ends of BOTH pipes (the unused ends)
          exec ls

grep:     dup read end of pipe1 onto stdin
          dup write end of pipe2 onto stdout
          close BOTH ends of BOTH pipes (the unused ends)
          exec grep

wc -l:    dup read end of pipe2 onto stdin
          close BOTH ends of BOTH pipes (the unused ends)
          exec wc
```

**Q3.** What happens if the writing end of a pipe is never closed in the reader?

**Answer.** The reader never sees EOF. `wc -l` keeps waiting because the kernel believes more data could still arrive — the program hangs forever.

---

## G. Signals

**Q1.** A program needs to ignore SIGINT (Ctrl-C) so it cannot be killed by the keyboard. Show the code.

**Answer.**
```c
signal(SIGINT, SIG_IGN);
```

**Q2.** Write a short program that prints "tick" every second using a SIGALRM handler and `setitimer`. Show the timer setup.

**Answer.**
```c
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void handler(int sig) { printf("tick\n"); }

int main(void) {
    signal(SIGALRM, handler);

    struct itimerval iv;
    iv.it_value.tv_sec = 1;  iv.it_value.tv_usec = 0;
    iv.it_interval     = iv.it_value;
    setitimer(ITIMER_REAL, &iv, NULL);

    while (1) pause();
}
```

**Q3.** Why can SIGKILL not be caught or ignored?

**Answer.** It is a system-design guarantee. The OS keeps SIGKILL (and SIGSTOP) uncatchable so it always has a way to terminate or stop a misbehaving process — even one that tried to ignore everything else.

**Q4.** Give one capability `sigaction()` provides that `signal()` does not.

**Answer.** `sigaction()` can set `SA_RESTART` to auto-restart interrupted system calls (or block other signals during the handler, or use `SA_SIGINFO` for extra signal info).

---

## H. Unix Commands and the Shell

**Q1.** Give a single shell pipeline that prints how many lines in `*.txt` files in the current directory contain the word "TODO".

**Answer.**
```sh
grep -c TODO *.txt | awk -F: '{s+=$2} END {print s}'
```
(Or simpler: `grep TODO *.txt | wc -l`.)

**Q2.** Difference between Ctrl-C and Ctrl-Z.

**Answer.** Ctrl-C sends SIGINT (default = terminate). Ctrl-Z sends SIGTSTP (default = stop / suspend the foreground process; can be resumed with `fg`).

**Q3.** You have a script `clean.sh` that says `Permission denied`. Two ways to run it.

**Answer.**
```sh
bash clean.sh
# or
chmod +x clean.sh && ./clean.sh
```

**Q4.** What does `chmod 644 file` give?

**Answer.** Owner: rw-, group: r--, others: r-- (no execute for anyone).

---

## I. make and Compilation

```make
prog: a.o b.o c.o
	gcc -o prog a.o b.o c.o

a.o: a.c shared.h
	gcc -c a.c

b.o: b.c shared.h
	gcc -c b.c

c.o: c.c
	gcc -c c.c
```

**Q1.** If you change `shared.h`, which targets get rebuilt?

**Answer.** `a.o` and `b.o` (both depend on `shared.h`), and then `prog` (because both `.o`s changed). `c.o` is NOT rebuilt because it does not depend on `shared.h`.

**Q2.** How does `make` decide if a target needs rebuilding?

**Answer.** It compares timestamps. Rebuild if the target does not exist OR if any dependency has a newer modified time than the target.

**Q3.** Everything is up to date. You run `touch a.c`, then `make`. What gets recompiled?

**Answer.** `a.o` (a.c is newer) and `prog` (a.o is newer than prog).

---

## J. Threads and Synchronization

```c
int total = 0;
void *worker(void *arg) {
    for (int i = 0; i < 500000; i++)
        total += 2;
    return NULL;
}
```

**Q1.** Two threads run `worker`. Will `total` reliably equal 2,000,000? Why or why not?

**Answer.** No. `total += 2` is read → add → write, not atomic. Two threads can read the same value, both add 2, and both write the same result back, losing one update. The final value will usually be less than 2,000,000.

**Q2.** Fix the code with a pthread mutex.

**Answer.**
```c
#include <pthread.h>
int total = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *worker(void *arg) {
    for (int i = 0; i < 500000; i++) {
        pthread_mutex_lock(&lock);
        total += 2;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
```

**Q3.** Why do threads need mutexes but separate processes (with separate address spaces) typically do not?

**Answer.** Threads share the same address space — same globals, same heap. Without a lock, they step on each other's data. Processes have separate address spaces, so each one's normal variables are private and need no lock to be safe.

---
---

# PREDICTED EXAM 2

## A. Bitwise Operations

You're packing a small instruction word:

| Field | Value | Bits |
|------|-------|------|
| opcode | 0x9 | 4 |
| reg    | 0x3 | 3 |
| imm    | 0x1F | 5 |

(LSB first: opcode at bottom, then reg, then imm.)

**Q1.** Pack all three into `unsigned int instr`.

**Answer.**
```c
unsigned int instr = 0;
instr  = opcode;
instr |= reg << 4;
instr |= imm << (4 + 3);
```

**Q2.** Toggle bit 0 of `x`.

**Answer.** `x = x ^ 1;`

**Q3.** Test if bit 7 of `x` is set.

**Answer.** `if (x & (1 << 7)) { ... }`

---

## B. C Pointers and Memory

```c
char *names[5];
char  greeting[] = "welcome";
```

**Q1.** Difference between `names` and `greeting` types?

**Answer.**
- `names` is an array of 5 pointers to char.
- `greeting` is an array of 8 chars (`'w','e','l','c','o','m','e','\0'`).

**Q2.** After `names[0] = greeting;`, what is `names[0][4]`?

**Answer.** `'o'` (w-e-l-c-o → indices 0,1,2,3,4).

**Q3.** Allocate an independent copy of "goodbye" into `names[1]`.

**Answer.**
```c
names[1] = malloc(strlen("goodbye") + 1);
strcpy(names[1], "goodbye");
```

**Q4.** Free that copy.

**Answer.** `free(names[1]);`

---

## C. argc / argv and String Handling

A program is invoked as:

```
./parse --output "my file.txt" --count 5
```

**Q1.** argc and argv?

**Answer.**
- argc = 6
- argv[0] = `./parse`
- argv[1] = `--output`
- argv[2] = `my file.txt`
- argv[3] = `--count`
- argv[4] = `5`
- argv[5] = NULL

**Q2.** How would you convert `argv[4]` into an integer?

**Answer.** `int n = atoi(argv[4]);`

**Q3.** Why use `strcmp` instead of `==` to test argv values?

**Answer.** `==` compares pointer addresses. Each string lives at a different address even if the contents are equal. `strcmp` compares the actual characters and returns 0 when they match.

---

## D. Process Control and wait

**Q1.** Write a short program that forks one child, the child runs `date`, the parent waits and prints whether the child exited normally and with what status.

**Answer.**
```c
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
    pid_t pid = fork();
    if (pid == 0) {
        execlp("date", "date", NULL);
        perror("exec date");
        exit(1);
    }

    int status;
    wait(&status);
    if (WIFEXITED(status))
        printf("date exited normally, status %d\n", WEXITSTATUS(status));
    else if (WIFSIGNALED(status))
        printf("date killed by signal %d\n", WTERMSIG(status));
    return 0;
}
```

**Q2.** What is the difference between `wait()` and `waitpid()`?

**Answer.** `wait()` waits for any child to finish. `waitpid(pid, &status, options)` lets you wait for a specific child, and with `WNOHANG` it returns immediately if no child has died yet (useful in shells for cleaning up background jobs).

**Q3.** What does `WNOHANG` do?

**Answer.** Makes `waitpid` non-blocking. If no child has exited yet, it returns 0 instead of waiting. Used in shell loops to reap finished background jobs without blocking.

---

## E. Unix I/O Redirection with System Calls

**Q1.** Translate this shell command into a fork + exec + redirection in C: `cat file.txt >> log.txt 2>&1`

**Answer.**
```c
pid_t pid = fork();
if (pid == 0) {
    int out = open("log.txt", O_WRONLY | O_CREAT | O_APPEND, 0644);
    dup2(out, STDOUT_FILENO);
    dup2(out, STDERR_FILENO);          // 2>&1
    close(out);

    execlp("cat", "cat", "file.txt", NULL);
    perror("exec cat");
    exit(1);
}
wait(NULL);
```

**Q2.** Explain `O_APPEND` vs `O_TRUNC`.

**Answer.**
- `O_TRUNC`: when opening for write, truncate the file to length 0 first (overwrite).
- `O_APPEND`: every write seeks to the end of the file first, atomically. Two processes appending at the same time will not overwrite each other.

**Q3.** What does `dup2(out, 2)` do?

**Answer.** Closes fd 2 (stderr) if open, then makes fd 2 refer to the same open file as `out`. Now anything written to stderr goes to that file.

---

## F. Pipes

**Q1.** Write the C code that runs `who | sort` using `pipe`, `fork`, and `dup2`.

**Answer.**
```c
int pfd[2];
pipe(pfd);

if (fork() == 0) {                 // who
    dup2(pfd[1], STDOUT_FILENO);
    close(pfd[0]); close(pfd[1]);
    execlp("who", "who", NULL);
    perror("exec who"); exit(1);
}

if (fork() == 0) {                 // sort
    dup2(pfd[0], STDIN_FILENO);
    close(pfd[0]); close(pfd[1]);
    execlp("sort", "sort", NULL);
    perror("exec sort"); exit(1);
}

close(pfd[0]); close(pfd[1]);     // parent must close BOTH ends too
wait(NULL); wait(NULL);
```

**Q2.** Why must the parent close BOTH ends of the pipe?

**Answer.** If the parent keeps the write end open, the reader (`sort`) will never see EOF and will hang forever. Each process that doesn't use a pipe end must close it.

**Q3.** What's the difference between a pipe and a FIFO (named pipe)?

**Answer.** A pipe (from `pipe()`) is anonymous — only related processes (parent and child) can use it. A FIFO is a pipe that has a name on the filesystem (made with `mkfifo`), so unrelated processes can open it by path.

---

## G. Signals

**Q1.** Write a handler that catches SIGINT and prints "interrupt received", but does NOT exit. The program should keep running.

**Answer.**
```c
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void on_int(int sig) {
    write(1, "interrupt received\n", 19);
}

int main(void) {
    signal(SIGINT, on_int);
    while (1) pause();
}
```
(I used `write` because `printf` is not async-signal-safe in a strict program.)

**Q2.** What does `pause()` do?

**Answer.** Blocks the calling process until any signal is delivered. It always returns -1 with `errno = EINTR`.

**Q3.** A timer set up with `setitimer(ITIMER_REAL, ...)` delivers which signal?

**Answer.** `SIGALRM`.

**Q4.** What is the difference between blocking a signal and ignoring it?

**Answer.**
- **Block** (sigprocmask): the signal is held pending. When you unblock it, it is delivered.
- **Ignore** (signal() with SIG_IGN): the signal is thrown away. It is never delivered.

---

## H. Unix Commands and the Shell

**Q1.** Give a single shell pipeline that prints the 5 largest files (in bytes) in the current directory tree.

**Answer.**
```sh
find . -type f -printf "%s %p\n" | sort -nr | head -5
```

**Q2.** What is the output of `ls -l` for a symbolic link, and how does it differ from a hard link?

**Answer.** A symbolic link shows up as `lrwxrwxrwx ... link -> target`. A hard link is just another directory entry pointing to the same inode — `ls -l` doesn't distinguish hard links from regular files except by the `nlink` count.

**Q3.** Difference between `>`, `>>`, and `2>`?

**Answer.**
- `>` redirect stdout, truncating the file.
- `>>` redirect stdout, appending.
- `2>` redirect stderr (file descriptor 2).

**Q4.** What does `kill -9 PID` do that `kill PID` does not?

**Answer.** `kill PID` (default SIGTERM) asks the process to terminate cleanly. The process can catch SIGTERM and clean up. `kill -9 PID` sends SIGKILL, which cannot be caught — the kernel kills the process immediately.

---

## I. make and Compilation

```make
CC = gcc
CFLAGS = -Wall -g

server: server.o net.o
	$(CC) $(CFLAGS) -o server server.o net.o

server.o: server.c net.h
	$(CC) $(CFLAGS) -c server.c

net.o: net.c net.h
	$(CC) $(CFLAGS) -c net.c

clean:
	rm -f *.o server
```

**Q1.** What does the `clean:` target do, and why is it useful?

**Answer.** Removes all `.o` files and the executable. Useful when you want to force a full rebuild from scratch (`make clean && make`).

**Q2.** What does `$(CC)` do?

**Answer.** Variable expansion. `make` substitutes the value of `CC` (here, `gcc`) wherever `$(CC)` appears.

**Q3.** Modify only `net.h`. What gets rebuilt?

**Answer.** `server.o` and `net.o` (both depend on `net.h`), then `server` (because both .o files are newer).

**Q4.** What if `clean:` had no body? Would it still work?

**Answer.** No — `make clean` would just say "Nothing to be done for `clean`." A target with no recipe does nothing.

---

## J. Threads and Synchronization

**Q1.** Write a producer-consumer style snippet using a mutex and a condition variable. (Producer adds to a count, consumer waits for count > 0.)

**Answer.**
```c
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t  cv   = PTHREAD_COND_INITIALIZER;
int count = 0;

void *producer(void *arg) {
    pthread_mutex_lock(&lock);
    count++;
    pthread_cond_signal(&cv);
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *consumer(void *arg) {
    pthread_mutex_lock(&lock);
    while (count == 0)
        pthread_cond_wait(&cv, &lock);
    count--;
    pthread_mutex_unlock(&lock);
    return NULL;
}
```

**Q2.** Why do we use `while (count == 0)` and not `if (count == 0)`?

**Answer.** Because of spurious wake-ups. `pthread_cond_wait` can return without a signal in rare cases. The `while` loop re-checks the condition and waits again if needed.

**Q3.** What does `pthread_cond_wait` do internally with the mutex?

**Answer.** It atomically releases the mutex and goes to sleep. When signaled, it re-acquires the mutex before returning. This avoids race conditions between releasing the mutex and waiting.

---
---

# PREDICTED EXAM 3

## A. Bitwise Operations

You receive an RGBA color value `0xRRGGBBAA` packed into one `unsigned int color`. Each channel is 8 bits.

**Q1.** Extract the red channel.

**Answer.**
```c
unsigned int red = (color >> 24) & 0xFF;
```

**Q2.** Extract green and blue similarly.

**Answer.**
```c
unsigned int green = (color >> 16) & 0xFF;
unsigned int blue  = (color >>  8) & 0xFF;
unsigned int alpha = color & 0xFF;
```

**Q3.** Build an RGBA value from 4 separate channels.

**Answer.**
```c
unsigned int color = (red << 24) | (green << 16) | (blue << 8) | alpha;
```

---

## B. C Pointers and Memory

```c
int  ages[]  = {21, 22, 23, 24};
int *p       = ages;
```

**Q1.** What is `*(p + 2)`?

**Answer.** `23` (same as `ages[2]`).

**Q2.** What is `p[3]`?

**Answer.** `24` (same as `*(p + 3)`).

**Q3.** Walk through what `*p++` does in `int x = *p++;`.

**Answer.** Postfix `++` binds tighter than `*`. So `*p++` means "dereference p (get `ages[0]` = 21), then advance p". After this line, `x == 21` and `p` points at `ages[1]`.

**Q4.** What is the difference between `int *p` and `int p[]` as a function parameter?

**Answer.** They are exactly the same. C decays array parameters to pointers — `void f(int p[])` is identical to `void f(int *p)`.

---

## C. argc / argv and String Handling

A program is invoked as:

```
./tool -x abc -y "hello there" file1 file2
```

**Q1.** argc?

**Answer.** 7

**Q2.** Which argv element holds `"hello there"`?

**Answer.** `argv[4]` (the quotes group it into one element).

**Q3.** Loop through every command-line argument and print it on its own line.

**Answer.**
```c
for (int i = 0; i < argc; i++)
    printf("%d: %s\n", i, argv[i]);
```

---

## D. Process Control and wait

**Q1.** What is the difference between `fork()` and `exec()`? Can a program use one without the other?

**Answer.**
- `fork()` creates a copy of the current process. Both processes return from `fork()` and run the same code afterwards.
- `exec()` replaces the current process's program with a new one. PID stays the same; everything else (code, stack, heap) is replaced.

Yes — you can fork without exec (just to do parallel work), and you can exec without fork (replace yourself with another program).

**Q2.** Predict the output of:
```c
fork();
fork();
printf("hi\n");
```

**Answer.** "hi" prints **4 times**. The first fork makes 2 processes, the second fork makes each one fork again → 4 processes total.

**Q3.** Why must shells call `wait` (or `waitpid`) on their children?

**Answer.** To collect the exit status and let the kernel clean up the child's process table entry. Without `wait`, dead children become zombies.

---

## E. Unix I/O Redirection with System Calls

**Q1.** What is `dup2(fd, 1)` doing precisely?

**Answer.** Closes fd 1 (stdout) if it is open, then makes fd 1 refer to the same underlying file/pipe/device as `fd`. After this, writing to stdout writes to whatever `fd` was opened on.

**Q2.** A program does:
```c
int fd = open("out.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
dup2(fd, 1);
close(fd);
printf("hello\n");
```
Where does "hello" go and why?

**Answer.** Into `out.txt`. After `dup2(fd, 1)`, fd 1 (stdout) refers to `out.txt`, and `printf` writes to stdout. The original `fd` is closed but stdout still points to the same open file in the kernel.

**Q3.** If you forget to `close(fd)` after `dup2`, what happens?

**Answer.** The original `fd` stays open. It is wasted (a leak) and the file may stay open longer than expected. Functionally, output still goes to the right place.

---

## F. Pipes

**Q1.** What do the two file descriptors returned by `pipe(int pipefd[2])` mean?

**Answer.**
- `pipefd[0]` — read end
- `pipefd[1]` — write end

**Q2.** What does `read(pipefd[0], buf, n)` return when the writer has closed the write end and the buffer is empty?

**Answer.** It returns 0 — that is the EOF indicator on a pipe.

**Q3.** What does `write` return if you try to write to a pipe whose read end has been closed?

**Answer.** It fails with `EPIPE`, and the kernel sends `SIGPIPE` to the writer (default action: terminate). To avoid being killed, you can ignore SIGPIPE: `signal(SIGPIPE, SIG_IGN);`

**Q4.** Why is data flow through a pipe limited in size? What is the size?

**Answer.** Pipes have a kernel buffer (typically 64 KB on Linux). When it fills, writers block until the reader drains it. This provides flow control between the two processes.

---

## G. Signals

**Q1.** A user program installs a handler for SIGINT. The user presses Ctrl-C. List the events from kernel to handler.

**Answer.**
1. The terminal driver sees Ctrl-C and sends SIGINT to the foreground process.
2. The kernel checks the process's signal disposition for SIGINT — finds the handler.
3. The kernel saves the user-mode register state and arranges to call the handler.
4. The handler runs.
5. When the handler returns, the kernel restores the saved state and resumes the interrupted code.

**Q2.** Suppose your program does:
```c
signal(SIGINT, h);
read(fd, buf, 100);
```
While `read` is blocked, the user presses Ctrl-C. What happens after the handler runs?

**Answer.** With plain `signal()`, `read` returns `-1` and sets `errno = EINTR` — the system call is interrupted and not restarted. With `sigaction()` and `SA_RESTART`, the kernel automatically restarts the `read`.

**Q3.** Explain `alarm(0)`.

**Answer.** Cancels any pending alarm. `alarm(N)` schedules a SIGALRM for N seconds; `alarm(0)` removes the schedule.

---

## H. Unix Commands and the Shell

**Q1.** Print only lines 10–20 of a file named `data.txt`.

**Answer.** `sed -n '10,20p' data.txt`  (or `head -20 data.txt | tail -11`).

**Q2.** Count how many users are currently logged in.

**Answer.** `who | wc -l`.

**Q3.** What is the difference between `find . -name "*.c"` and `find . -iname "*.c"`?

**Answer.** `-name` is case-sensitive. `-iname` is case-insensitive (matches `.C` and `.c`).

**Q4.** What does `&` at the end of a command line do?

**Answer.** Runs the command in the background. The shell does not wait for it; it returns to the prompt immediately and prints the new job's PID.

---

## I. make and Compilation

```make
all: hello

hello: hello.o util.o
	gcc -o hello hello.o util.o

hello.o: hello.c
	gcc -c hello.c

util.o: util.c util.h
	gcc -c util.c
```

**Q1.** Why is `all:` listed first?

**Answer.** Because `make` with no arguments builds the FIRST target in the file. Putting `all:` first makes `make` (no args) do the same thing as `make all`.

**Q2.** What is a phony target? Give an example.

**Answer.** A target with no associated file. `clean:` is phony. To declare it: `.PHONY: clean all`. Phony targets always run.

**Q3.** What does `gcc -c hello.c` do without `-o`?

**Answer.** Compiles `hello.c` and writes the object file to `hello.o` (default).

**Q4.** What does `gcc -Wall -g` mean?

**Answer.** `-Wall` turns on all common warnings. `-g` adds debugging information so you can use `gdb`.

---

## J. Threads and Synchronization

```c
int balance = 100;

void *deposit(void *arg) {
    int amount = *(int *)arg;
    int old = balance;
    usleep(1000);              // simulate slow processing
    balance = old + amount;
    return NULL;
}
```

**Q1.** Two threads both call `deposit(&fifty)` (each amount = 50). Will the final balance always be 200?

**Answer.** No. Both threads can read `old = 100`, sleep, and then both write back `100 + 50 = 150`. The final balance can be 150, losing one deposit. This is a classic race condition.

**Q2.** Fix it with a mutex held around the read-modify-write.

**Answer.**
```c
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *deposit(void *arg) {
    int amount = *(int *)arg;
    pthread_mutex_lock(&lock);
    int old = balance;
    usleep(1000);
    balance = old + amount;
    pthread_mutex_unlock(&lock);
    return NULL;
}
```

**Q3.** What is a deadlock? Give one way it can happen.

**Answer.** Two or more threads are stuck waiting for each other forever, holding resources the other one needs. Classic example:
- Thread A locks `m1`, then tries to lock `m2`.
- Thread B locks `m2`, then tries to lock `m1`.
- Each holds the lock the other wants → forever stuck.

**Avoidance:** always acquire locks in the SAME global order.

---
---

# Final tips before sitting the real exam

- **Always read the question twice.** Practice exam questions often hide one detail that changes the answer (e.g. quotes in argv, append vs truncate).
- **Always check `+1` for `\0`.**
- **Always close after `dup2`.**
- **Always close BOTH ends of EVERY pipe in EVERY child.**
- **Always have `perror` + `exit` after `exec`.**
- **Always reap children to avoid zombies.**
- **`==` vs `strcmp`. `make` = timestamps. SIGKILL/SIGSTOP uncatchable.**

Three full predicted exams above. If you can answer all 30 questions cold, you'll have no trouble with the real one.
