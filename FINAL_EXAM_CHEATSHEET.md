# COS 350 - Final Exam Cheat Sheet

**Name:** Abdallah Mohamed
**Date:** May 3, 2026

This sheet covers everything from the practice final + lecture 26 review + my projects/experiments. Topics are listed in the order the professor showed in the practice exam.

---

## 1. Bitwise Operations (bit packing)

**Operators**

| Op | Meaning | Common use |
|----|---------|-----------|
| `&` | bitwise AND | clear bits with a mask |
| `\|` | bitwise OR | set bits with a mask |
| `^` | bitwise XOR | toggle bits |
| `~` | ones complement | build masks |
| `<<` | shift left, fills 0 from bottom | move bits up |
| `>>` | shift right (sign bit copied on signed types) | move bits down |

**Pack 3 values into one buffer (LSB first):**

```c
unsigned int buffer = 0;
int totalBits = 0;

buffer  = val1;                          // val1 at the bottom
buffer |= val2 << bits1;                 // val2 above val1
buffer |= val3 << (bits1 + bits2);       // val3 on top

totalBits = bits1 + bits2 + bits3;
```

**Unpack:**
```c
unsigned int mask = (1 << bits1) - 1;
unsigned int v1 = buffer & mask;
unsigned int v2 = (buffer >> bits1) & ((1 << bits2) - 1);
unsigned int v3 = (buffer >> (bits1 + bits2)) & ((1 << bits3) - 1);
```

---

## 2. C Pointers and Memory

```c
char *words[4];        // array of 4 pointers to char
char (*words)[4];      // pointer to an array of 4 chars
char buf[] = "hello world";
```

**Indexing:** after `words[0] = buf;`, `words[0][3]` = `'l'` (h e l l o → 0 1 2 3 4)

**Independent copy with malloc:**
```c
words[1] = malloc(strlen("goodbye") + 1);   // +1 for the '\0'
strcpy(words[1], "goodbye");
```

**Always remember:** `+ 1` for the terminating `\0`. Free what you malloc.

---

## 3. argc / argv

Command:
```
./mygrep -i -n "hello world" data.txt
```

| index | argv |
|------|------|
| 0 | `./mygrep` |
| 1 | `-i` |
| 2 | `-n` |
| 3 | `hello world` (one arg because of quotes) |
| 4 | `data.txt` |
| 5 | `NULL` |

`argc = 5`.

**Wrong:** `if (argv[1] == "-i")` — that compares pointer addresses, not characters.
**Right:**
```c
if (strcmp(argv[1], "-i") == 0) { ... }
```

---

## 4. Process Control: fork / exec / wait

**Pattern:**
```c
pid_t pid = fork();
if (pid == 0) {                          // child
    execlp("ls", "ls", "-l", NULL);
    perror("exec failed");               // only runs if exec fails
    exit(1);
}
int status;
wait(&status);
```

**Status macros:**
```c
if (WIFEXITED(status))
    printf("child exited with status %d\n", WEXITSTATUS(status));
else if (WIFSIGNALED(status))
    printf("child killed by signal %d\n", WTERMSIG(status));
```

- If `exec` succeeds, the child's program is replaced; lines after `exec` do not run.
- If `exec` fails, the lines after still run — that's why we put `perror` + `exit`.
- If parent never calls `wait`, the dead child becomes a **zombie** (still in process table, exit status not collected).
- If parent dies first, child becomes an **orphan** and is adopted by `init`.

**exec family:**
- `execlp("ls", "ls", "-l", NULL)` — list of args, search PATH
- `execvp("ls", argv)` — vector of args, search PATH

---

## 5. I/O Redirection with System Calls

To run `sort < input.txt > output.txt`:

```c
int in = open("input.txt", O_RDONLY);
dup2(in, STDIN_FILENO);
close(in);

int out = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
dup2(out, STDOUT_FILENO);
close(out);

execlp("sort", "sort", NULL);
perror("exec sort failed");
exit(1);
```

**Why close after dup2?** stdin / stdout already point to the file. The original fd from open is not needed and would leak.

