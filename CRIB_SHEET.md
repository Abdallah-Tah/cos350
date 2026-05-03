# COS 350 - Crib Sheet (one 8.5x11 page, handwritten)

> Copy this onto ONE side of a sheet. Designed to fit when written small but readable.

---

**BITWISE** & AND  | OR  ^ XOR  ~ NOT  <<  >>
mask N bits: `(1<<N)-1`
pack: `b=v1; b|=v2<<bits1; b|=v3<<(bits1+bits2);`

**POINTERS**
`char *w[4]` = array of 4 ptrs · `char (*w)[4]` = ptr to array of 4
strings need `+1` for `\0` · `==` ≠ strcmp
`w[1]=malloc(strlen("x")+1); strcpy(w[1],"x");`

**ARGV**  `./mygrep -i -n "hello world" data.txt`
argc=5 · argv[0]=./mygrep · argv[1]=-i · argv[2]=-n · argv[3]="hello world" · argv[4]=data.txt · argv[5]=NULL
compare: `strcmp(argv[1],"-i")==0`

**FORK / EXEC / WAIT**
```
pid_t pid=fork();
if(pid==0){ execlp("ls","ls","-l",NULL); perror("exec"); exit(1); }
int s; wait(&s);
if(WIFEXITED(s))   printf("%d",WEXITSTATUS(s));
else if(WIFSIGNALED(s)) printf("%d",WTERMSIG(s));
```
no wait → zombie · parent dies → orphan (init adopts)
exec succeeds → next lines NEVER run · exec fails → run perror+exit

**REDIRECT  sort < in > out**
```
int i=open("in",O_RDONLY);              dup2(i,0); close(i);
int o=open("out",O_WRONLY|O_CREAT|O_TRUNC,0644); dup2(o,1); close(o);
execlp("sort","sort",NULL);
```
close after dup2 → no leak · `>>` = O_APPEND (atomic seek+write)

**PIPES  a | b | c**
2 pipe(), 3 fork() · each child: dup end, close BOTH ends of EVERY pipe, exec
write end open in reader → no EOF → reader hangs

**SIGNALS** signal() simple · sigaction() reliable (SA_RESTART, mask, SA_SIGINFO)
SIGKILL(9), SIGSTOP(19) → cannot catch/ignore/block
INT(2)=Ctrl-C term · QUIT(3)=Ctrl-\ core · ALRM(14)=alarm/timer
TERM(15) · CHLD(17) ignored · TSTP(20)=Ctrl-Z stop
SIG_IGN ignore · SIG_DFL default
```
void h(int s){...} signal(SIGALRM,h); alarm(5); pause();
```

**SHELL**
count .c under home: `find ~ -name "*.c" | wc -l`
no perm: `bash s.sh`  OR  `chmod +x s.sh; ./s.sh`
chmod 755 = rwxr-xr-x

**MAKE**  compares TIMESTAMPS · rebuild if missing or any dep newer
defs.h changes → all .o + final exe rebuilt
touch utils.c → utils.o + final rebuilt

**THREADS**  counter++ NOT atomic (read/add/write) → lost updates
threads share addr space → need lock · processes don't share → usually no lock
```
pthread_mutex_t L=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_lock(&L); counter++; pthread_mutex_unlock(&L);
pthread_create(&t,NULL,fn,arg); pthread_join(t,&r);
pthread_cond_wait(&c,&L); pthread_cond_signal(&c);
```

**STRINGS**  strlen strcmp strcpy strcat strdup strtok atoi sprintf
**MALLOC**  `malloc(strlen(s1)+strlen(s2)+1)` · `n*sizeof(int)` · free()

**FILE I/O**
unbuf: open creat read write lseek close · flags O_RDONLY/WRONLY/RDWR/CREAT/TRUNC/APPEND · whence SEEK_SET/CUR/END
buf:   fopen fgetc fgets fscanf fputc fputs fprintf fflush fclose · "r w a r+ w+ a+"
fd: 0=stdin 1=stdout 2=stderr  (STDIN_FILENO etc.)

**DIRS**  opendir readdir closedir scandir · mkdir rmdir · link unlink symlink rename · chdir getcwd
stat: st_size st_mode st_mtime st_uid st_nlink st_ino · lstat = no symlink follow

**TIME**  `gettimeofday(&tv,NULL)` tv.tv_sec/tv_usec · sleep usleep nanosleep
alarm(s)→SIGALRM · setitimer(ITIMER_REAL,&iv,NULL) repeating · pause()

**TERMINAL**  open("/dev/tty",O_RDWR); tcgetattr(); flag &= ~(ICANON|ECHO); tcsetattr(fd,TCSANOW,&t); RESTORE on exit
window: `ioctl(1,TIOCGWINSZ,&ws)` ws_row/ws_col
VT100: `\033[H\033[J` clear · `\033[7m` reverse · `\033[1m` bold · `\033[4m` under · `\033[0m` reset

**TYPE DECL — read out from name, () [] before ***
`int *b[10]`        array of 10 ptrs to int
`int (*c)[10]`      ptr to array of 10 ints
`int (*d[10])(char*)` array of 10 ptrs to fn(char*) returning int
`void (*signal(int,void(*)(int)))(int)` ⇒ `typedef void(*sh)(int); sh signal(int,sh);`

**PRECEDENCE**  () [] . -> ++ -- | unary * & ! ~ sizeof | * / % | + - | << >> | < > <= >= | == != | & | ^ | \| | && | \|\| | ?: | = += | ,

**TRAPS**
+1 for `\0` · always close after dup2 · close ALL pipe ends in children · perror+exit after exec · wait or get zombies · SIGKILL/SIGSTOP uncatchable · == vs strcmp · make = timestamps · `>>` is O_APPEND atomic
