# COS 350 - Study & Memorize Sheet

**For studying at home before the exam.** Use this to learn the concepts. The crib sheet is for the exam itself.

Each section has the **notes** + **example Q&A** so you can practice the same way the professor asks.

---

## How to use this sheet

1. Read the notes for one section.
2. Cover the answers and try to write each example from memory.
3. Compare with the answer.
4. Move to the next section only when you can answer all questions cold.

---

## 1. Bitwise / Bit Packing

### Notes
- `&` AND — clear bits
- `|` OR — set bits
- `^` XOR — flip bits
- `~` NOT — build masks
- `<<` shift left, `>>` shift right
- Mask of N bits: `(1 << N) - 1`

### Q1. Pack val1=0x5 (3 bits), val2=0xF (4 bits), val3=0x2 (2 bits) into one buffer with val1 at the bottom.
**A.**
```c
unsigned int buffer = 0;
int totalBits = 0;

buffer  = val1;
buffer |= val2 << bits1;
buffer |= val3 << (bits1 + bits2);

totalBits = bits1 + bits2 + bits3;
```

### Q2. How do you unpack val2 from buffer?
**A.**
```c
unsigned int v2 = (buffer >> bits1) & ((1 << bits2) - 1);
```

### Q3. How do you clear the lowest 4 bits of x?
**A.** `x = x & ~0xF;`

### Q4. How do you turn ON bit 5 of x?
**A.** `x = x | (1 << 5);`

---

## 2. C Pointers and Memory

### Notes
| Code | Means |
|------|-------|
| `char *words[4]` | array of 4 pointers to char |
| `char (*words)[4]` | pointer to an array of 4 chars |
| `char buf[] = "hello"` | actual memory `'h','e','l','l','o','\0'` |

Strings need `+1` for `\0`. `==` compares addresses; use `strcmp` for content.

### Q1. What is the difference between `char *words[4]` and `char (*words)[4]`?
**A.**
- `char *words[4]` is an array of 4 pointers to char.
- `char (*words)[4]` is a pointer to an array of 4 chars.

### Q2. After `words[0] = buf;` where `buf[] = "hello world"`, what is `words[0][3]`?
**A.** `'l'` — because h(0) e(1) l(2) l(3) o(4)…

### Q3. Make `words[1]` point to its own independent copy of "goodbye".
**A.**
```c
words[1] = malloc(strlen("goodbye") + 1);
strcpy(words[1], "goodbye");
```

### Q4. Why is `+1` important?
**A.** For the terminating `\0` byte. Without it, library functions read past the end and you get garbage or crashes.

---

## 3. argc / argv

### Notes
Quotes group multiple words into ONE argv element. `argv[argc]` is always NULL.

### Q1. For `./mygrep -i -n "hello world" data.txt`, what are argc and argv?
**A.**
- argc = 5
- argv[0] = "./mygrep"
- argv[1] = "-i"
- argv[2] = "-n"
- argv[3] = "hello world"   ← one arg, quotes
- argv[4] = "data.txt"
- argv[5] = NULL

### Q2. Why is `if (argv[1] == "-i")` wrong?
**A.** `==` compares pointer addresses. `argv[1]` is in the program's stack/argv area; `"-i"` is a string literal somewhere else. Same letters, different addresses.

### Q3. Show the correct way.
**A.**
```c
if (strcmp(argv[1], "-i") == 0) { ... }
```

---

## 4. fork / exec / wait

### Notes
- `fork()` returns 0 in child, child's PID in parent, -1 on error.
- `exec` replaces the process image. If it succeeds, code after it never runs.
- `wait()` reaps a child's exit status.

### Q1. Write the fork/exec/wait pattern that runs `ls -l` and prints how the child ended.
**A.**
```c
pid_t pid = fork();
if (pid == 0) {
    execlp("ls", "ls", "-l", NULL);
    perror("exec failed");
    exit(1);
}
int status;
wait(&status);
if (WIFEXITED(status))
    printf("child exited with %d\n", WEXITSTATUS(status));
else if (WIFSIGNALED(status))
    printf("child killed by signal %d\n", WTERMSIG(status));
```

### Q2. Why is `perror` + `exit` after `execlp` important?
**A.** If exec succeeds, the lines after it never run. If exec fails (bad path, no permission), the child keeps running our parent code — that would be wrong. `perror` reports the error and `exit(1)` ends the child cleanly.

### Q3. What happens if the parent never calls wait?
**A.** The dead child becomes a **zombie** — it has finished, but its exit status sits in the process table because nobody collected it.

### Q4. What if the parent dies first?
**A.** The child becomes an **orphan** and is adopted by `init` (PID 1), which will eventually reap it.