**Append mode (`>>`)** uses `O_APPEND` — seek-to-end and write are one atomic step, so two writers can't overwrite each other (this is what experiment 22 tested).

---

## 6. Pipes

For `cat file.txt | grep "error" | wc -l`:

- **2 calls** to `pipe()`
- **3 calls** to `fork()`

```
pipe1: cat  -> grep
pipe2: grep -> wc
```

Each child:
- dups its end of the pipe to STDIN or STDOUT
- closes BOTH ends of EVERY pipe (the unused ones)
- exec's its command

**If a write end stays open in the reader,** the reader never sees EOF (e.g. `wc -l` hangs forever).

---

## 7. Signals

**signal vs sigaction:**
- `signal()` is the old, simple way.
- `sigaction()` is reliable, gives more control:
  - `SA_RESTART` — auto-restart interrupted system calls
  - block other signals while handler runs
  - `SA_SIGINFO` for extra info about the signal

**Alarm + pause:**
```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) { printf("alarm received\n"); }

int main(void) {
    signal(SIGALRM, handler);
    alarm(5);    // SIGALRM in 5 seconds
    pause();     // sleep until any signal
    printf("pause returned\n");
    return 0;
}
```

**SIGKILL (9) and SIGSTOP** — cannot be caught, ignored, or blocked. The OS keeps a guaranteed way to kill a process.

**Common signals:**

| Signal | Default | Notes |
|--------|---------|-------|
| SIGINT (2) | terminate | Ctrl-C |
| SIGQUIT (3) | core dump | Ctrl-\ |
| SIGKILL (9) | terminate | cannot be caught |
| SIGSEGV (11) | core dump | bad memory access |
| SIGALRM (14) | terminate | from `alarm()` / `setitimer()` |
| SIGTERM (15) | terminate | normal kill |
| SIGCHLD (17) | ignored | child died |
| SIGSTOP (19) | stop | cannot be caught |
| SIGTSTP (20) | stop | Ctrl-Z |

**Ignore / default:**
```c
signal(SIGINT, SIG_IGN);   // ignore
signal(SIGINT, SIG_DFL);   // back to default
```

---

## 8. Unix Commands and the Shell

**Count `.c` files under home:**
```sh
find ~ -name "*.c" | wc -l
```

**Ctrl-C vs Ctrl-Z:**
- Ctrl-C → `SIGINT` → terminate foreground process
- Ctrl-Z → `SIGTSTP` → stop / suspend foreground process

**`./script.sh: Permission denied`** — two fixes:
```sh
bash myscript.sh
# or
chmod +x myscript.sh && ./myscript.sh
```

**Other useful commands:**
- `ls -l`, `ls -a`, `ls -R`
- `ps`, `ps aux`, `kill -9 PID`
- `chmod +x file`, `chmod 755 file`
- `grep "pattern" file`, `grep -c`, `grep -i`
- `wc -l`, `wc -w`, `wc -c`
- `find DIR -name "*.c"`
- `diff file1 file2`, `sdiff -t file1 file2`
- `tar -cvf archive.tar dir/`, `tar -xvf archive.tar`, `tar -tvf archive.tar`
- `gzip file`, `gunzip file.gz`

---

## 9. make / Compilation

```make
myapp: main.o utils.o
	gcc -o myapp main.o utils.o

main.o: main.c defs.h
	gcc -c main.c

utils.o: utils.c defs.h
	gcc -c utils.c
```

- **Modify only `defs.h`:** rebuilds `main.o`, `utils.o`, `myapp` (both .o's depend on `defs.h`, and `myapp` depends on the .o's).
- **How make decides:** compares **timestamps**. A target is rebuilt if it does not exist OR any dependency is newer than it.
- **`touch utils.c` then `make`:** rebuilds `utils.o` and `myapp`.

---

## 10. Threads and Synchronization

**Race condition:**
```c
int counter = 0;
void *increment(void *arg) {
    for (int i = 0; i < 1000000; i++) counter++;
    return NULL;
}
```
Two threads will NOT reliably get 2,000,000 because `counter++` is `read → add → write` and threads can interleave and lose updates.

