/*
Name: Abdallah Mohamed
Course: COS 350
Program 4 - scroll
Date: April 10, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <termios.h>
#include <string.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#define MAX_BUFFER 1000000
#define MAX_LINES 50000
#define TAB_SIZE 8
#define DEFAULT_SPEED 2.0
#define SPEED_CHANGE 0.2

char buffer[MAX_BUFFER]; /* buffer to hold the file */
long buffer_len = 0;     /* how many bytes in buffer */

char *screen_lines[MAX_LINES];  /* pointer to start of each screen line */
int screen_line_len[MAX_LINES]; /* length of each screen line */
int total_lines = 0;            /* total number of screen lines */

int window_rows = 24;                /* terminal rows */
int window_cols = 80;                /* terminal columns */
int current_top = 0;                 /* first line on screen */
int at_end = 0;                      /* 1 if at end of file */
int scroll_active = 0;               /* 1 if scrolling is on */
double scroll_speed = DEFAULT_SPEED; /* scroll interval in seconds */
int keyboard_fd = -1;                /* file descriptor for keyboard */

struct termios original_term; /* save original terminal settings */

void stop_timer(void);
void cleanup(void);
void handle_alarm(int sig);
void handle_sigint(int sig);
void get_window_size(void);
void build_screen_lines(void);
int get_char_width(int pos, int col, int *used);
void print_screen_line(int n);
void erase_prompt(void);
void draw_prompt(void);
void draw_screen(void);
void scroll_one_line(void);
void set_timer(double seconds);
void setup_terminal(void);
void restore_terminal(void);
void read_file(FILE *fp);
void handle_key(char key);

// get the current window size
void get_window_size(void)
{
    struct winsize ws;

    if (ioctl(1, TIOCGWINSZ, &ws) == -1)
        return;

    if (ws.ws_row > 0)
        window_rows = ws.ws_row;
    if (ws.ws_col > 0)
        window_cols = ws.ws_col;
}

// set terminal to raw mode
void setup_terminal(void)
{
    struct termios new_term;

    tcgetattr(keyboard_fd, &original_term);
    new_term = original_term;
    new_term.c_lflag &= ~(ICANON | ECHO);
    new_term.c_cc[VMIN] = 1;
    new_term.c_cc[VTIME] = 0;
    tcsetattr(keyboard_fd, TCSANOW, &new_term);
}

// restore original terminal settings
void restore_terminal(void)
{
    if (keyboard_fd >= 0)
        tcsetattr(keyboard_fd, TCSANOW, &original_term);
}

// read the whole file into the buffer
void read_file(FILE *fp)
{
    buffer_len = fread(buffer, 1, MAX_BUFFER - 1, fp);
    buffer[buffer_len] = '\0';
}

// get the display width of a character
int get_char_width(int pos, int col, int *used)
{
    char ch = buffer[pos];

    if (ch == '\t')
    {
        *used = 1;
        return TAB_SIZE - (col % TAB_SIZE);
    }

    if (ch == '\b')
    {
        *used = 1;
        return 0;
    }

    if (pos + 2 < buffer_len && buffer[pos + 1] == '\b')
    {
        if (buffer[pos + 2] != '\n')
        {
            *used = 3;
            return 1;
        }
    }

    *used = 1;
    return 1;
}

// build the screen lines from the buffer
void build_screen_lines(void)
{
    int i, start, col, used, w;

    total_lines = 0;
    start = 0;
    col = 0;

    for (i = 0; i < buffer_len && total_lines < MAX_LINES;)
    {
        if (buffer[i] == '\n')
        {
            screen_lines[total_lines] = &buffer[start];
            screen_line_len[total_lines] = i - start;
            total_lines++;
            start = i + 1;
            col = 0;
            i++;
        }
        else
        {
            w = get_char_width(i, col, &used);
            if (w > 0 && col + w > window_cols)
            {
                screen_lines[total_lines] = &buffer[start];
                screen_line_len[total_lines] = i - start;
                total_lines++;
                start = i;
                col = 0;
            }
            else
            {
                col += w;
                i += used;

                if (col >= window_cols)
                {
                    screen_lines[total_lines] = &buffer[start];
                    screen_line_len[total_lines] = i - start;
                    total_lines++;
                    start = i;
                    col = 0;
                }
            }
        }
    }

    if (start < buffer_len && total_lines < MAX_LINES)
    {
        screen_lines[total_lines] = &buffer[start];
        screen_line_len[total_lines] = buffer_len - start;
        total_lines++;
    }

    if (total_lines == 0)
    {
        screen_lines[0] = buffer;
        screen_line_len[0] = 0;
        total_lines = 1;
    }
}

// print one screen line, handle tabs and extra credit
void print_screen_line(int n)
{
    int i, col, used, j, spaces;
    char ch, next;
    int offset;

    col = 0;
    i = 0;

    while (i < screen_line_len[n] && col < window_cols)
    {
        offset = (int)(screen_lines[n] - buffer) + i;
        ch = buffer[offset];

        if (ch == '\t')
        {
            spaces = TAB_SIZE - (col % TAB_SIZE);
            for (j = 0; j < spaces && col < window_cols; j++)
            {
                putchar(' ');
                col++;
            }
            i++;
        }
        else if (ch == '\b')
        {
            i++;
        }
        else if (offset + 2 < buffer_len && buffer[offset + 1] == '\b')
        {
            next = buffer[offset + 2];

            if (ch == next)
            {
                printf("\033[1m%c\033[0m", ch);
                col++;
            }
            else if (ch == '_')
            {
                printf("\033[4m%c\033[0m", next);
                col++;
            }
            else
            {
                putchar(next);
                col++;
            }
            i += 3;
        }
        else
        {
            if (col < window_cols)
            {
                putchar(ch);
                col++;
            }
            i++;
        }
    }
}