### Q5. Difference between execlp and execvp?
**A.** `execlp` takes a list of arguments ending in NULL. `execvp` takes an argv vector. Both search PATH.

---

## 5. I/O Redirection (`<`, `>`, `>>`)

### Notes
After `dup2(fd, 0)`, fd 0 (stdin) refers to the same file as fd. The original fd should then be closed.

### Q1. Write the system calls (after fork, in the child) for `sort < input.txt > output.txt`.
**A.**
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

### Q2. Why must we close the original fd after dup2?
**A.** Stdin / stdout already point to the file. The original fd is duplicate work, leaks a descriptor, and may keep the file open longer than expected.

### Q3. Does `>>` use O_APPEND or seek+write?
**A.** It uses `O_APPEND`. The seek-to-end and write happen as ONE atomic step in the kernel, so two writers running at the same time both reach 1000+1000=2000 lines without overwriting each other (this is what experiment 22 tested).

---

## 6. Pipes

### Notes
A pipe gives you two fds: `pipefd[0]` is the read end, `pipefd[1]` is the write end. Children must close BOTH ends of EVERY pipe they don't use.

### Q1. For `cat file.txt | grep "error" | wc -l`, how many calls to `pipe()` and `fork()`?
**A.** 2 pipes, 3 forks.

### Q2. What does each child do with the pipe fds?
**A.**
- **cat**: dup write end of pipe1 onto stdout, close everything else, exec.
- **grep**: dup read end of pipe1 onto stdin, dup write end of pipe2 onto stdout, close everything else, exec.
- **wc**: dup read end of pipe2 onto stdin, close everything else, exec.

### Q3. What if the writing end of a pipe is never closed in the reader?
**A.** The reader never sees EOF. `wc -l` keeps waiting because the kernel thinks more data could still arrive, so it hangs forever.

---

## 7. Signals

### Notes
- `signal()` is simple but old.
- `sigaction()` is reliable: SA_RESTART, signal masks, SA_SIGINFO.
- SIGKILL (9) and SIGSTOP (19) cannot be caught, ignored, or blocked.

### Q1. One specific thing sigaction does that signal does not?
**A.** It can set `SA_RESTART` to auto-restart interrupted system calls. (Or: it can block other signals during the handler, or use SA_SIGINFO to get extra info.)

### Q2. Write a program that handles SIGALRM, calls alarm(5), then pause(). Walk through what happens.
**A.**
```c
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void handler(int sig) { printf("alarm received\n"); }

int main(void) {
    signal(SIGALRM, handler);
    alarm(5);
    pause();
    printf("pause returned\n");
    return 0;
}
```
Steps:
1. Install `handler` for SIGALRM.
2. Ask kernel to send SIGALRM in 5 seconds.
3. `pause()` blocks until any signal arrives.
4. After 5s, SIGALRM fires → `handler` runs → prints "alarm received".
5. `pause()` returns → final printf → exit.

### Q3. Can SIGKILL be caught or ignored? Why?
**A.** No. The OS keeps SIGKILL and SIGSTOP uncatchable so it always has a guaranteed way to terminate or stop a process, even a buggy one.

### Q4. What signals are Ctrl-C and Ctrl-Z?
**A.** Ctrl-C → SIGINT (terminate). Ctrl-Z → SIGTSTP (stop / suspend).

### Q5. How do you ignore SIGINT, then restore default?
**A.**
```c
signal(SIGINT, SIG_IGN);
signal(SIGINT, SIG_DFL);
```

---

## 8. Unix Commands and the Shell

### Q1. One pipeline that counts how many `.c` files exist anywhere under your home directory.
**A.** `find ~ -name "*.c" | wc -l`

### Q2. Difference between Ctrl-C and Ctrl-Z?
**A.** Ctrl-C sends SIGINT, default = terminate the foreground process. Ctrl-Z sends SIGTSTP, default = stop / suspend it.

### Q3. `./myscript.sh` says "Permission denied". Two ways to still execute it?
**A.**
```sh
bash myscript.sh
# OR
chmod +x myscript.sh && ./myscript.sh
```

### Q4. What does `chmod 755 file` mean?
**A.** Owner: rwx, group: r-x, others: r-x.

### Q5. What is `ps aux` for?
**A.** List ALL processes on the system (a = all users, u = user-friendly format, x = include processes without a terminal).

---

## 9. make / Compilation

### Notes
make compares **timestamps**. Rebuilds a target if it doesn't exist OR any dependency is newer.

```make
myapp: main.o utils.o
	gcc -o myapp main.o utils.o
main.o: main.c defs.h
	gcc -c main.c
utils.o: utils.c defs.h
	gcc -c utils.c
```

### Q1. If you modify only `defs.h`, what gets rebuilt and why?
**A.** `main.o`, `utils.o`, and `myapp`. Both `.o` files depend on `defs.h`, and `myapp` depends on both `.o` files.