**Fix with mutex:**
```c
#include <pthread.h>

int counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *increment(void *arg) {
    for (int i = 0; i < 1000000; i++) {
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}
```

**Why threads need locks but processes usually don't:** threads share the same address space (same global variables, same heap). Separate processes have separate address spaces, so each one's normals are private.

**Pthread API:**
```c
pthread_create(&tid, NULL, fn, arg);
pthread_join(tid, &retval);
pthread_exit(retval);
```

**Condition variables:**
```c
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_cond_wait(&cond, &mutex);    // releases mutex, waits, re-locks
pthread_cond_signal(&cond);
```

---

## 11. Strings Library (cheat list)

```c
int   strlen(char *s);
int   strcmp(char *s1, char *s2);
char *strcpy(char *dst, char *src);     // dst must have space!
char *strcat(char *dst, char *src);
char *strdup(char *s);                   // malloc + strcpy in one
char *strtok(char *s, char *delims);
int   atoi(char *s);
sprintf(buf, "%d %s", n, s);
```

Always allocate `strlen + 1` for the `\0`.

---

## 12. malloc / free

```c
char *buf = malloc(strlen(s1) + strlen(s2) + 1);
int  *arr = malloc(n * sizeof(int));
struct list *node = malloc(sizeof(struct list));

free(buf); free(arr); free(node);
```

`malloc` returns `NULL` on failure — check it for safety.

---

## 13. File I/O

**Unbuffered (system calls, fd is an int):**
```c
int open(char *path, int flags);              // O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC, O_APPEND
int creat(char *path, mode_t mode);
ssize_t read(int fd, void *buf, size_t n);
ssize_t write(int fd, void *buf, size_t n);
off_t lseek(int fd, off_t off, int whence);   // SEEK_SET, SEEK_CUR, SEEK_END
int close(int fd);
```

**Buffered (stdio, FILE *):**
```c
FILE *fopen(char *path, char *mode);          // "r","w","a","r+","w+","a+"
int   fgetc(FILE *);
char *fgets(char *s, int n, FILE *);
int   fscanf(FILE *, char *fmt, ...);
int   fputc(int c, FILE *);
int   fputs(char *s, FILE *);
int   fprintf(FILE *, char *fmt, ...);
int   fflush(FILE *);
int   fclose(FILE *);
```

**Standard streams / fds:**
- `stdin`/0, `stdout`/1, `stderr`/2
- constants: `STDIN_FILENO`, `STDOUT_FILENO`, `STDERR_FILENO`

---

## 14. Directories and stat

```c
DIR *opendir(char *name);
struct dirent *readdir(DIR *dirp);   // d_name, d_ino
int closedir(DIR *dirp);

int scandir(char *dir, struct dirent ***list, int (*filter)(), int (*cmp)());

int mkdir(char *path, mode_t mode);
int rmdir(char *path);
int link(char *old, char *new);       // hard link
int unlink(char *path);
int symlink(char *old, char *new);    // soft link
int rename(char *old, char *new);
int chdir(char *path);
char *getcwd(char *buf, size_t size);

int stat(char *path, struct stat *buf);    // follows symlinks
int lstat(char *path, struct stat *buf);   // does NOT follow symlinks
```

`struct stat` highlights: `st_size`, `st_mode`, `st_mtime`, `st_uid`, `st_nlink`, `st_ino`.

---

## 15. Time, Sleep, Timers

```c
gettimeofday(&tv, NULL);          // tv.tv_sec, tv.tv_usec
struct tm *t = localtime(&time_t_val);
char    *s = ctime(&time_t_val);

sleep(seconds);
usleep(microseconds);
nanosleep(&req, &rem);

alarm(seconds);                    // delivers SIGALRM

// repeating timer
struct itimerval it;
it.it_value.tv_sec = 0; it.it_value.tv_usec = 1000;       // first fire
it.it_interval.tv_sec = 0; it.it_interval.tv_usec = 1000; // each fire
setitimer(ITIMER_REAL, &it, NULL);

pause();                           // wait for any signal
```