// erase the prompt line
void erase_prompt(void)
{
    printf("\033[%d;1H\033[0K", window_rows);
    fflush(stdout);
}

// draw the prompt line
void draw_prompt(void)
{
    printf("\033[%d;1H\033[7m", window_rows);

    if (at_end)
        printf(" (END) ");
    else if (scroll_active)
        printf(" scrolling %.1f sec  f=faster s=slower ", scroll_speed);
    else
        printf(" space=page enter=scroll q=quit ");

    printf("\033[0m\033[0K");
    fflush(stdout);
}

/* draw a full screen of text */
void draw_screen(void)
{
    int i;
    int page_len = window_rows - 1;

    /* clear screen */
    printf("\033[H\033[J");

    /* print each line */
    for (i = 0; i < page_len; i++)
    {
        printf("\033[%d;1H\033[0K", i + 1);
        if (current_top + i < total_lines)
            print_screen_line(current_top + i);
    }

    at_end = (current_top + page_len >= total_lines);
    draw_prompt();
}

/* scroll forward one line */
void scroll_one_line(void)
{
    int page_len = window_rows - 1;
    int next_line = current_top + page_len;

    if (next_line >= total_lines)
    {
        at_end = 1;
        scroll_active = 0;
        stop_timer();
        return;
    }

    current_top++;
    printf("\033[%d;1H\n", window_rows - 1);
    printf("\033[%d;1H\033[0K", window_rows - 1);
    print_screen_line(next_line);

    at_end = (current_top + page_len >= total_lines);
}

/* set the interval timer */
void set_timer(double seconds)
{
    struct itimerval timer;
    int sec = (int)seconds;
    int usec = (int)((seconds - sec) * 1000000.0);

    timer.it_value.tv_sec = sec;
    timer.it_value.tv_usec = usec;
    timer.it_interval.tv_sec = sec;
    timer.it_interval.tv_usec = usec;
    setitimer(ITIMER_REAL, &timer, NULL);
}

/* stop the timer */
void stop_timer(void)
{
    struct itimerval timer;

    timer.it_value.tv_sec = 0;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
}

/* restore terminal and clean up */
void cleanup(void)
{
    stop_timer();
    restore_terminal();
    printf("\033[%d;1H\033[0K\n", window_rows);
    fflush(stdout);
}

/* timer signal handler - scroll one line */
void handle_alarm(int sig)
{
    if (scroll_active)
    {
        erase_prompt();
        scroll_one_line();
        draw_prompt();
    }
}

/* ctrl-c signal handler */
void handle_sigint(int sig)
{
    cleanup();
    exit(0);
}

/* handle one keypress */
void handle_key(char key)
{
    /* space - page forward */
    if (key == ' ')
    {
        scroll_active = 0;
        stop_timer();

        if (!at_end)
        {
            current_top += window_rows - 1;
            if (current_top >= total_lines)
                current_top = total_lines - 1;
            draw_screen();
        }
        else
        {
            draw_prompt();
        }
    }
    /* enter - toggle scrolling */
    else if (key == '\n' || key == '\r')
    {
        if (scroll_active)
        {
            scroll_active = 0;
            stop_timer();
        }
        else if (!at_end)
        {
            scroll_active = 1;
            set_timer(scroll_speed);
        }
        draw_prompt();
    }
    /* f - scroll faster */
    else if (key == 'f')
    {
        scroll_speed *= (1.0 - SPEED_CHANGE);
        if (scroll_speed < 0.1)
            scroll_speed = 0.1;
        if (scroll_active)
            set_timer(scroll_speed);
        draw_prompt();
    }
    /* s - scroll slower */
    else if (key == 's')
    {
        scroll_speed *= (1.0 + SPEED_CHANGE);
        if (scroll_speed > 10.0)
            scroll_speed = 10.0;
        if (scroll_active)
            set_timer(scroll_speed);
        draw_prompt();
    }
}

int main(int argc, char *argv[])
{
    FILE *fp;
    char key;

    fp = stdin;

    if (argc > 2)
    {
        printf("Usage: %s [file]\n", argv[0]);
        return 1;
    }

    /* open file if given */
    if (argc == 2)
    {
        fp = fopen(argv[1], "r");
        if (fp == NULL)
        {
            printf("Cannot open %s\n", argv[1]);
            return 1;
        }
    }

    /* read file into buffer */
    read_file(fp);

    if (fp != stdin)
        fclose(fp);

    /* get window size */
    get_window_size();

    /* break file into screen lines */
    build_screen_lines();

    /* open keyboard */
    if (argc == 2)
        keyboard_fd = STDIN_FILENO;
    else
        keyboard_fd = open("/dev/tty", O_RDONLY);

    if (keyboard_fd < 0)
    {
        printf("Cannot open keyboard\n");
        return 1;
    }

    /* set terminal to raw mode */
    setup_terminal();

    /* set signal handlers */
    signal(SIGALRM, handle_alarm);
    signal(SIGINT, handle_sigint);

    /* show first page */
    draw_screen();

    /* main loop - wait for keyboard input */
    while (1)
    {
        if (read(keyboard_fd, &key, 1) != 1)
            continue;

        if (key == 'q')
        {
            cleanup();
            break;
        }

        handle_key(key);
    }

    if (argc == 1 && keyboard_fd >= 0)
        close(keyboard_fd);

    return 0;
}
