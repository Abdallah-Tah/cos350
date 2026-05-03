#include "linecount.h"

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 65536

int count_lines_file(const char *path, unsigned long long *count_out)
{
    char buffer[BUFFER_SIZE];
    unsigned long long count = 0;
    ssize_t bytes_read;
    int fd = open(path, O_RDONLY);
    int saved_errno = 0;

    if (fd < 0) {
        return -1;
    }

    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        ssize_t i;

        for (i = 0; i < bytes_read; ++i) {
            if (buffer[i] == '\n') {
                ++count;
            }
        }
    }

    if (bytes_read < 0) {
        saved_errno = errno;
    }

    if (close(fd) < 0 && bytes_read >= 0) {
        return -1;
    }

    if (bytes_read < 0) {
        errno = saved_errno;
        return -1;
    }

    *count_out = count;
    return 0;
}