(Experiment 15: a 1-ms `setitimer` averaged ~999 µs per tick on the school server.)

---

## 16. Terminal (raw mode)

```c
int fd = open("/dev/tty", O_RDWR);
struct termios t;
tcgetattr(fd, &t);
t.c_lflag &= ~(ICANON | ECHO);     // raw, no echo
tcsetattr(fd, TCSANOW, &t);
// ... read characters one at a time ...
tcsetattr(fd, TCSANOW, &original);  // restore on exit!
```

Window size: `ioctl(1, TIOCGWINSZ, &ws)` → `ws.ws_row`, `ws.ws_col`.

VT100 escapes used in scroll: `\033[H\033[J` clear, `\033[7m` reverse, `\033[1m` bold, `\033[4m` underline, `\033[0m` reset.

---

## 17. Reading C Type Declarations

**Rule:** declarations look like use.

| Declaration | Read as |
|-------------|---------|
| `int a;` | `a` is an int |
| `int *b;` | `*b` is an int → `b` is pointer to int |
| `int **c;` | `**c` is an int → pointer to pointer to int |
| `int d[50];` | `d[i]` is an int → array of 50 ints |
| `int (*fn)(int,int);` | `(*fn)(...)` is an int → pointer to function |

**Walk-out method (start at the name, follow precedence: `()` `[]` then `*`):**

```
int  *b[10];                // array of 10, pointer to int
int (*c)[10];               // pointer to array of 10 ints
int (*d[10])(char *argv[]); // array of 10 pointers to function (taking argv) returning int
void (*signal(int, void(*)(int)))(int);
                            // signal: function taking (int, ptr-to-fn-of-int-returning-void)
                            //         returning ptr-to-fn-of-int-returning-void
```

**Use typedef to simplify:**
```c
typedef void (*sighandler_t)(int);
sighandler_t signal(int sig, sighandler_t func);
```

---

## 18. Operator Precedence (top = highest)

```
() [] . -> expr++ expr--           left-to-right
* & + - ! ~ ++expr --expr (cast) sizeof   right-to-left
* / %
+ -
<< >>
< > <= >=
== !=
&
^
|
&&
||
?:                                  right-to-left
= += -= ...                         right-to-left
,                                   left-to-right
```

---

## 19. Quick-Glance Toolkit Commands (course commands at a glance)

| Tool | One-line use |
|------|--------------|
| `ls`, `ls -l`, `ls -a` | list files |
| `cd`, `pwd` | move / where am I |
| `cp`, `mv`, `rm`, `mkdir`, `rmdir` | files & dirs |
| `chmod +x f`, `chmod 755 f` | permissions |
| `cat`, `more`, `less`, `head`, `tail` | view files |
| `grep "pat" f` | search |
| `find DIR -name "*.c"` | find files |
| `wc -l/-w/-c` | count |
| `sort`, `uniq`, `cut`, `tr` | text tools |
| `diff a b`, `sdiff -t a b` | compare |
| `tar -cvf out.tar dir/`, `tar -xvf out.tar` | archive |
| `gzip f`, `gunzip f.gz` | compress |
| `ps`, `ps aux`, `kill -9 PID` | processes |
| `man N name` | manual page section N |
| `make`, `make clean` | build |
| `bash script.sh`, `./script.sh` | run scripts |

---

## 20. Last-Minute Reminders (the things that always trip me up)

- Always `+1` for the `\0` when allocating string buffers.
- `malloc` then check for `NULL` (and `free` later).
- After `dup2`, always `close` the original fd.
- Always close BOTH ends of EVERY pipe in EVERY child.
- After `exec`, always have `perror` + `exit` in case it fails.
- `wait` zombies — always reap children, otherwise process table fills up.
- `SIGKILL` and `SIGSTOP` cannot be caught.
- Threads share memory → need locks. Processes have separate memory → usually don't.
- `==` compares pointers, `strcmp` compares characters.
- `make` uses **timestamps**, not content.
- `>>` uses `O_APPEND` — atomic seek+write, so concurrent appends are safe.

Good luck on the exam!