### Q2. How does make decide if a target needs rebuilding?
**A.** It compares timestamps. Rebuild if the target does not exist OR any of its dependencies has a newer modified time than the target.

### Q3. After everything is up to date, you `touch utils.c` and run `make`. What gets recompiled?
**A.** `utils.o` (because `utils.c` is now newer) and `myapp` (because `utils.o` is newer than `myapp`).

### Q4. What does `make clean` typically do?
**A.** Runs a `clean:` target that removes all object files and the final executable, so the next `make` builds from scratch.

---

## 10. Threads + Mutex

### Notes
`counter++` is `read → add → write`. Threads sharing memory can interleave these steps and lose updates.

### Q1. Two threads both increment `counter` 1,000,000 times. Will it reliably equal 2,000,000?
**A.** No. `counter++` is not atomic. Two threads can read the same value, both add 1, both write back the same result — one update is lost. The final value will usually be less than 2,000,000.

### Q2. Fix it with a pthread mutex.
**A.**
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

### Q3. Why do threads need locks but separate processes usually don't?
**A.** Threads share the same address space — same globals, same heap. Without a lock they can step on each other. Processes have separate address spaces, so each one's variables are private.

### Q4. What is `pthread_join` for?
**A.** It waits for a thread to finish and (optionally) collects its return value, similar to `wait()` for processes.

---

## 11. C Type Declarations

### Notes
Read OUT from the variable name. `()` and `[]` bind tighter than `*`. Use parentheses to flip the order.

### Q1. Read `int *b[10]`.
**A.** Array of 10 pointers to int.

### Q2. Read `int (*c)[10]`.
**A.** Pointer to an array of 10 ints.

### Q3. Read `int (*d[10])(char *argv[])`.
**A.** Array of 10 pointers to a function taking `char *argv[]` and returning `int`.

### Q4. Read `void (*signal(int sig, void (*func)(int)))(int)`.
**A.** `signal` is a function. It takes an int and a pointer-to-function-of-int-returning-void. It returns a pointer-to-function-of-int-returning-void.

### Q5. Use a typedef to make signal's declaration readable.
**A.**
```c
typedef void (*sighandler_t)(int);
sighandler_t signal(int sig, sighandler_t func);
```

---

## 12. Operator Precedence

### Notes (highest first)
1. `()` `[]` `.` `->` `++` `--` (postfix) — left-to-right
2. unary `*` `&` `!` `~` `++` `--` `(cast)` `sizeof` — right-to-left
3. `*` `/` `%`
4. `+` `-`
5. `<<` `>>`
6. `<` `>` `<=` `>=`
7. `==` `!=`
8. `&` (bitwise)
9. `^`
10. `|`
11. `&&`
12. `||`
13. `?:` — right-to-left
14. `=` `+=` `-=` … — right-to-left
15. `,`

### Q1. What does `*p++` do?
**A.** Post-increment binds tighter than unary `*`. So it dereferences `p`, then increments `p`. Equivalent to `*(p++)`.

### Q2. What does `(*p)++` do?
**A.** Increments the value pointed to by `p`.

### Q3. In `a & b == c`, which runs first?
**A.** `==` is higher precedence than `&`, so it parses as `a & (b == c)`. Always parenthesize bitwise tests.

---

## 13. Strings + malloc

### Notes
```c
strlen, strcmp, strcpy, strcat, strdup, strtok, atoi, sprintf
```

### Q1. Allocate enough memory to hold the concatenation of s1 and s2.
**A.**
```c
char *buf = malloc(strlen(s1) + strlen(s2) + 1);
strcpy(buf, s1);
strcat(buf, s2);
```

### Q2. What is `strdup`?
**A.** A helper that does `malloc` + `strcpy` in one step. Returns a fresh malloc'd copy of the string.

### Q3. What does `atoi("42abc")` return?
**A.** `42`. It reads digits until it hits a non-digit, then stops.

### Q4. How do you free an array of malloc'd strings?
**A.** Free each element first, then free the array itself.

---

## 14. File I/O

### Q1. List the unbuffered system calls for files.
**A.** `open, creat, read, write, lseek, close`.

### Q2. List the buffered (stdio) ones.
**A.** `fopen, fgetc, fgets, fscanf, fputc, fputs, fprintf, fflush, fclose`.

### Q3. What flags do you use to open a file for writing, creating it if needed and truncating?
**A.** `O_WRONLY | O_CREAT | O_TRUNC`.

### Q4. Difference between `read` and `fread`?
**A.** `read` is unbuffered, calls the kernel directly with an int fd. `fread` uses the stdio buffer through a `FILE *`.

