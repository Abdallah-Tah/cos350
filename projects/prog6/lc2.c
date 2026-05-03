#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

struct child_info {
    pid_t pid;
    int pipe_read_fd;
    const char *filename;
};

static void print_count(unsigned long long count, const char *name)
{
    printf("%7llu %s\n", count, name);
}

static int find_child_index(const struct child_info *children, int count, pid_t pid)
{
    int i;

    for (i = 0; i < count; ++i) {
        if (children[i].pid == pid) {
            return i;
        }
    }

    return -1;
}

static int read_child_count(int fd, unsigned long long *count_out)
{
    char buffer[512];
    char *end = NULL;
    size_t used = 0;
    ssize_t bytes_read;

    while ((bytes_read = read(fd, buffer + used, sizeof(buffer) - 1 - used)) > 0) {
        used += (size_t)bytes_read;
        if (used >= sizeof(buffer) - 1) {
            break;
        }
    }

    if (bytes_read < 0) {
        return -1;
    }

    buffer[used] = '\0';
    errno = 0;
    *count_out = strtoull(buffer, &end, 10);

    if (end == buffer || errno != 0) {
        errno = EPROTO;
        return -1;
    }

    return 0;
}

static int build_lc1_path(const char *argv0, char *path_buffer, size_t buffer_size)
{
    const char *slash = strrchr(argv0, '/');
    size_t dir_len;

    if (slash == NULL) {
        if (snprintf(path_buffer, buffer_size, "lc1") >= (int)buffer_size) {
            errno = ENAMETOOLONG;
            return -1;
        }
        return 0;
    }

    dir_len = (size_t)(slash - argv0);
    if (dir_len + sizeof("/lc1") > buffer_size) {
        errno = ENAMETOOLONG;
        return -1;
    }

    memcpy(path_buffer, argv0, dir_len);
    path_buffer[dir_len] = '\0';
    strcat(path_buffer, "/lc1");
    return 0;
}

int main(int argc, char *argv[])
{
    char lc1_path[PATH_MAX];
    struct child_info *children;
    unsigned long long total = 0;
    int exit_status = 0;
    int started = 0;
    int remaining;
    int i;

    if (argc < 2) {
        fprintf(stderr, "usage: %s file ...\n", argv[0]);
        return 1;
    }

    if (build_lc1_path(argv[0], lc1_path, sizeof(lc1_path)) != 0) {
        fprintf(stderr, "%s: cannot locate lc1: %s\n", argv[0], strerror(errno));
        return 1;
    }

    children = calloc((size_t)(argc - 1), sizeof(*children));
    if (children == NULL) {
        perror("calloc");
        return 1;
    }

    for (i = 1; i < argc; ++i) {
        int pipe_fds[2];
        pid_t pid;

        if (pipe(pipe_fds) != 0) {
            perror("pipe");
            exit_status = 1;
            break;
        }

        pid = fork();
        if (pid < 0) {
            perror("fork");
            close(pipe_fds[0]);
            close(pipe_fds[1]);
            exit_status = 1;
            break;
        }

        if (pid == 0) {
            char *const child_argv[] = { lc1_path, argv[i], NULL };

            close(pipe_fds[0]);
            if (dup2(pipe_fds[1], STDOUT_FILENO) < 0) {
                perror("dup2");
                _exit(1);
            }
            close(pipe_fds[1]);
            execv(lc1_path, child_argv);
            perror(lc1_path);
            _exit(1);
        }

        close(pipe_fds[1]);
        children[started].pid = pid;
        children[started].pipe_read_fd = pipe_fds[0];
        children[started].filename = argv[i];
        ++started;
    }

    remaining = started;
    while (remaining > 0) {
        int status = 0;
        pid_t pid = wait(&status);
        int child_index;
        unsigned long long count = 0;

        if (pid < 0) {
            perror("wait");
            exit_status = 1;
            break;
        }

        child_index = find_child_index(children, started, pid);
        if (child_index < 0) {
            continue;
        }

        if (!WIFEXITED(status) || WEXITSTATUS(status) != 0) {
            exit_status = 1;
        } else if (read_child_count(children[child_index].pipe_read_fd, &count) != 0) {
            fprintf(stderr, "%s: failed to read count for %s\n",
                    argv[0], children[child_index].filename);
            exit_status = 1;
        } else {
            print_count(count, children[child_index].filename);
            total += count;
        }

        close(children[child_index].pipe_read_fd);
        children[child_index].pipe_read_fd = -1;
        --remaining;
    }

    for (i = 0; i < started; ++i) {
        if (children[i].pipe_read_fd >= 0) {
            close(children[i].pipe_read_fd);
        }
    }

    free(children);

    if (argc > 2) {
        print_count(total, "total");
    }

    return exit_status;
}