### Q5. What does `lseek(fd, 0, SEEK_END)` do?
**A.** Moves the file offset to the end of the file (and returns the size in bytes).

---

## 15. Directories + stat

### Notes
```c
opendir, readdir, closedir, scandir
mkdir, rmdir, link, unlink, symlink, rename
chdir, getcwd
stat, lstat
```

### Q1. Difference between `stat` and `lstat`?
**A.** `stat` follows symbolic links and returns info about the target. `lstat` returns info about the symlink itself.

### Q2. How do you find a file's size in bytes?
**A.**
```c
struct stat st;
stat("file", &st);
printf("%lld\n", (long long)st.st_size);
```

### Q3. Difference between `unlink` and `rmdir`?
**A.** `unlink` removes a name (file). `rmdir` removes an empty directory.

### Q4. What's a hard link vs a symbolic link?
**A.** Hard link (`link`) makes another name pointing to the same inode. Symlink (`symlink`) is a small file containing a path to another file.

---

## 16. Time + Timers

### Q1. How do you get the current time with microsecond precision?
**A.**
```c
struct timeval tv;
gettimeofday(&tv, NULL);
// tv.tv_sec, tv.tv_usec
```

### Q2. How do you sleep for 500 microseconds?
**A.** `usleep(500);`

### Q3. How do you set up a 1ms repeating timer that delivers SIGALRM?
**A.**
```c
struct itimerval iv;
iv.it_value.tv_sec = 0; iv.it_value.tv_usec = 1000;
iv.it_interval = iv.it_value;
setitimer(ITIMER_REAL, &iv, NULL);
```

### Q4. What does `pause()` do?
**A.** Blocks the process until any signal is delivered.

---

## 17. Terminal (raw mode)

### Q1. How do you put the terminal in raw mode (no canonical, no echo)?
**A.**
```c
struct termios t;
tcgetattr(fd, &t);
t.c_lflag &= ~(ICANON | ECHO);
tcsetattr(fd, TCSANOW, &t);
```
Always restore the original on exit.

### Q2. Why open `/dev/tty` instead of using stdin?
**A.** Stdin may be redirected to a file or pipe. `/dev/tty` always refers to the controlling terminal, so keyboard input still works even when stdin is redirected.

### Q3. How do you get the window size?
**A.**
```c
struct winsize ws;
ioctl(1, TIOCGWINSZ, &ws);
// ws.ws_row, ws.ws_col
```

### Q4. What VT100 escape clears the screen?
**A.** `\033[H\033[J` — move cursor to home, then clear from cursor to end.

---

## 18. Big-picture concept questions

### Q1. What's the difference between a process and a thread?
**A.** A process has its own address space, file descriptors, and memory. Threads inside one process share all of those. Threads are cheaper to create and to switch between, but need locks for shared data.

### Q2. What's a system call vs a library function?
**A.** A system call enters the kernel (`open`, `read`, `fork`). A library function runs in user space (`fopen`, `printf`). Library functions often wrap system calls and add buffering or convenience.

### Q3. Why is buffered I/O faster than unbuffered?
**A.** Each unbuffered call (`read`, `write`) is a system call that crosses into the kernel. Buffered I/O collects bytes in user-space memory and only crosses into the kernel when the buffer fills or you flush — far fewer system calls.

### Q4. What's an inode?
**A.** A data structure on disk that holds a file's metadata (size, permissions, owner, timestamps, block pointers). The directory entry maps a name to an inode number.

### Q5. What is a zombie process?
**A.** A child that has exited but whose exit status has not been collected by `wait()`. It still has an entry in the process table.

---

## Mnemonics

- **fork-exec-wait:** "fork makes a clone, exec replaces the brain, wait collects the body"
- **dup2 then close:** "after copy, close the original"
- **pipe close-everything-everywhere:** every child closes BOTH ends of EVERY pipe
- **zombie vs orphan:** zombie = parent didn't wait; orphan = parent already died
- **SIGKILL/SIGSTOP uncatchable:** "the OS keeps two emergency keys"
- **+1 for \0:** every string buffer needs one extra byte
- **make is timestamp-based:** newer file → rebuild

---

## Final mini-test (do these from memory)

1. Pack 0x5 (3 bits), 0xF (4 bits), 0x2 (2 bits) into one buffer.
2. Write the fork/exec/wait skeleton with status macros.
3. Redirect stdout to `out.txt` using only system calls.
4. How many pipes and forks for `a | b | c`?
5. Difference between Ctrl-C and Ctrl-Z (signals + behavior).
6. Why threads need locks but processes don't.
7. Read `int (*d[10])(char *)` in plain English.
8. Two ways to run a script with no execute permission.
9. Why is `argv[1] == "-i"` wrong?
10. What does `>>` actually do at the system call level?

If you can answer all 10 from memory, you're ready.
